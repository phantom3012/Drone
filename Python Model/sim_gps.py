import random
from datetime import datetime, timezone
import serial
import time
import argparse


def calculate_checksum(sentence_body):
    """Calculates the NMEA checksum for the sentence body."""
    checksum = 0
    for char in sentence_body:
        checksum ^= ord(char)
    return f"{checksum:02X}"


def generate_gngll(valid=True):
    """
    Generate a single $GNGLL NMEA sentence (valid or invalid).
    $GNGLL,<lat>,<N/S>,<lon>,<E/W>,<hhmmss.ss>,<status>,<number>
    """
    now = datetime.now(timezone.utc)
    # Format the time with two decimal places for seconds (centiseconds)
    utc = now.strftime("%H%M%S.") + f"{now.microsecond // 10000:02d}"

    if valid:
        lat = random.uniform(43.065, 43.066)
        lon = random.uniform(89.279, 89.281)
        ns = 'N'
        ew = 'W'
        lat_deg = int(lat)
        lat_min = (lat - lat_deg) * 60
        lat_str = f"{lat_deg:02d}{lat_min:07.4f}"
        lon_deg = int(lon)
        lon_min = (lon - lon_deg) * 60
        lon_str = f"{lon_deg:03d}{lon_min:07.4f}"
        status = 'A'
    else:
        lat_str = ''
        ns = ''
        lon_str = ''
        ew = ''
        status = 'V'

    body = (f"GNGLL,{lat_str},{ns},{lon_str},{ew},{utc},"
            f"{status}")
    checksum = calculate_checksum(body)
    sentence = f"${body},{checksum}\r"

    return sentence


if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description=(
            "NMEA GPS Sentence Simulator. "
            "Sends $GNGLL sentences to a serial port."
        )
    )
    parser.add_argument(
        "port",
        help=(
            "Serial port name "
            "(e.g., COM15 or /dev/ttyUSB0)"
        )
    )
    parser.add_argument(
        "--baudrate",
        type=int,
        default=115200,
        help="Baud rate (default: 115200)"
    )
    parser.add_argument(
        "--interval",
        type=float,
        default=1.0,
        help="Time between messages in seconds (default: 1.0)"
    )
    args = parser.parse_args()

    ser = None
    try:
        ser = serial.Serial(args.port, args.baudrate, timeout=1)
        print(f"Successfully opened {args.port} at {args.baudrate} baud.")
        print("Press Ctrl+C to stop.")
        while True:
            # Randomly decide whether to send a valid or invalid message
            msg = generate_gngll(valid=random.choice([True, False]))
            print(f"Sending: {msg.strip()}")
            ser.write(msg.encode('ascii'))
            time.sleep(args.interval)
    except serial.SerialException as e:
        print(
            f"Error: Could not open or write to serial port {args.port}. "
            f"{e}"
        )
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        if ser and ser.is_open:
            ser.close()
            print(f"Closed port {args.port}.")
