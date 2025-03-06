import matplotlib.pyplot as plt
import numpy as np

# Data from the tables
distances = [90, 180, 270, 300]
sent_packets = [1000, 1001, 1000, 1000]
received_packets = [974, 970, 748, 217]
rssi_values = [-70.96, -88.53, -95.87, -99.05]

# Create figure and axis
fig, ax1 = plt.subplots(figsize=(8, 5))

# Bar plot for packet counts
width = 20  # Bar width
ax1.bar(np.array(distances) - width/2, sent_packets, width, label="Sent Packets", color='blue', alpha=0.6)
ax1.bar(np.array(distances) + width/2, received_packets, width, label="Received Packets", color='green', alpha=0.6)
ax1.set_xlabel("Distance (m)")
ax1.set_ylabel("Packet Count")
ax1.set_title("Packet Counts and RSSI at Different Distances")
ax1.legend(loc="upper left")

# Line plot for RSSI values on secondary axis
ax2 = ax1.twinx()
ax2.plot(distances, rssi_values, marker="o", color="red", linestyle="-", label="RSSI (dBm)")
ax2.set_ylabel("RSSI (dBm)")
ax2.legend(loc="upper right")

# Show plot
plt.show()