import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter
import sys

if len(sys.argv) < 3:
    print("Usage: python script.py <path_to_csv> <output_filename>")
    sys.exit(1)

# Retrieve command-line arguments
csv_file = sys.argv[1]
output_file = sys.argv[2]

# Read the CSV file into a pandas DataFrame
df = pd.read_csv(csv_file)

# Calculate mean and standard deviation of duration for each data_size
grouped = df.groupby('data_size (B)')['duration (ms)']
mean_duration = grouped.mean()
std_dev_duration = grouped.std()

# Create evenly spaced x-values
x_values = np.arange(len(mean_duration))

# Plotting with wider figure size
plt.figure(figsize=(12, 8), dpi=200)  # Width = 12 inches, Height = 6 inches

# Plot points with error bars
plt.errorbar(x_values, mean_duration, yerr=std_dev_duration, fmt='o', capsize=5, label='Mean Duration')

# Plot a line connecting the points
plt.plot(x_values, mean_duration, marker='o', linestyle='-', color='b', label='Line Through Points')

plt.xlabel('Data Size (B)')
plt.ylabel('Duration (ms)')
plt.title('Mean and Standard Deviation of Duration for Each Byte Size')

# Rotate x-axis labels vertically at the bottom
plt.xticks(x_values, mean_duration.index, rotation='vertical', ha='center')

plt.grid(True)
plt.tight_layout()
plt.legend()

# Save plot to a PNG file
plt.savefig(output_file)
