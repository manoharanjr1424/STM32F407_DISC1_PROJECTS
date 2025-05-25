import tkinter as tk
from tkinter import messagebox
import serial
import time
import serial.tools.list_ports

# Constants
START_BYTE = 0x81
STOP_BYTE = 0xA5

# Replace with your actual USB port (e.g., 'COM3' on Windows or '/dev/ttyUSB0' on Linux)
USB_PORT = '/dev/ttyUSB0'  # or '/dev/ttyUSB0'
BAUD_RATE = 9600

def send_to_usb():
    text = entry.get()
    if not text:
        messagebox.showwarning("Warning", "Text box is empty!")
        return

    try:
        with serial.Serial(USB_PORT, BAUD_RATE, timeout=1) as ser:
            ser.write(bytes([START_BYTE]))
            ser.write(text.encode('utf-8'))
            ser.write(bytes([STOP_BYTE]))
        messagebox.showinfo("Success", "CMD sent to USB!")
    except serial.SerialException as e:
        messagebox.showerror("Error", f"Failed to send CMD: {e}")

# GUI Setup
root = tk.Tk()
root.title("IO_EXPANDER CMD APPLICATION")

label = tk.Label(root, text="Enter CMD to Send via USB:")
label.pack(padx=10, pady=5)

label = tk.Label(root, text="Commands To send :")
label.pack(padx=10, pady=5)

label = tk.Label(root, text="To set the PORT INPUT: IOEXP_P<PORT>_PIN<PIN_NUMBER>_SET_INPUT")
label.pack(padx=0, pady=5)
label = tk.Label(root, text="To set the PORT OUTPUT: IOEXP_P<PORT>_PIN<PIN_NUMBER>_SET_OUTPUT")
label.pack(padx=0, pady=5)
label = tk.Label(root, text="To Write HIGH to Pin: IOEXP_P<PORT>_PIN<PIN_NUMBER>_WRITE_HIGH")
label.pack(padx=0, pady=5)
label = tk.Label(root, text="To Write LOW to Pin: IOEXP_P<PORT>_PIN<PIN_NUMBER>_WRITE_LOW")
label.pack(padx=0, pady=5)

label = tk.Label(root, text="Example : IOEXP_PA_PIN00_SET_INPUT, IOEXP_PA_PIN00_SET_OUTPUT, IOEXP_PA_PIN00_WRITE_HIGH, IOEXP_PA_PIN00_WRITE_LOW")
label.pack(padx=0, pady=20)

entry = tk.Entry(root, width=50)
entry.pack(padx=10, pady=5)

send_button = tk.Button(root, text="Send", command=send_to_usb)
send_button.pack(padx=10, pady=10)

root.mainloop()
