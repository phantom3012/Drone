from env import generate_environment_inputs
from drone import Drone
import serial
import time
import threading
import matplotlib.pyplot as plt
import numpy as np
from gps import GPS
import sys

# --- Global debug variables ---
last_pitch_cmd = 0.0
last_roll_cmd = 0.0
last_sent_lat = 0.0
last_sent_lon = 0.0

# --- Import the Drone class from your model ---

# --- Simulation Parameters ---
COM_SEND = 'COM15'  # To microcontroller (GPS IN)
COM_RECV = 'COM7'   # From microcontroller (Pitch/Roll OUT)
BAUDRATE = 115200
dt = 1  # seconds per loop

# Initial drone state (lat, lon in degrees)
drone_lat = 43.0653950
drone_lon = -89.2803402
drone_heading = 0.0  # degrees

# Target position (lat, lon in degrees)
target_lat = 43.0660000
target_lon = -89.2795000

# For visualization
history_lat = [drone_lat]
history_lon = [drone_lon]

# --- Helper Functions ---


def calculate_checksum(sentence_body):
    """Calculates the NMEA checksum for the sentence body."""
    checksum = 0
    for char in sentence_body:
        checksum ^= ord(char)
    return f"{checksum:02X}"


def generate_gngll(lat, lon, valid=True):
    """Generate a $GNGLL NMEA sentence for given lat/lon."""
    ns = 'N' if lat >= 0 else 'S'
    ew = 'E' if lon >= 0 else 'W'
    lat_abs = abs(lat)
    lon_abs = abs(lon)
    lat_deg = int(lat_abs)
    lat_min = (lat_abs - lat_deg) * 60
    lat_str = f"{lat_deg:02d}{lat_min:07.4f}"
    lon_deg = int(lon_abs)
    lon_min = (lon_abs - lon_deg) * 60
    lon_str = f"{lon_deg:03d}{lon_min:07.4f}"
    utc = time.strftime("%H%M%S.00", time.gmtime())
    status = 'A' if valid else 'V'
    body = (f"GNGLL,{lat_str},{ns},{lon_str},{ew},{utc},"
            f"{status}")
    checksum = calculate_checksum(body)
    sentence = f"${body},{checksum}\r"
    return sentence


def setup_plot(start_lat, start_lon, target_lat, target_lon):
    fig, ax = plt.subplots(figsize=(10, 8))
    fig.subplots_adjust(left=0.12, right=0.95, top=0.80, bottom=0.1)
    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title("Drone Simulation (HIL)")
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')

    # Plot start and target
    ax.plot(start_lon, start_lat, 'go', label='Start')
    ax.plot(target_lon, target_lat, 'rx', markersize=10, label='Target')

    # Path line and current drone marker
    path_line, = ax.plot([start_lon], [start_lat], 'b-', label='Path')
    drone_marker, = ax.plot([start_lon], [start_lat], 'o', color='purple')

    # Legend outside plot
    handles, labels = ax.get_legend_handles_labels()
    fig.legend(handles, labels, loc='upper right', bbox_to_anchor=(0.98, 0.97))

    # Status/debug text box
    status_text = fig.text(
        0.02, 0.97, '', va='top', fontsize=9,
        bbox=dict(
            boxstyle='round,pad=0.5',
            fc='wheat',
            alpha=0.5
        )
    )
    return fig, ax, path_line, drone_marker, status_text


def plot_drone(history_lat, history_lon, target_lat, target_lon):
    plt.clf()
    plt.plot(history_lon, history_lat, 'b.-', label='Drone Path')
    plt.plot([target_lon], [target_lat], 'ro', label='Target')
    plt.xlabel('Longitude')
    plt.ylabel('Latitude')
    plt.title('Drone Navigation Simulation')
    plt.legend()
    plt.pause(0.01)


# --- Serial Communication Threads ---


def send_gps_thread(ser_send, get_state_func, stop_event):
    global last_sent_lat, last_sent_lon
    """Thread to send GPS strings to the microcontroller."""
    while not stop_event.is_set():
        lat, lon = get_state_func()
        last_sent_lat, last_sent_lon = lat, lon
        gps_str = generate_gngll(lat, lon)
        print(f"[COM15 SEND] {gps_str.strip()} (lat={lat:.7f}, lon={lon:.7f})")
        ser_send.write(gps_str.encode('ascii'))
        time.sleep(dt)


def recv_cmd_thread(ser_recv, cmd_queue, stop_event):
    global last_pitch_cmd, last_roll_cmd
    while not stop_event.is_set():
        try:
            ser_recv.write(bytes([0, 0, 0, 0, 4]))
            print("[COM7 SEND] 40000")
            line = ser_recv.readline().decode('ascii').strip()
            if line:
                print(f"[COM7 RECV] {line}")
            if line and line.startswith("PITCH:"):
                parts = line.split(',')
                pitch = float(parts[0].split(':')[1])
                roll = float(parts[1].split(':')[1])
                last_pitch_cmd, last_roll_cmd = pitch, roll
                print(f"[DEBUG] Pitch: {pitch:.2f}°, Roll: {roll:.2f}°")
                cmd_queue.append((pitch, roll))
            time.sleep(dt)
        except Exception:
            continue

# --- Main Simulation Loop ---


def main():
    global drone_lat, drone_lon, drone_heading
    ser_send = serial.Serial(COM_SEND, BAUDRATE, timeout=0.5)
    ser_recv = serial.Serial(COM_RECV, BAUDRATE, timeout=0.5)
    stop_event = threading.Event()
    cmd_queue = []

    drone = Drone(drone_lat, drone_lon, drone_heading)

    def get_state():
        return drone.get_position()

    # Only use setup_plot for plotting
    env_inputs = generate_environment_inputs()
    wind_model = env_inputs['wind_model']
    fig, ax, path_line, drone_marker, status_text = setup_plot(
        drone_lat, drone_lon, target_lat, target_lon
    )

    t_send = threading.Thread(target=send_gps_thread,
                              args=(ser_send, get_state, stop_event))
    t_recv = threading.Thread(target=recv_cmd_thread,
                              args=(ser_recv, cmd_queue, stop_event))
    t_send.start()
    t_recv.start()

    plt.ion()

    try:
        while True:
            wind_speed_mph, wind_bearing_deg = wind_model.update(dt)
            wind_angle_rad = np.deg2rad(wind_bearing_deg - drone.heading)
            head_wind_mph = wind_speed_mph * np.cos(wind_angle_rad)
            right_wind_mph = wind_speed_mph * np.sin(wind_angle_rad)

            if cmd_queue:
                pitch_cmd, roll_cmd = cmd_queue.pop(0)
            else:
                pitch_cmd, roll_cmd = 0.0, 0.0

            drone.update_physics(
                pitch_cmd, roll_cmd,
                head_wind_mph, right_wind_mph, dt
            )
            lat, lon = drone.get_position()
            history_lat.append(lat)
            history_lon.append(lon)

            path_line.set_data(history_lon, history_lat)
            drone_marker.set_data([lon], [lat])
            dist = GPS.haversine_distance(lat, lon, target_lat, target_lon)
            if dist < 2.0:
                print("Target reached!")
                break

            status_text.set_text(
                (
                    f'Pitch Cmd: {last_pitch_cmd:.2f}° | '
                    f'Roll Cmd: {last_roll_cmd:.2f}°\n'
                    f'Sent Lat: {last_sent_lat:.7f} | '
                    f'Sent Lon: {last_sent_lon:.7f}\n'
                    f'Distance to Target: {dist:.2f} m'
                )
            )

            plt.pause(dt)
    except KeyboardInterrupt:
        print("Simulation stopped.")
        stop_event.set()
        t_send.join()
        t_recv.join()
        ser_send.close()
        ser_recv.close()
        plt.ioff()
        plt.show()
        sys.exit(0)  # <-- This will terminate the whole program
    finally:
        pass


if __name__ == "__main__":
    main()
