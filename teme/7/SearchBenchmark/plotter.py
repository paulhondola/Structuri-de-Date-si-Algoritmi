import os
import numpy as np
import matplotlib.pyplot as plt

# Get the current working directory
current_dir = os.getcwd()

# Full paths to the benchmark files in the current directory
linear_benchmark_path = os.path.join(current_dir, 'cmake-build-debug', 'linear_benchmark.txt')
binary_benchmark_path = os.path.join(current_dir, 'cmake-build-debug', 'binary_benchmark.txt')
interpolation_benchmark_path = os.path.join(current_dir, 'cmake-build-debug', 'interpolation_benchmark.txt')

# Load data from the text files
data1 = np.loadtxt(linear_benchmark_path)
data2 = np.loadtxt(binary_benchmark_path)
data3 = np.loadtxt(interpolation_benchmark_path)

# Split data into columns for each dataset
x1, y1 = data1[:, 0], data1[:, 1]  # Linear benchmark
x2, y2 = data2[:, 0], data2[:, 1]  # Binary benchmark
x3, y3 = data3[:, 0], data3[:, 1]  # Interpolation benchmark

# Create a single plot
plt.figure(figsize=(10, 6))  # Adjust figure size

# Plot each dataset with different colors and labels
plt.plot(x1, y1, marker='o', color='blue', label='Linear Benchmark')
plt.plot(x2, y2, marker='s', color='green', label='Binary Benchmark')
plt.plot(x3, y3, marker='^', color='red', label='Interpolation Benchmark')

# Add labels, title, and legend
plt.xlabel('Time')
plt.ylabel('Data Size')
plt.title('Benchmark Comparisons')
plt.legend()  # Add a legend to differentiate the lines
plt.grid(True)  # Add grid lines for better visualization

# Display the plot
plt.tight_layout()
plt.show()