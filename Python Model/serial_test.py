import serial
import time
import random
from sim_gps import generate_gngll

# Open serial ports
ser_out = serial.Serial('COM15', baudrate=115200, timeout=1)
ser_in = serial.Serial('COM7', baudrate=115200, timeout=1)

try:
    # Generate GPS string using sim_gps.py function
    gps_data = generate_gngll(random.choice([True, False]))
    print(f"Sending to COM15: {gps_data.strip()}")
    ser_out.write(gps_data.encode())

    time.sleep(0.5)  # Wait for response

    print("Received from COM7:")
    while True:
        response = ser_in.readline().decode(errors='ignore').strip()
        if not response:
            break
        print(response)

finally:
    ser_out.close()
