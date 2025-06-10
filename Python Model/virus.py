import math
import time
import random  # Added for random heading generation
import matplotlib.pyplot as plt

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


def normalize_angle_degrees(angle):
    """Normalize an angle to the range [-180, 180) degrees."""
    angle = angle % 360
    if angle >= 180:
        angle -= 360
    return angle

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

        # Proportional term
        p_out = self.kp * error

        # Integral term
        self._integral += error * dt_to_use
        self._integral = self._clamp(self._integral, self.integral_limits)
        i_out = self.ki * self._integral

        # Derivative term
        derivative = (error - self._previous_error) / dt_to_use
        d_out = self.kd * derivative

        # Total output
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
                 distance_threshold=5.0):
        self.target_lat = target_lat
        self.target_lon = target_lon
        self.max_pitch_cmd = max_pitch_cmd
        self.max_roll_cmd = max_roll_cmd
        self.distance_threshold = distance_threshold

        # PID for pitch controls the error along the drone's forward axis.
        self.pitch_pid = SimplePID(
            kp_pitch, ki_pitch, kd_pitch, setpoint=0.0,
            output_limits=(-1.0, 1.0), integral_limits=(-50.0, 50.0),
            name="Pitch (Forward Error)"
        )
        # PID for roll controls the error along the drone's right axis.
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
            dt = 0.01  # Default for first call
        else:
            dt = current_time - self._last_time_nav_update
        self._last_time_nav_update = current_time
        return max(dt, 1e-6)  # Ensure dt is positive

    def update(self, current_lat, current_lon,
               fixed_drone_heading_degrees, dt_external=None):
        """Calculate pitch and roll commands to navigate towards the target."""
        dt = dt_external if dt_external is not None else self._get_nav_dt()

        distance = haversine(
            current_lat, current_lon, self.target_lat, self.target_lon)
        if distance < self.distance_threshold:
            self.pitch_pid.reset()
            self.roll_pid.reset()
            return 0.0, 0.0

        bearing_rad = math.radians(calculate_bearing(
            current_lat, current_lon, self.target_lat, self.target_lon))
        heading_rad = math.radians(fixed_drone_heading_degrees)

        # Angle of target relative to drone's fixed heading.
        relative_bearing_rad = math.atan2(
            math.sin(bearing_rad - heading_rad),
            math.cos(bearing_rad - heading_rad))

        # Decompose total distance into forward and rightward errors.
        error_forward = distance * math.cos(relative_bearing_rad)
        error_right = distance * math.sin(relative_bearing_rad)

        # Get Pitch command from PID to correct forward error.
        pitch_norm = self.pitch_pid.update(error_forward, dt=dt)
        pitch_cmd = -pitch_norm * self.max_pitch_cmd

        # Get Roll command from PID to correct rightward error.
        roll_norm = self.roll_pid.update(error_right, dt=dt)
        roll_cmd = -roll_norm * self.max_roll_cmd

        return pitch_cmd, roll_cmd

    def set_target(self, lat, lon):
        """Update the target coordinates and reset PIDs."""
        self.target_lat = lat
        self.target_lon = lon
        self.pitch_pid.reset()
        self.roll_pid.reset()
        self._last_time_nav_update = None

    def is_target_reached(self, current_lat, current_lon):
        """
        Check if the drone is within the distance threshold of the target.
        """
        distance = haversine(
            current_lat, current_lon, self.target_lat, self.target_lon)
        return distance < self.distance_threshold

# --- Example Usage (Fixed Yaw Simulation) ---


if __name__ == "__main__":
    # --- Simulation Parameters ---
    TARGET_LATITUDE = 34.052235
    TARGET_LONGITUDE = -118.243683

    INITIAL_LAT = 34.050000
    INITIAL_LON = -118.240000

    # Drone's heading is FIXED and randomly generated.
    FIXED_DRONE_HEADING_DEGREES = random.uniform(0.0, 360.0)

    # PID Gains (require tuning for real-world performance)
    KP_PITCH = 0.05
    KI_PITCH = 0.001
    KD_PITCH = 0.02
    KP_ROLL = 0.05
    KI_ROLL = 0.001
    KD_ROLL = 0.02

    MAX_PITCH_CMD_DEGREES = 15.0
    MAX_ROLL_CMD_DEGREES = 15.0

    MAX_SPEED_FORWARD_MPS = 3.0
    MAX_SPEED_STRAFE_MPS = 2.0

    # --- Initialization ---
    current_lat = INITIAL_LAT
    current_lon = INITIAL_LON

    path_lats = [current_lat]
    path_lons = [current_lon]

    navigator = DroneNavigator(
        target_lat=TARGET_LATITUDE, target_lon=TARGET_LONGITUDE,
        kp_pitch=KP_PITCH, ki_pitch=KI_PITCH, kd_pitch=KD_PITCH,
        kp_roll=KP_ROLL, ki_roll=KI_ROLL, kd_roll=KD_ROLL,
        max_pitch_cmd=MAX_PITCH_CMD_DEGREES,
        max_roll_cmd=MAX_ROLL_CMD_DEGREES,
        distance_threshold=3.0
    )

    print("Drone Navigation Simulation Started (Fixed Yaw).")
    print(f"Target: Lat={TARGET_LATITUDE:.6f}, Lon={TARGET_LONGITUDE:.6f}")
    print(f"Start:  Lat={current_lat:.6f}, Lon={current_lon:.6f}")
    print(f"Drone Fixed Heading: {FIXED_DRONE_HEADING_DEGREES:.2f}°")

    # --- Simulation Loop ---
    max_simulation_steps = 10000  # Safety break
    dt_sim_update = 0.1         # Simulation time step in seconds
    step_count = 0

    while step_count < max_simulation_steps:
        step_count += 1
        if navigator.is_target_reached(current_lat, current_lon):
            print(
                f"\nSimulation Complete: Target reached at step {step_count}."
            )
            break

        pitch_cmd, roll_cmd = navigator.update(
            current_lat,
            current_lon,
            FIXED_DRONE_HEADING_DEGREES,
            dt_external=dt_sim_update
        )

        if step_count % 50 == 0:  # Print status periodically
            dist = haversine(
                current_lat, current_lon, TARGET_LATITUDE, TARGET_LONGITUDE)
            print(f"Step {step_count}: Dist={dist:.2f}m -> "
                  f"Pitch={pitch_cmd:.2f}°, Roll={roll_cmd:.2f}°")

        # --- Kinematic Simulation with Fixed Yaw ---
        speed_fwd = (pitch_cmd / MAX_PITCH_CMD_DEGREES) * MAX_SPEED_FORWARD_MPS
        speed_strafe = (roll_cmd/MAX_ROLL_CMD_DEGREES) * MAX_SPEED_STRAFE_MPS

        dist_fwd = speed_fwd * dt_sim_update
        dist_strafe = speed_strafe * dt_sim_update

        heading_rad = math.radians(FIXED_DRONE_HEADING_DEGREES)

        # Decompose movements into North and East components.
        delta_n = (dist_fwd*math.cos(heading_rad)) - \
                  (dist_strafe*math.sin(heading_rad))
        delta_e = (dist_fwd*math.sin(heading_rad)) + \
                  (dist_strafe*math.cos(heading_rad))

        # Update position.
        current_lat += delta_n / 111000.0
        current_lon += delta_e / \
            (111000.0 * math.cos(math.radians(current_lat)))

        path_lats.append(current_lat)
        path_lons.append(current_lon)
    else:  # This block runs if the while loop finishes without a 'break'
        dist_final = haversine(
            current_lat, current_lon, TARGET_LATITUDE, TARGET_LONGITUDE)
        print(f"\nSimulation Incomplete: Max steps ({max_simulation_steps}) "
              f"reached. Final distance: {dist_final:.2f}m")

    # --- Plotting the Results ---
    plt.figure(figsize=(10, 8))
    plt.plot(path_lons, path_lats, marker='.', linestyle='-', color='blue',
             label='Drone Path', markersize=3, linewidth=1)
    plt.plot(INITIAL_LON, INITIAL_LAT, 'go', markersize=8,
             label=f'Start ({INITIAL_LAT:.4f}, {INITIAL_LON:.4f})')
    plt.plot(TARGET_LONGITUDE, TARGET_LATITUDE, 'rx', markersize=10, mew=2,
             label=f'Target ({TARGET_LATITUDE:.4f}, {TARGET_LONGITUDE:.4f})')

    plt.text(INITIAL_LON, INITIAL_LAT, ' Start',
             verticalalignment='bottom', horizontalalignment='right')
    plt.text(TARGET_LONGITUDE, TARGET_LATITUDE, ' Target',
             verticalalignment='bottom', horizontalalignment='left')

    # Plot drone's fixed heading direction from start point.
    arrow_len_deg = 0.0005
    plt.arrow(
        INITIAL_LON, INITIAL_LAT,
        arrow_len_deg * math.sin(math.radians(FIXED_DRONE_HEADING_DEGREES)),
        arrow_len_deg * math.cos(math.radians(FIXED_DRONE_HEADING_DEGREES)),
        head_width=0.0001, head_length=0.00015, fc='black', ec='black',
        label=f'Fixed Heading ({FIXED_DRONE_HEADING_DEGREES:.2f}°)'
    )

    plt.xlabel("Longitude (degrees)")
    plt.ylabel("Latitude (degrees)")
    plt.title(
        f"Drone Navigation (Fixed Yaw: "
        f"{FIXED_DRONE_HEADING_DEGREES:.2f}°)"
    )
    plt.legend()
    plt.grid(True)
    plt.axis('equal')

    # Auto-adjust plot limits with padding
    lon_min, lon_max = min(path_lons), max(path_lons)
    lat_min, lat_max = min(path_lats), max(path_lats)
    lon_pad = (lon_max - lon_min) * 0.15
    lat_pad = (lat_max - lat_min) * 0.15
    plt.xlim(lon_min - lon_pad, lon_max + lon_pad)
    plt.ylim(lat_min - lat_pad, lat_max + lat_pad)

    plt.show()
