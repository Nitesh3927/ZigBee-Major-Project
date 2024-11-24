
from PyQt5.QtWidgets import (
    QMainWindow, QVBoxLayout, QHBoxLayout, QWidget, QPushButton, QTextEdit, QComboBox, QLabel, QMessageBox)

from PyQt5.QtCore import pyqtSlot
from Backend.serial_manager import SerialManager

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.serial_manager = SerialManager()
        
        self.setup_ui()
        self.setup_connections()

    def setup_ui(self):
        """Initialize the main layout and widgets."""
        self.setWindowTitle("COM Port Logger")
        self.setGeometry(100, 100, 800, 600)
        
        # Main layout
        main_layout = QVBoxLayout()
        
        # Add UI sections
        main_layout.addLayout(self.setup_controls())
        main_layout.addLayout(self.setup_display())
        main_layout.addLayout(self.setup_buttons())
        
        # Set layout in central widget
        container = QWidget()
        container.setLayout(main_layout)
        self.setCentralWidget(container)

    def setup_controls(self):
        """Create and return the control widgets layout."""
        # COM Port and Baud Rate selectors
        self.port_selector = QComboBox()
        self.port_selector.addItems(["COM1", "COM2", "COM3", "COM4", "COM5"])  # Example ports
        
        self.baud_rate_selector = QComboBox()
        self.baud_rate_selector.addItems(["9600", "19200", "38400", "57600", "115200"])

        # Control layout
        config_layout = QHBoxLayout()
        config_layout.addWidget(QLabel("COM Port:"))
        config_layout.addWidget(self.port_selector)
        config_layout.addWidget(QLabel("Baud Rate:"))
        config_layout.addWidget(self.baud_rate_selector)

        return config_layout

    def setup_display(self):
        """Create and return the display widgets layout."""
        # Live Data Display
        self.live_data_display = QTextEdit(self)
        self.live_data_display.setReadOnly(True)
        self.live_data_display.setPlaceholderText("Live Data from COM Port")
        
        # Logged Data Display
        self.logged_data_display = QTextEdit(self)
        self.logged_data_display.setReadOnly(True)
        self.logged_data_display.setPlaceholderText("Logged Data")

        # Display layout
        display_layout = QHBoxLayout()
        display_layout.addWidget(self.live_data_display)
        display_layout.addWidget(self.logged_data_display)

        return display_layout

    def setup_buttons(self):
        """Create and return the buttons layout."""
        # Start and Stop Buttons
        self.start_button = QPushButton("Start Logging")
        self.stop_button = QPushButton("Stop Logging")
        
        # Initially disable the Stop button
        self.stop_button.setEnabled(False)

        # Buttons layout
        button_layout = QHBoxLayout()
        button_layout.addWidget(self.start_button)
        button_layout.addWidget(self.stop_button)

        return button_layout

    def setup_connections(self):
        """Connect signals and slots."""
        self.start_button.clicked.connect(self.start_logging)
        self.stop_button.clicked.connect(self.stop_logging)
        self.serial_manager.new_data.connect(self.update_live_display)
        self.serial_manager.logged_data.connect(self.update_logged_display)

    @pyqtSlot()
    def start_logging(self):
        selected_port = self.port_selector.currentText()
        selected_baud_rate = int(self.baud_rate_selector.currentText())
        
        # Configure the SerialManager and attempt to start reading
        try:
            self.serial_manager.configure_port(selected_port, selected_baud_rate)
            self.serial_manager.start_reading()

            # Enable the Stop button and disable the Start button
            self.start_button.setEnabled(False)
            self.stop_button.setEnabled(True)
        except Exception as e:
            # Show error message if COM port is not found or unavailable
            self.show_error_message(f"Failed to connect to {selected_port}. Please check the connection and try again.")

    @pyqtSlot()
    def stop_logging(self):
        self.serial_manager.stop_reading()

        # Enable the Start button and disable the Stop button
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)

    @pyqtSlot(str)
    def update_live_display(self, data):
        self.live_data_display.append(data)

    @pyqtSlot(str)
    def update_logged_display(self, data):
        self.logged_data_display.append(data)

    def show_error_message(self, message):
        """Show an error message in a popup dialog."""
        msg_box = QMessageBox()
        msg_box.setIcon(QMessageBox.Critical)
        msg_box.setWindowTitle("Error")
        msg_box.setText(message)
        msg_box.exec_()
