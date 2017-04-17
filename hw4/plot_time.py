import math
import matplotlib.pyplot as plt
import numpy as np

x = []
y = []

fo = open("data_kruskal.txt","r")
size = 98
for i in range(size):
    line_split = fo.readline().split(",")
    x.append(line_split[0])
    y.append(line_split[1])

plt.plot(x, y, label = 'Time Complexity')

plt.xlabel('E')
plt.ylabel('Time')
plt.title('Graph: Kruskal')
plt.grid(True)
plt.legend()
plt.show()
