import math
import time
import random
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# --- GPS Helper Functions ---


def haversine(lat1, lon1, lat2, lon2):
    """
    Calculate the great circle distance in meters between two points
    on the earth (specified in decimal degrees).
    """
    radius_earth = 6371000  # In meters
    phi1 = math.radians(lat1)
    phi2 = math.radians(lat2)
    delta_phi = math.radians(lat2 - lat1)
    delta_lambda = math.radians(lon2 - lon1)

    a = (math.sin(delta_phi / 2.0)**2 +
         math.cos(phi1) * math.cos(phi2) *
         math.sin(delta_lambda / 2.0)**2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    distance = radius_earth * c
    return distance


def calculate_bearing(lat1, lon1, lat2, lon2):
    """
    Calculate the bearing in degrees from point 1 to point 2.
    North = 0, East = 90, South = 180, West = 270.
    """
    phi1 = math.radians(lat1)
    lambda1 = math.radians(lon1)
    phi2 = math.radians(lat2)
    lambda2 = math.radians(lon2)

    y = math.sin(lambda2 - lambda1) * math.cos(phi2)
    x = (math.cos(phi1) * math.sin(phi2) -
         math.sin(phi1) * math.cos(phi2) * math.cos(lambda2 - lambda1))
    theta = math.atan2(y, x)
    bearing = (math.degrees(theta) + 360) % 360
    return bearing


def get_random_initial_position(center_lat, center_lon, max_radius_meters):
    """
    Generates a random GPS coordinate within a given radius
    from a center point using basic trigonometry.
    """
    # Generate a random bearing and distance
    random_bearing_rad = random.uniform(0, 2 * math.pi)
    random_distance_meters = random.uniform(0, max_radius_meters)

    # Convert meter changes to degree changes (approximation)
    delta_lat_meters = random_distance_meters * math.cos(random_bearing_rad)
    delta_lon_meters = random_distance_meters * math.sin(random_bearing_rad)

    new_lat = center_lat + delta_lat_meters / 111000.0
    new_lon = center_lon + delta_lon_meters / (
        111000.0 * math.cos(math.radians(center_lat)))

    return new_lat, new_lon

# --- PID Controller Class ---


class SimplePID:
    """A simple Proportional-Integral-Derivative (PID) controller."""

    def __init__(self, kp, ki, kd, setpoint,
                 output_limits=(-1.0, 1.0),
                 integral_limits=(-1.0, 1.0),
                 name="PID"):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.setpoint = setpoint
        self.output_limits = output_limits
        self.integral_limits = integral_limits  # Anti-windup for integral
        self.name = name

        self._integral = 0.0
        self._previous_error = 0.0
        self._last_time = None

    def update(self, current_value, dt=None):
        """
        Calculate PID output.

        :param current_value: The current value of the process variable.
        :param dt: Time delta in seconds. Calculated internally if None.
        :return: PID output clamped within output_limits.
        """
        if dt is None:
            current_time = time.monotonic()
            if self._last_time is None:
                dt_calc = 0.01  # Assume a small dt for the first call
            else:
                dt_calc = current_time - self._last_time
            self._last_time = current_time
            dt_to_use = max(dt_calc, 1e-6)  # Ensure dt is positive
        else:
            dt_to_use = dt

        if dt_to_use <= 0:
            return 0.0  # Cannot compute derivative with non-positive dt

        error = self.setpoint - current_value

        p_out = self.kp * error

        self._integral += error * dt_to_use
        self._integral = self._clamp(self._integral, self.integral_limits)
        i_out = self.ki * self._integral

        derivative = (error - self._previous_error) / dt_to_use
        d_out = self.kd * derivative

        output = p_out + i_out + d_out
        output = self._clamp(output, self.output_limits)

        self._previous_error = error
        return output

    def reset(self):
        """Reset the PID controller's integral and derivative states."""
        self._integral = 0.0
        self._previous_error = 0.0
        self._last_time = None

    def _clamp(self, value, limits):
        """Clamp a value between lower and upper limits."""
        lower, upper = limits
        return max(lower, min(value, upper))

# --- Drone Navigation Controller (Fixed Yaw) ---


class DroneNavigator:
    """Navigates a drone with a fixed yaw to target GPS coordinates."""

    def __init__(self, target_lat, target_lon,
                 kp_pitch, ki_pitch, kd_pitch,
                 kp_roll, ki_roll, kd_roll,
                 max_pitch_cmd=20.0,
                 max_roll_cmd=20.0,
                 distance_threshold=3.0):
        self.target_lat = target_lat
        self.target_lon = target_lon
        self.max_pitch_cmd = max_pitch_cmd
        self.max_roll_cmd = max_roll_cmd
        self.distance_threshold = distance_threshold

        self.pitch_pid = SimplePID(
            kp_pitch, ki_pitch, kd_pitch, setpoint=0.0,
            output_limits=(-1.0, 1.0), integral_limits=(-50.0, 50.0),
            name="Pitch (Forward Error)"
        )
        self.roll_pid = SimplePID(
            kp_roll, ki_roll, kd_roll, setpoint=0.0,
            output_limits=(-1.0, 1.0), integral_limits=(-50.0, 50.0),
            name="Roll (Rightward Error)"
        )
        self._last_time_nav_update = None

    def _get_nav_dt(self):
        """Calculate the time delta for the navigator's update cycle."""
        current_time = time.monotonic()
        if self._last_time_nav_update is None:
            dt = 0.01
        else:
            dt = current_time - self._last_time_nav_update
        self._last_time_nav_update = current_time
        return max(dt, 1e-6)

    def update(self, current_lat, current_lon,
               fixed_drone_heading_degrees, dt_external=None):
        """Calculate pitch and roll commands to navigate."""
        dt = dt_external if dt_external is not None else self._get_nav_dt()

        distance = haversine(
            current_lat, current_lon, self.target_lat, self.target_lon)
        if distance < self.distance_threshold:
            self.pitch_pid.reset()
            self.roll_pid.reset()
            return 0.0, 0.0, True  # Return True for target reached

        bearing_rad = math.radians(calculate_bearing(
            current_lat, current_lon, self.target_lat, self.target_lon))
        heading_rad = math.radians(fixed_drone_heading_degrees)

        relative_bearing_rad = math.atan2(
            math.sin(bearing_rad - heading_rad),
            math.cos(bearing_rad - heading_rad))

        error_forward = distance * math.cos(relative_bearing_rad)
        error_right = distance * math.sin(relative_bearing_rad)

        pitch_norm = self.pitch_pid.update(error_forward, dt=dt)
        pitch_cmd = -pitch_norm * self.max_pitch_cmd

        roll_norm = self.roll_pid.update(error_right, dt=dt)
        roll_cmd = -roll_norm * self.max_roll_cmd

        return pitch_cmd, roll_cmd, False  # Target not reached


# --- Live Simulation ---

if __name__ == "__main__":
    # --- Simulation Parameters ---
    TARGET_LATITUDE = 34.052235
    TARGET_LONGITUDE = -118.243683

    # Generate a random starting position within 300m of the target
    INITIAL_LAT, INITIAL_LON = get_random_initial_position(
        TARGET_LATITUDE, TARGET_LONGITUDE, 300
    )

    FIXED_DRONE_HEADING_DEGREES = random.uniform(0.0, 360.0)

    # PID Gains - Kp values are lowered to prevent aggressive initial response
    KP_PITCH = 0.005  # Reduced from 0.05
    KI_PITCH = 0.001
    KD_PITCH = 0.02
    KP_ROLL = 0.005  # Reduced from 0.05
    KI_ROLL = 0.001
    KD_ROLL = 0.02

    MAX_PITCH_CMD_DEGREES = 15.0
    MAX_ROLL_CMD_DEGREES = 15.0

    # Slew Rate Limits (degrees per second)
    PITCH_SLEW_RATE_LIMIT = 20.0
    ROLL_SLEW_RATE_LIMIT = 25.0

    MAX_SPEED_FORWARD_MPS = 3.0
    MAX_SPEED_STRAFE_MPS = 2.0

    # --- Initialization ---
    current_pos = {'lat': INITIAL_LAT, 'lon': INITIAL_LON}
    path_lats, path_lons = [INITIAL_LAT], [INITIAL_LON]
    step_count = 0
    # Initialize the drone's actual commands to a random state
    actual_pitch_cmd = random.uniform(-MAX_PITCH_CMD_DEGREES,
                                      MAX_PITCH_CMD_DEGREES)
    actual_roll_cmd = random.uniform(-MAX_ROLL_CMD_DEGREES,
                                     MAX_ROLL_CMD_DEGREES)

    navigator = DroneNavigator(
        target_lat=TARGET_LATITUDE, target_lon=TARGET_LONGITUDE,
        kp_pitch=KP_PITCH, ki_pitch=KI_PITCH, kd_pitch=KD_PITCH,
        kp_roll=KP_ROLL, ki_roll=KI_ROLL, kd_roll=KD_ROLL,
        max_pitch_cmd=MAX_PITCH_CMD_DEGREES,
        max_roll_cmd=MAX_ROLL_CMD_DEGREES,
        distance_threshold=3.0
    )

    # --- Plot Setup ---
    fig, ax = plt.subplots(figsize=(10, 8))
    fig.subplots_adjust(top=0.85, left=0.1)

    ax.set_xlabel("Longitude (degrees)")
    ax.set_ylabel("Latitude (degrees)")
    title = (
        f"Drone Navigation (Fixed Heading: "
        f"{FIXED_DRONE_HEADING_DEGREES:.1f}°)"
    )
    ax.set_title(title)
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')

    # Set static plot limits with padding
    min_lon = min(INITIAL_LON, TARGET_LONGITUDE)
    max_lon = max(INITIAL_LON, TARGET_LONGITUDE)
    min_lat = min(INITIAL_LAT, TARGET_LATITUDE)
    max_lat = max(INITIAL_LAT, TARGET_LATITUDE)
    lon_pad = (max_lon - min_lon) * 0.2 if max_lon > min_lon else 0.002
    lat_pad = (max_lat - min_lat) * 0.2 if max_lat > min_lat else 0.002
    ax.set_xlim(min_lon - lon_pad, max_lon + lon_pad)
    ax.set_ylim(min_lat - lat_pad, max_lat + lat_pad)

    # Static elements
    ax.plot(INITIAL_LON, INITIAL_LAT, 'go', markersize=8, label='Start')
    ax.plot(TARGET_LONGITUDE, TARGET_LATITUDE, 'rx', markersize=10, mew=2,
            label='Target')

    # Dynamic elements
    line, = ax.plot(path_lons, path_lats, 'b-', label='Drone Path', lw=1.5)
    drone_marker, = ax.plot(
        INITIAL_LON, INITIAL_LAT, 'o', color='purple', markersize=6)
    status_text = fig.text(
        0.02, 0.97, '', verticalalignment='top', fontsize=10,
        bbox=dict(boxstyle='round,pad=0.5', fc='wheat', alpha=0.5))
    handles, labels = ax.get_legend_handles_labels()
    fig.legend(handles, labels, loc='upper right', bbox_to_anchor=(0.98, 0.97))

    dt_sim_update = 0.1  # Simulation time step

    def animate(i):
        """Performs one animation step."""
        global step_count, actual_pitch_cmd, actual_roll_cmd
        step_count += 1

        # PID controller is always active, calculating the desired state
        target_pitch_cmd, target_roll_cmd, reached = navigator.update(
            current_pos['lat'], current_pos['lon'],
            FIXED_DRONE_HEADING_DEGREES,
            dt_external=dt_sim_update
        )

        if reached:
            ani.event_source.stop()
            # Display final state using the last actual commands
            final_text = (
                f'Target Reached!\n'
                f'Steps: {step_count}\n'
                f'Final Pitch: {actual_pitch_cmd:.2f}°\n'
                f'Final Roll: {actual_roll_cmd:.2f}°'
            )
            status_text.set_text(final_text)
            return

        # --- Apply Slew Rate Limiting ---
        # The slew rate limiter smoothly moves the actual command
        # towards the target command calculated by the PID.
        max_pitch_change = PITCH_SLEW_RATE_LIMIT * dt_sim_update
        max_roll_change = ROLL_SLEW_RATE_LIMIT * dt_sim_update

        pitch_error = target_pitch_cmd - actual_pitch_cmd
        roll_error = target_roll_cmd - actual_roll_cmd

        pitch_change = max(-max_pitch_change,
                           min(pitch_error, max_pitch_change))
        roll_change = max(-max_roll_change,
                          min(roll_error, max_roll_change))

        actual_pitch_cmd += pitch_change
        actual_roll_cmd += roll_change
        # --- End Slew Rate Limiting ---

        speed_fwd = (actual_pitch_cmd / MAX_PITCH_CMD_DEGREES *
                     MAX_SPEED_FORWARD_MPS)
        speed_strafe = (actual_roll_cmd / MAX_ROLL_CMD_DEGREES *
                        MAX_SPEED_STRAFE_MPS)
        dist_fwd = speed_fwd * dt_sim_update
        dist_strafe = speed_strafe * dt_sim_update
        heading_rad = math.radians(FIXED_DRONE_HEADING_DEGREES)

        delta_n = ((dist_fwd * math.cos(heading_rad)) -
                   (dist_strafe * math.sin(heading_rad)))
        delta_e = ((dist_fwd * math.sin(heading_rad)) +
                   (dist_strafe * math.cos(heading_rad)))

        current_pos['lat'] += delta_n / 111000.0
        current_pos['lon'] += delta_e / (
            111000.0 * math.cos(math.radians(current_pos['lat'])))

        path_lats.append(current_pos['lat'])
        path_lons.append(current_pos['lon'])

        line.set_data(path_lons, path_lats)
        drone_marker.set_data([current_pos['lon']], [current_pos['lat']])

        dist_now = haversine(
            current_pos['lat'], current_pos['lon'],
            TARGET_LATITUDE, TARGET_LONGITUDE)
        current_status_text = (
            f'Step: {step_count}\n'
            f'Distance: {dist_now:.2f}m\n'
            f'Pitch Cmd: {actual_pitch_cmd:.2f}°\n'
            f'Roll Cmd: {actual_roll_cmd:.2f}°'
        )
        status_text.set_text(current_status_text)

    # Set blit=False for robust rendering of all elements
    ani = animation.FuncAnimation(
        fig, animate, frames=None,
        interval=10, blit=False, repeat=False)

    plt.show()
