import math
import matplotlib.pyplot as plt
import numpy as np

x = []
y = []

fo = open("data.txt","r")
size = 99
for i in range(size):
    line_split = fo.readline().split(",")
    x.append(line_split[0])
    y.append(line_split[1])

plt.plot(x, y, label = 'Time Complexity')

plt.xlabel('Number of Vertices')
plt.ylabel('Time')
plt.title('Graph: Dijkstra')
plt.grid(True)
plt.legend()
plt.show()
