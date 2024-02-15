import matplotlib.pyplot as plt

filename = 'battery_data.txt'
time_data, voltage_data, current_data, capacity_data = [], [], [], []

with open(filename, 'r') as file:
    for line in file:
        if line.startswith('Battery Voltage'):
            voltage_data.append(float(line.split()[3]))
        elif line.startswith('Current'):
            current_data.append(float(line.split()[1]))
        elif line.startswith('Capacity'):
            capacity_data.append(float(line.split()[1]))

# Generating time data based on the number of readings
time_data = [i * 10 for i in range(len(voltage_data))]

# Plotting
plt.figure(figsize=(12, 8))

# Battery Voltage
plt.subplot(3, 1, 1)
plt.plot(time_data, voltage_data, marker='o', linestyle='-', color='b')
plt.title('Battery Monitoring')
plt.ylabel('Battery Voltage (V)')
plt.grid(True)

# Current
plt.subplot(3, 1, 2)
plt.plot(time_data, current_data, marker='o', linestyle='-', color='r')
plt.ylabel('Current (mA)')
plt.grid(True)

# Capacity
plt.subplot(3, 1, 3)
plt.plot(time_data, capacity_data, marker='o', linestyle='-', color='g')
plt.xlabel('Time (s)')
plt.ylabel('Capacity (mAh)')
plt.grid(True)

plt.tight_layout()
plt.show()
