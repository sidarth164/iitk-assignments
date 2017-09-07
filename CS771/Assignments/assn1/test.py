from sklearn.datasets import load_svmlight_file
import numpy as np
import sys

def predict(Xtr, Ytr, Xts, metric=None):

    N, D = Xtr.shape

    assert N == Ytr.shape[0], "Number of samples don't match"
    assert D == Xts.shape[1], "Train and test dimensions don't match"

    if metric is None:
        metric = np.identity(D)

    Yts = np.zeros((Xts.shape[0], 1))

    for i in range(Xts.shape[0]):
        '''
        Predict labels for test data using k-NN. Specify your tuned value of k here
        '''

    return Yts

def main(): 

    # Get training and testing file names from the command line
    traindatafile = sys.argv[1]
    testdatafile = sys.argv[2]

    # The training file is in libSVM format
    tr_data = load_svmlight_file(traindatafile)

    Xtr = tr_data[0].toarray();
    Ytr = tr_data[1];

    # The testing file is in libSVM format too
    ts_data = load_svmlight_file(testdatafile)

    Xts = ts_data[0].toarray();
    # The test labels are useless for prediction. They are only used for evaluation

    # Load the learned metric
    metric = np.load("model.npy")

    ### Do soemthing (if required) ###

    Yts = predict(Xtr, Ytr, Xts, metric)

    # Save predictions to a file
	# Warning: do not change this file name
    np.savetxt("testY.dat", Yts)

if __name__ == '__main__':
    main()
