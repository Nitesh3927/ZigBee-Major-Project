import serial
import csv
from PyQt5.QtCore import QObject, QThread, pyqtSignal

class SerialManager(QObject):
    new_data = pyqtSignal(str)
    logged_data = pyqtSignal(str)

    def __init__(self):
        super().__init__()
        self.port = 'COM3'
        self.baudrate = 9600
        self.serial_connection = None
        self.reading = False
        self.inner_thread = None

    def configure_port(self, port, baudrate):
        self.port = port
        self.baudrate = baudrate

    def start_reading(self):
        if self.inner_thread is None:
            self.inner_thread = QThread()
            self.moveToThread(self.inner_thread)
            self.inner_thread.started.connect(self._read_from_com_port)
            self.inner_thread.start()

    def _read_from_com_port(self):
        self.serial_connection = serial.Serial(self.port, self.baudrate, timeout=1)
        self.reading = True

        while self.reading:
            if self.serial_connection.in_waiting > 0:
                line = str(self.serial_connection.readline().strip())
                self.new_data.emit(line)
                self.log_data(line)

    def stop_reading(self):
        self.reading = False
        if self.serial_connection and self.serial_connection.is_open:
            self.serial_connection.close()
        if self.inner_thread:
            self.inner_thread.quit()
            self.inner_thread.wait()
            self.inner_thread = None

    def log_data(self, data):
        with open('log.txt', mode='a', newline='') as file:
            file.write(str(data)+"/n")          
            # writer = csv.writer(file)
            # writer.writerow([data])
        
        # Emit signal to update the logged data display
        self.logged_data.emit(data)
