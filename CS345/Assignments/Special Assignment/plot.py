import numpy as np
import matplotlib.pyplot as plt 
from scipy.optimize import curve_fit
from scipy.stats import norm
import matplotlib.mlab as mlab


# f1 = open("brute.txt", "r")
# f2 = open("randomized.txt", "r")
# f3 = open("randomized_distribution.txt", "r")
f4 = open("distribution.txt", "r")

# a_x=[]
# b_x=[]
# a_y=[]
# b_y=[]
# c=[]
d=[]
# for line in f1:
#     x = line.split(' ')
#     a_x.append(int(x[0]))
#     a_y.append(float(x[1].strip()))
# for line in f2:
#     x,y = line.split(' ')
#     b_x.append(int(x))
#     b_y.append(float(y.strip()))
# for line in f3:
#     c.append(float(line))
for line in f4:
    d.append(float(line))
# f1.close()
# f2.close()
# f3.close()
f4.close()

# plt.figure(0)
# plt.scatter(a_x, a_y, s=1)
# plt.suptitle("Brute Force Algorithm")
# plt.xlabel("Number of points")
# plt.ylabel("Time Taken")


# plt.figure(1)
# plt.plot(b_x, b_y, 'o', markersize=1)
# plt.suptitle("Randomized Algorithm")
# plt.xlabel("Number of points")
# plt.ylabel("Time Taken")

# brute_coeff = np.polynomial.polynomial.polyfit(a_x,a_y,4)
# random_coeff = np.polynomial.polynomial.polyfit(b_x,b_y,1)
# b_fit = [random_coeff[0]+random_coeff[1]*b_x[i] for i in range(0,len(b_x))]
# a_fit = [brute_coeff[0]+brute_coeff[1]*(a_x[i])+brute_coeff[2]*(a_x[i]**2)+brute_coeff[3]*(a_x[i]**3)+brute_coeff[4]*(a_x[i]**4) for i in range(0,len(a_x))]

# plt.figure(1)
# plt.plot(b_x, b_fit, color='r', label="fitted line")
# plt.legend()
# plt.savefig("randomized",dpi=400)


# plt.figure(0)
# plt.plot(a_x, a_fit, color='r' , label="fitted curve: O(x^4)")
# plt.legend()
# plt.savefig("Brute",dpi=400)

# plt.figure(3)
# c= np.array(c)
# mu, sigma = norm.fit(c)
# n, bins, patches = plt.hist(c, 100, normed=1, facecolor='green', alpha=0.75)
# y = mlab.normpdf( bins, mu, sigma)
# l = plt.plot(bins, y, 'r--', linewidth=2)
# plt.suptitle("Frequency of running time for n = 1000")
# plt.xlabel("Running time")
# plt.xticks(rotation=90, size=4)
# plt.yticks( size=4)
# plt.ylabel("Frequency")
# plt.grid(True)
# plt.legend()
# plt.savefig("randomized_distribution", dpi=400)

#plt.figure(4)
# d= np.array(d)
# mu, sigma = norm.fit(d)
n, bins, patches = plt.hist(d, 100, normed=1, facecolor='green', alpha=0.9)
# y = mlab.normpdf( bins, mu, sigma)
# l = plt.plot(bins, y, 'r--', linewidth=2)
plt.suptitle("Frequency of running time for n = 10000")
plt.xlabel("Running time")
plt.xticks(rotation=90, size=4)
plt.yticks( size=4)
plt.ylabel("Frequency")
plt.grid(True)
plt.legend()
plt.savefig("randomized_distribution_5000", dpi=400)
