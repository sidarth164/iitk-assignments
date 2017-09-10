import numpy as np
import sys
from modshogun import LMNN, RealFeatures, MulticlassLabels
from sklearn.datasets import load_svmlight_file

def main(): 

    # Get training file name from the command line
    traindatafile = sys.argv[1]

	# The training file is in libSVM format
    tr_data = load_svmlight_file(traindatafile);

    Xtr = tr_data[0].toarray(); # Converts sparse matrices to dense
    Ytr = tr_data[1]; # The trainig labels
    
    Xtr=Xtr[0:10000]
    Ytr=Ytr[0:10000]
    # Cast data to Shogun format to work with LMNN
    features = RealFeatures(Xtr.T)
    labels = MulticlassLabels(Ytr.astype(np.float64))

    print("Running LMNN!!")
    ### Do magic stuff here to learn the best metric you can ###

    # Number of target neighbours per example - tune this using validation
    k = 13
    
    # Initialize the LMNN package
    lmnn = LMNN(features, labels, k)
    init_transform = np.eye(Xtr.shape[1])

    # Choose an appropriate timeout
    lmnn.set_maxiter(10000)
    lmnn.train(init_transform)

    # Let LMNN do its magic and return a linear transformation
	# corresponding to the Mahalanobis metric it has learnt
    L = lmnn.get_linear_transform()
    M = np.matrix(np.dot(L.T, L))

    # Save the model for use in testing phase
	# Warning: do not change this file name
    np.save("model.npy", M) 

if __name__ == '__main__':
    main()
