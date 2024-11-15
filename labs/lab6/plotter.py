import numpy as np
import matplotlib.pyplot as plt

# Load data from the text files
data1 = np.loadtxt('merge_test.txt')
data2 = np.loadtxt('selection_test.txt')

# Split data into columns for the first dataset
x1 = data1[:, 0]  # First column
y1 = data1[:, 1]  # Second column

# Split data into columns for the second dataset
x2 = data2[:, 0]  # First column
y2 = data2[:, 1]  # Second column

# Create a subplot layout with 1 row and 2 columns
plt.figure(figsize=(12, 5))

# First plot (left)
plt.subplot(1, 2, 1)  # 1 row, 2 columns, position 1
plt.plot(x1, y1, marker='o')
plt.xlabel('Time')
plt.ylabel('Data Size')
plt.title('Merge Test Data Plot')
plt.grid(True)

# Second plot (right)
plt.subplot(1, 2, 2)  # 1 row, 2 columns, position 2
plt.plot(x2, y2, marker='o')
plt.xlabel('Time')
plt.ylabel('Data Size')
plt.title('Selection Test Data Plot')
plt.grid(True)

# Display both plots on one page
plt.tight_layout()
plt.show()
