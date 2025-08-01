import serial
import serial.tools.list_ports


def flush_all_com_ports():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        try:
            with serial.Serial(port.device, timeout=0.5) as ser:
                ser.reset_input_buffer()
                ser.reset_output_buffer()
                print(f"Flushed {port.device}")
        except Exception as e:
            print(f"Could not flush {port.device}: {e}")


if __name__ == "__main__":
    flush_all_com_ports()
