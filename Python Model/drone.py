import math
import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from env import generate_environment_inputs, Pilot
from gps import GPS
from mux import Mux
from virus import DroneNavigator

"""
Vector-based
Integrated
Responsive
Unmanned
System
"""
# --- Global Constants for Physics ---
DRONE_MASS_KG = 0.350  # 350 grams
GRAVITY_MPS2 = 9.81
# K = 0.5 * rho * Cd * A. Assuming rho=1.225, Cd=1.0, A=0.0225m^2 (15cmx15cm)
K_DRAG_COEFFICIENT = 0.014  # Units: kg/m
MPH_TO_MPS = 0.44704


class Drone:
    """
    Simulates the drone's physical state and handles its movement based
    on control inputs and environmental factors.
    """

    def __init__(self, initial_lat, initial_lon, initial_heading):
        """
        Initializes the Drone's state.
        :param initial_lat: Starting latitude.
        :param initial_lon: Starting longitude.
        :param initial_heading: Starting heading in degrees. This is fixed.
        """
        self.position = {'lat': initial_lat, 'lon': initial_lon}
        self.heading = initial_heading  # Drone's orientation is fixed
        self.pitch = 0.0
        self.roll = 0.0
        self.mass_kg = DRONE_MASS_KG
        self.k_drag = K_DRAG_COEFFICIENT

        # Velocities in drone's body frame (m/s)
        self.velocity_fwd_mps = 0.0
        self.velocity_right_mps = 0.0

    def update_physics(self, pitch_cmd, roll_cmd,
                       head_wind_mph, right_wind_mph, dt):
        """
        Updates drone's state using force-based physics.
        Velocities and speeds are in m/s.
        :return: Tuple (current_fwd_ground_speed_mps,
                        current_right_ground_speed_mps).
        """
        self.pitch = pitch_cmd
        self.roll = roll_cmd

        # Convert wind from mph to m/s
        # head_wind_mph is magnitude of wind from front (always >= 0)
        # right_wind_mph is signed (+ve from right, -ve from left)
        head_wind_component_mps = head_wind_mph * MPH_TO_MPS
        right_wind_component_mps = right_wind_mph * MPH_TO_MPS

        weight_N = self.mass_kg * GRAVITY_MPS2

        # --- Calculate Forces ---
        # Propulsive forces based on user's formula
        thrust_fwd_N = math.sin(math.radians(self.pitch)) * weight_N
        thrust_right_N = math.sin(math.radians(self.roll)) * weight_N

        # Velocity of drone relative to air
        # Wind from front opposes positive drone velocity_fwd_mps
        v_relative_fwd_mps = self.velocity_fwd_mps + head_wind_component_mps
        # Wind from right opposes positive drone velocity_right_mps
        v_relative_right_mps = (self.velocity_right_mps +
                                right_wind_component_mps)

        # Drag forces (oppose relative air motion)
        drag_fwd_N = -math.copysign(1.0, v_relative_fwd_mps) * \
            self.k_drag * (v_relative_fwd_mps**2)
        drag_right_N = -math.copysign(1.0, v_relative_right_mps) * \
            self.k_drag * (v_relative_right_mps**2)

        net_force_fwd_N = thrust_fwd_N + drag_fwd_N
        net_force_right_N = thrust_right_N + drag_right_N

        # --- Integration Step 1: Acceleration to Velocity ---
        accel_fwd_mps2 = net_force_fwd_N / self.mass_kg
        accel_right_mps2 = net_force_right_N / self.mass_kg

        self.velocity_fwd_mps += accel_fwd_mps2 * dt
        self.velocity_right_mps += accel_right_mps2 * dt

        # --- Integration Step 2: Velocity to Position ---
        dist_fwd_m = self.velocity_fwd_mps * dt
        dist_strafe_m = self.velocity_right_mps * dt
        heading_rad = math.radians(self.heading)

        delta_n = ((dist_fwd_m * math.cos(heading_rad)) -
                   (dist_strafe_m * math.sin(heading_rad)))
        delta_e = ((dist_fwd_m * math.sin(heading_rad)) +
                   (dist_strafe_m * math.cos(heading_rad)))

        self.position['lat'] += delta_n / 111000.0
        self.position['lon'] += delta_e / (
            111000.0 * math.cos(math.radians(self.position['lat'])))

        return self.velocity_fwd_mps, self.velocity_right_mps

    def get_position(self):
        """Returns the current GPS position of the drone."""
        return self.position['lat'], self.position['lon']


def write_log_to_csv(log_data, filename="simulation_log.csv"):
    """
    Writes the collected simulation data to a CSV file.
    :param log_data: A list of dictionaries representing the log.
    :param filename: The name of the output CSV file.
    """
    if not log_data:
        print("No data to write to log.")
        return

    # Use the keys from the first dictionary as header
    headers = log_data[0].keys()
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=headers)
        writer.writeheader()
        writer.writerows(log_data)
    print(f"Simulation log saved to {filename}")

# --- Main Simulation Testbench ---


if __name__ == "__main__":
    # --- 1. Initialization ---
    gps_module = GPS()
    mux_module = Mux()
    env_static_inputs = generate_environment_inputs()

    TARGET_LAT, TARGET_LON = gps_module.get_target_coordinates()
    INITIAL_LAT, INITIAL_LON = gps_module.get_random_start_position(
        min_radius_meters=100,  # Updated min starting distance
        max_radius_meters=300   # Updated max starting distance
    )
    INITIAL_HEADING = env_static_inputs['initial_heading']

    # Get the dynamic wind model from the environment
    wind_model = env_static_inputs['wind_model']

    drone_sim = Drone(INITIAL_LAT, INITIAL_LON, INITIAL_HEADING)

    # Command Limits
    MAX_PITCH_CMD_DEGREES = 15.0
    MAX_ROLL_CMD_DEGREES = 15.0

    # Pass command limits to the pilot simulator
    pilot_sim = Pilot(max_pitch=MAX_PITCH_CMD_DEGREES,
                      max_roll=MAX_ROLL_CMD_DEGREES)

    # Autopilot (VIRUS) controller setup - Tuned for smoother control
    virus_controller = DroneNavigator(
        target_lat=TARGET_LAT, target_lon=TARGET_LON,
        kp_pitch=0.04, ki_pitch=0.003, kd_pitch=0.03,
        kp_roll=0.04, ki_roll=0.003, kd_roll=0.03,
        distance_threshold=5.0,  # Updated target reached threshold to 5m
        max_pitch_cmd=MAX_PITCH_CMD_DEGREES,
        max_roll_cmd=MAX_ROLL_CMD_DEGREES
    )

    # Slew Rate Limits (degrees per second)
    PITCH_SLEW_RATE_LIMIT = 4.0  # Reduced for smoother pitch transitions
    ROLL_SLEW_RATE_LIMIT = 4.0   # Reduced for smoother roll transitions

    # Old speed limits (MAX_SPEED_FORWARD_CMPS, MAX_SPEED_STRAFE_CMPS)
    # are no longer directly used by update_physics.

    # Simulation state variables
    path_lats, path_lons = [INITIAL_LAT], [INITIAL_LON]
    simulation_log = []  # To store data for CSV export
    total_step_count = 0
    autopilot_step_count = 0
    autopilot_on = False  # Start with autopilot OFF for testing
    # Initialize actual commands to match the pilot's initial state
    actual_pitch_cmd = pilot_sim.current_pitch
    actual_roll_cmd = pilot_sim.current_roll
    # Variables to store last pilot commands for display
    last_pilot_pitch = actual_pitch_cmd
    last_pilot_roll = actual_roll_cmd
    # Variables for dynamic wind, calculated each frame
    wind_speed_mph = 0.0
    wind_bearing_deg = 0.0
    head_wind_component_mph = 0.0
    right_wind_component_mph = 0.0
    final_fwd_speed, final_right_speed = 0.0, 0.0

    # --- 2. Plot Setup ---
    fig, ax = plt.subplots(figsize=(10, 8))
    # Adjust subplot parameters to create more space for the status text
    # and legend, preventing overlap with the plot area.
    fig.subplots_adjust(left=0.12, right=0.95, top=0.80, bottom=0.1)
    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title(f"Drone Simulation (Fixed Heading: {INITIAL_HEADING}°)")
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')

    # Set static plot limits to be appropriate for the small distance
    # Adjust plot span for larger starting distances
    plot_span_meters = 700.0  # Span of 700 meters for the plot
    lat_span_deg = plot_span_meters / 111000.0
    lon_span_deg = plot_span_meters / (
        111000.0 * math.cos(math.radians(TARGET_LAT)))
    ax.set_xlim(TARGET_LON - lon_span_deg / 2, TARGET_LON + lon_span_deg / 2)
    ax.set_ylim(TARGET_LAT - lat_span_deg / 2, TARGET_LAT + lat_span_deg / 2)

    ax.plot(INITIAL_LON, INITIAL_LAT, 'go', label='Start')
    ax.plot(TARGET_LON, TARGET_LAT, 'rx', markersize=10, label='Target')
    line, = ax.plot(path_lats, path_lons, 'b-', label='Path')
    drone_marker, = ax.plot(INITIAL_LON, INITIAL_LAT, 'o', color='purple')
    status_text = fig.text(0.02, 0.97, '', va='top', fontsize=9,
                           bbox=dict(boxstyle='round,pad=0.5', fc='wheat',
                                     alpha=0.5))
    handles, labels = ax.get_legend_handles_labels()
    fig.legend(handles, labels, loc='upper right', bbox_to_anchor=(0.98, 0.97))

    # --- 3. Animation Loop ---
    def init_animation():
        """Initializes the animated elements for a clean start."""
        line.set_data([], [])
        drone_marker.set_data([], [])
        status_text.set_text('')
        return line, drone_marker, status_text

    def animate(i):
        global total_step_count, autopilot_step_count, autopilot_on
        global final_fwd_speed, final_right_speed
        global actual_pitch_cmd, actual_roll_cmd
        global last_pilot_pitch, last_pilot_roll
        global wind_speed_mph, wind_bearing_deg
        global head_wind_component_mph, right_wind_component_mph

        total_step_count += 1
        dt = 0.1  # time delta

        # --- Update Dynamic Wind On-The-Go ---
        wind_speed_mph, wind_bearing_deg = wind_model.update(dt)
        wind_angle_diff = wind_bearing_deg - INITIAL_HEADING
        relative_wind_angle_rad = math.radians(wind_angle_diff)
        head_wind_component_mph = (
            wind_speed_mph * math.cos(relative_wind_angle_rad)
        )
        right_wind_component_mph = (
            wind_speed_mph * math.sin(relative_wind_angle_rad)
        )

        if not autopilot_on and total_step_count > 100:
            autopilot_on = True
            # Reset PID controllers for a smooth handover
            virus_controller.pitch_pid.reset()
            virus_controller.roll_pid.reset()

        current_lat, current_lon = drone_sim.get_position()
        virus_pitch, virus_roll, reached = virus_controller.update(
            current_lat, current_lon, drone_sim.heading, dt
        )
        pilot_pitch, pilot_roll = pilot_sim.update_commands(dt)
        if not autopilot_on:
            last_pilot_pitch = pilot_pitch
            last_pilot_roll = pilot_roll

        if reached:
            ani.event_source.stop()
            status_text.set_text(
                f'Target Reached!\n'
                f'Total Steps: {total_step_count}\n'
                f'Autopilot Steps: {autopilot_step_count}\n'
                f'Final Fwd Speed: {final_fwd_speed:.2f} cm/s\n'
                f'Final Right Speed: {final_right_speed:.2f} cm/s'
            )
            return line, drone_marker, status_text

        # Use the Mux to select the source of the commands
        mux_pitch, mux_roll = mux_module.select_commands(
            pilot_pitch, pilot_roll,
            virus_pitch, virus_roll,
            autopilot_on
        )

        # Apply commands based on the autopilot state
        # (instant vs. slew-limited)
        if autopilot_on:
            target_pitch, target_roll = mux_pitch, mux_roll
            max_pitch_change = PITCH_SLEW_RATE_LIMIT * dt
            max_roll_change = ROLL_SLEW_RATE_LIMIT * dt
            pitch_error = target_pitch - actual_pitch_cmd
            roll_error = target_roll - actual_roll_cmd
            pitch_change = max(-max_pitch_change,
                               min(pitch_error, max_pitch_change))
            roll_change = max(-max_roll_change,
                              min(roll_error, max_roll_change))
            actual_pitch_cmd += pitch_change
            actual_roll_cmd += roll_change
        else:
            # Autopilot is OFF: Respond instantly to the selected (pilot)
            # commands
            actual_pitch_cmd, actual_roll_cmd = mux_pitch, mux_roll

        # Update drone physics with the rate-limited commands and speed limits
        # Speeds returned are now in m/s
        fwd_speed_mps, right_speed_mps = drone_sim.update_physics(
            actual_pitch_cmd, actual_roll_cmd,
            head_wind_component_mph,   # Pass calculated headwind component
            right_wind_component_mph,  # Pass calculated rightwind component
            dt
        )
        final_fwd_speed, final_right_speed = fwd_speed_mps, right_speed_mps

        # Log data for this step
        log_entry = {
            "step": total_step_count,
            "autopilot_on": autopilot_on,
            "pilot_pitch_cmd": last_pilot_pitch,
            "pilot_roll_cmd": last_pilot_roll,
            "virus_pitch_cmd": virus_pitch,
            "virus_roll_cmd": virus_roll,
            "wind_speed_mph": wind_speed_mph,
            "wind_bearing_deg": wind_bearing_deg,
            "head_wind_component_mph": head_wind_component_mph,
            "right_wind_component_mph": right_wind_component_mph,
            "final_pitch_cmd": actual_pitch_cmd,
            "final_roll_cmd": actual_roll_cmd,
        }
        simulation_log.append(log_entry)

        new_lat, new_lon = drone_sim.get_position()
        path_lats.append(new_lat)
        path_lons.append(new_lon)
        line.set_data(path_lons, path_lats)
        drone_marker.set_data([new_lon], [new_lat])

        mode = "ON" if autopilot_on else "OFF"
        step_display = ""
        if autopilot_on:
            autopilot_step_count += 1
            step_display = f" | A/P Steps: {autopilot_step_count}"

        dist_now = GPS.haversine_distance(
            current_lat, current_lon, TARGET_LAT, TARGET_LON
        )
        status_text.set_text(
            f'Total Steps: {total_step_count} | '
            f'Autopilot: {mode}{step_display}\n'
            f'Wind: {wind_speed_mph:.1f} mph @ {wind_bearing_deg}°\n'
            f'Wind Comp: Head {head_wind_component_mph:.1f} mph | '
            f'Right {right_wind_component_mph:.1f} mph\n'
            f'Distance to Target: {dist_now:.2f} m\n'
            f'Fwd Speed: {fwd_speed_mps * 100:.2f} cm/s | '  # Display as cm/s
            f'Right Speed: {right_speed_mps * 100:.2f} cm/s\n'
            f'Actual Pitch: {actual_pitch_cmd:.2f}° | '
            f'Actual Roll: {actual_roll_cmd:.2f}°\n'
            f'Pilot Pitch: {last_pilot_pitch:.2f}° | '
            f'Pilot Roll: {last_pilot_roll:.2f}°'
        )
        # Ensure the animation artists are always returned
        return line, drone_marker, status_text

    # Set interval for a much faster animation
    ani = animation.FuncAnimation(
        fig, animate, init_func=init_animation, frames=None,
        interval=1, blit=False, repeat=False
    )
    plt.show()

    # --- 4. Post-Simulation: Save Log ---
    write_log_to_csv(simulation_log)
