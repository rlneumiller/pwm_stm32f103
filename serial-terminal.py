import serial
import threading
import sys

def read_from_port(serial_port):
    while True:
        try:
            data = serial_port.read(serial_port.in_waiting or 1)
            if data:
                sys.stdout.write(data.decode('ascii', errors='replace'))
                sys.stdout.flush()
                
        except Exception as e:
            print(f"Error reading from serial port: {e}")
            break

def main():
    port = '/dev/ttyUSB0'  # Change this to your serial port
    baud_rate = 115200

    try:
        ser = serial.Serial(port, baud_rate, timeout=0, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE)
    except serial.SerialException as e:
        print(f"Could not open serial port {port}: {e}")
        return

    thread = threading.Thread(target=read_from_port, args=(ser,))
    thread.daemon = True
    thread.start()

    print(f"Connected to {port} at {baud_rate} baud. Press Ctrl+C to exit.")

    try:
        while True:
            user_input = input()
            ser.write((user_input + '\r\n').encode('ascii'))  # Ensure correct line ending
            ser.flush()  # Flush the output to ensure the command is sent
    except KeyboardInterrupt:
        print("Exiting...")
    finally:
        ser.close()

if __name__ == "__main__":
    main()