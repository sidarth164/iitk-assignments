from sklearn.datasets import load_svmlight_file
import numpy as np
import sys

def checkacc(Yts,Yts_correct):
	wrong=0
	for i in range(Yts_correct.shape[0]):
		if(Yts[i]!=Yts_correct[i]):
			wrong=wrong+1
	acc=(Yts_correct.shape[0]-wrong)/Yts_correct.shape[0]
	return acc

def predict(Xtr, Ytr, Xts, k, metric=None):

    N, D = Xtr.shape

    assert N == Ytr.shape[0], "Number of samples don't match"
    assert D == Xts.shape[1], "Train and test dimensions don't match"

    if metric is None:
        metric = np.identity(D)

    Yts = np.zeros((Xts.shape[0], 1))

    for i in range(Xts.shape[0]):
        a=Xtr-Xts[i]
        LMNN_dist=[]
        mult=np.dot(a,metric)
        for x in range(Xtr.shape[0]):
            LMNN_dist.append(np.dot(a[x],mult[x]))
        LMNN_dist=np.array(LMNN_dist)
        indx=np.argpartition(LMNN_dist,k)[:k]
        (_, idx, counts) = np.unique(Ytr[indx], return_index=True, return_counts=True)
        index = idx[np.argmax(counts)]
        Yts[i]=Ytr[indx][index]
        print(i,Yts[i],k)

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
    Yts_correct=ts_data[1];
    # The test labels are useless for prediction. They are only used for evaluation

    # Load the learned metric
    metric = np.load("model.npy")

    ### Do soemthing (if required) ###
    
    acc=[]
    k=13
    
    Yts = predict(Xtr, Ytr, Xts, k, metric)
    acc=checkacc(Yts,Yts_correct)

    np.savetxt("Accuracy.dat",acc)

    # Save predictions to a file
	# Warning: do not change this file name
    # np.savetxt("testY.dat", Yts)

if __name__ == '__main__':
    main()
