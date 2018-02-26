import numpy as np
import matplotlib.pyplot as plt 
from scipy.optimize import curve_fit
from scipy.stats import norm
import matplotlib.mlab as mlab

f = open("on.txt");
a_x=[]
b_x=[]
a_y=[]
b_y=[]
for line in f:
	x = line.split(' ')
	#print(x[0])
	a_x.append(x[0])
	a_y.append(x[2].strip())
f.close()
plt.figure(0)
plt.plot(a_x, a_y, 'o', markersize=1)
plt.suptitle("Randomized Algorithm")
plt.xlabel("Number of points")
plt.ylabel("Time Taken")

random_coeff = np.polynomial.polynomial.polyfit(a_x,a_y,1)
b_fit = [random_coeff[0]+random_coeff[1]*b_x[i] for i in range(0,len(b_x))]

plt.figure(1)
plt.plot(a_x, b_fit, color='r', label="fitted line")
plt.legend()
plt.savefig("randomized",dpi=400)