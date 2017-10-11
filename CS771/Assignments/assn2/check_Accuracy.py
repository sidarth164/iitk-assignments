import numpy as np
from scipy.sparse import csr_matrix
import sys
from sklearn.datasets import load_svmlight_file
import random
from datetime import datetime
import math

def main():
	# Get training file name from the command line
	traindatafile = sys.argv[1];
	wfile = sys.argv[2];
	
	# The training file is in libSVM format
	tr_data = load_svmlight_file(traindatafile);

	Xtr = tr_data[0]; # Training features in sparse format
	Ytr = tr_data[1]; # Training labels

	# We have n data points each in d-dimensions
	n, d = Xtr.get_shape();
	
	# The labels are named 1 and 2 in the data set. Convert them to our standard -1 and 1 labels
	Ytr = 2*(Ytr - 1.5);
	Ytr = Ytr.astype(int);
	Xtr=Xtr.toarray();

	w=np.load(wfile);

	right=0;
	for i in range(n-1):
		temp = w.dot(Xtr[i].T);
		if(temp>=0):
			Y_obs=1;
		else:
			Y_obs=-1
		if(Ytr[i]==Y_obs):
			right=right+1;
	acc=right/n*100;
	print(acc);

if __name__ == '__main__':
    main()