import serial
import threading
import tkinter as tk
from tkinter import scrolledtext
import time
import os
from datetime import datetime

# Function to generate a unique log file name using timestamp
def generate_log_filename(port):
    timestamp = datetime.now().strftime("%H%M%S")
    return f"{port}_log_{timestamp}.txt"

# Function to log and display serial data for each COM port
def log_serial_data(port, baud_rate, text_widget, stop_event):
    log_filename = generate_log_filename(port)
    try:
        with serial.Serial(port, baud_rate, timeout=1) as ser, open(log_filename, 'w') as log_file:
            print(f"Logging data from {port} to {log_filename}...")
            while not stop_event.is_set():
                data = ser.readline()
                if data:
                    decoded_data = data.decode('utf-8', errors='ignore')
                    text_widget.insert(tk.END, f"{decoded_data}\n")
                    text_widget.yview(tk.END)  # Scroll to the latest data
                    log_file.write(decoded_data + "\n")
                    log_file.flush()  # Ensure data is written to the file immediately
                time.sleep(0.1)
            text_widget.insert(tk.END, f"Stopped logging {port}\n")
    except serial.SerialException as e:
        text_widget.insert(tk.END, f"Error with {port}: {e}\n")
    except Exception as e:
        text_widget.insert(tk.END, f"Unexpected error with {port}: {e}\n")

# Function to start logging
def start_logging():
    global stop_events  # Make the stop events global so they can be accessed by the stop button
    baud_rate = int(baud_rate_entry.get())
    stop_events = {}  # Dictionary to store threading events for each port
    
    for port, text_widget in com_ports.items():
        stop_event = threading.Event()
        stop_events[port] = stop_event
        thread = threading.Thread(target=log_serial_data, args=(port, baud_rate, text_widget, stop_event))
        thread.daemon = True
        thread.start()

# Function to stop logging
def stop_logging():
    for port, stop_event in stop_events.items():
        stop_event.set()  # Signal the thread to stop
        com_ports[port].insert(tk.END, f"Saving log for {port} and stopping...\n")
    stop_events.clear()  # Clear stop events after stopping

# Create the main application window
root = tk.Tk()
root.title("Serial Data Logger")

# Set up a frame for the COM port configuration
config_frame = tk.Frame(root)
config_frame.pack(pady=10)

tk.Label(config_frame, text="Baud Rate:").grid(row=0, column=0, padx=5, pady=5)
baud_rate_entry = tk.Entry(config_frame)
baud_rate_entry.grid(row=0, column=1, padx=5, pady=5)
baud_rate_entry.insert(tk.END, "115200")  # Default baud rate

# Create a frame for holding the COM ports side by side
com_ports_frame = tk.Frame(root)
com_ports_frame.pack(pady=10)

# Define the COM ports and corresponding text widgets for displaying data
com_ports = {}
available_ports = ['COM4', 'COM5']  # List of COM ports to check

# Create text boxes for each available COM port
for port in available_ports:
    text_widget = scrolledtext.ScrolledText(com_ports_frame, width=50, height=10)
    text_widget.grid(row=0, column=available_ports.index(port), padx=10)
    com_ports[port] = text_widget
    tk.Label(com_ports_frame, text=f"Data from {port}:").grid(row=1, column=available_ports.index(port))

# Button to start logging
start_button = tk.Button(root, text="Start Logging", command=start_logging)
start_button.pack(pady=10)

# Button to stop logging
stop_button = tk.Button(root, text="Stop Logging", command=stop_logging)
stop_button.pack(pady=10)

# Run the GUI loop
root.mainloop()
