import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('points.txt')

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(data[:,0], data[:,1], data[:,2], 
           c='red', s=50, alpha=0.7)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Points from points.txt')

plt.show()