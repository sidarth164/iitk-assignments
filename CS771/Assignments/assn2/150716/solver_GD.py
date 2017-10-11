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
	# For how many iterations do we wish to execute GD?
	n_iter = int(sys.argv[2]);
	# After how many iterations do we want to timestamp?
	spacing = int(sys.argv[3]);
	
	# The training file is in libSVM format
	tr_data = load_svmlight_file(traindatafile);

	Xtr = tr_data[0]; # Training features in sparse format
	Ytr = tr_data[1]; # Training labels

	# We have n data points each in d-dimensions
	n, d = Xtr.get_shape();
	
	# The labels are named 1 and 2 in the data set. Convert them to our standard -1 and 1 labels
	Ytr = 2*(Ytr - 1.5);
	Ytr = Ytr.astype(int);
	#convert Ytr into csr matrix for calculatioins
	Ytr=csr_matrix(Ytr).T;
	
	# Optional: densify the features matrix.
	# Warning: will slow down computations
	#Xtr = Xtr.toarray();
	
	# Initialize model
	# For primal GD, you only need to maintain w
	# Note: if you have densified the Xt matrix then you can initialize w as a NumPy array
	w = csr_matrix((1, d));
	wbar = csr_matrix((1,d));
	
	# We will take a timestamp after every "spacing" iterations
	time_elapsed = np.zeros(math.ceil(n_iter/spacing));
	tick_vals = np.zeros(math.ceil(n_iter/spacing));
	obj_val = np.zeros(math.ceil(n_iter/spacing));
	obj_val_avg = np.zeros(math.ceil(n_iter/spacing));
	tick = 0;
	
	ttot = 0.0;
	t_start = datetime.now();
	grad = (Xtr.multiply(Ytr)).T;
	
	for t in range(n_iter):
		### Doing primal GD ###
		
		# Compute gradient
		ip=Xtr.dot(w.T);
		hinge=1-(Ytr.multiply(ip)).toarray();
		grmlt=np.sign(hinge);
		hinge=(hinge+hinge*grmlt)/2;
		grmlt=np.sign(hinge);
		#print(grmlt.shape);
		#print(grad.shape);
		g_corr=grad.T.multiply(grmlt);
		g_corr=g_corr.sum(axis=0);
		g=w-g_corr;
		#g.reshape(1,d); # Reshaping since model is a row vector
		
		# Calculate step lenght. Step length may depend on n and t
		eta = 2/pow(n,1) * 1/pow(t+1,0.5);
		
		# Update the model
		w = w - eta * g;
		
		# Use the averaged model if that works better (see [\textbf{SSBD}] section 14.3)
		wbar = (t * wbar + w)/(t+1);
		
		# Take a snapshot after every few iterations
		# Take snapshots after every spacing = 5 or 10 GD iterations since they are slow
		# if t%spacing == 0:
		# 	# Stop the timer - we want to take a snapshot
		# 	t_now = datetime.now();
		# 	delta = t_now - t_start;
		# 	time_elapsed[tick] = ttot + delta.total_seconds();
		# 	ttot = time_elapsed[tick];
		# 	tick_vals[tick] = tick;
		# 	obj_val[tick] = 0.5* w.dot(w.T) + hinge.sum(axis=0); # Calculate the objective value f(w) for the current model w^t or the current averaged model \bar{w}^t
		# 	print(delta.total_seconds(),obj_val[tick]);
		# 	obj_val_avg[tick] = 0.5* wbar.dot(wbar.T) + hinge.sum(axis=0);
		# 	tick = tick+1;
		# 	# Start the timer again - training time!
		# 	t_start = datetime.now();
		
	# Choose one of the two based on whichever works better for you
	#w_final = w;
	wbar_final = wbar;
	# np.save("model_GD.npy", w_final);
	np.save("model_GD.npy", wbar_final);
	# np.save("obj_val_GD.npy",obj_val);
	# np.save("obj_val_GD_avg.npy",obj_val_avg);
	# np.save("time_elapsed.npy",time_elapsed);
		
if __name__ == '__main__':
    main()
