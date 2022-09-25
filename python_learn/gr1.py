import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


#fig = plt.figure()
#ax = Axes3D(fig)

u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
x = np.cos(u)*np.sin(v)
y = np.sin(u)*np.sin(v)
z = np.cos(v)

print(x)
print(y)

x = [1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144, 1, 4, 16, 36, 64, 144,]
y = [24, 24, 24, 24, 24, 24, 48, 48, 48, 48, 48, 48, 72, 72, 72, 72, 72, 72, 96, 96, 96, 96, 96, 96, 120, 120, 120, 120, 120, 120, 144, 144, 144, 144, 144, 144, 168, 168, 168, 168, 168, 168, 192, 192, 192, 192, 192, 192, 216, 216, 216, 216, 216, 216, 240, 240, 240, 240, 240, 240]
z = [7.407, 7.503, 7.887, 8.966, 11.018, 	12.704,
7.642,	7.675,	8.137,	9.066,  11.048,	12.840,
7.817,	7.670,	8.078,	8.980,	11.157,	12.788,
8.231,	7.807,	8.142,	9.051,	10.976,	12.881,
8.943,	7.984,	8.248,	9.058,	11.256,	13.055,
10.024,	8.589,	8.209,	9.829,	11.004,	12.997,
11.440,	8.618,	8.623,	9.618,	11.744,	13.148,
13.466,	9.187,	8.808,	9.565,	11.685,	13.406,
15.912,	9.771,	9.006,	9.915,	12.428,	14.438,
18.880,	10.528,	10.492,	10.087,	12.544,	21.251]

#ax.scatter(x, y, z, c='red')
