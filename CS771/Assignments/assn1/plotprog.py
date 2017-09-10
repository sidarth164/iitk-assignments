import matplotlib.pyplot as plt
from sklearn.datasets import load_svmlight_file
import numpy as np
import sys

def main():
	acc_data = np.genfromtxt("Accuracy.dat")
	Y = acc_data
	X = [1,2,3,5,10]
	plt.plot(X,Y,marker='o')
	plt.xlabel('k')
	plt.ylabel('Accuracy')
	plt.title('kNN Accuracy Plot')
	plt.xticks(np.arange(min(X), max(X)+1, 1.0))
	plt.show()
if __name__ == '__main__':
    main()    
    