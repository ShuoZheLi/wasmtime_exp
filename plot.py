import matplotlib.pyplot as plt
import numpy as np

# Sample data (replace these with your actual data)
sizes = [128, 256, 512, 1024]
raw_times = [0.005, 0.033, 0.27, 3.08]

# 3.47514ms
# 25.629177ms
# 234.739475ms
# 2.666469511s
soft_times = [0.02, 0.1, 0.4, 1.6]


# 3.382487ms
# 30.773052ms
# 279.513876ms
# 2.319106363s
page_times = [0.2, 0.8, 3.2, 12.8]

# Create the plot
plt.figure(figsize=(10, 6))

# Plot each configuration
plt.plot(sizes, raw_times, marker='o', label='Raw')
plt.plot(sizes, soft_times, marker='o', label='Software')
plt.plot(sizes, page_times, marker='o', label='Page-Fault')

# Logarithmic scale for both axes
plt.xscale('log')
plt.yscale('log')

# Labels and title
plt.xlabel('SIZE')
plt.ylabel('TIME (s)')
plt.title('Performance Comparison Across Raw C, Page-Fault-Based, and Software-Based Bounds Checks')

# Add a legend
plt.legend()

# Show grid
plt.grid(True, which="both", linestyle='--', linewidth=0.5)

# Show the plot
plt.show()
