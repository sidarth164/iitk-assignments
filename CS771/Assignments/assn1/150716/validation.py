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
    	a**=2
    	euclid_dist=np.sum(a,axis=1)
    	indx=np.argpartition(euclid_dist,k)[:k]
    	(_, idx, counts) = np.unique(Ytr[indx], return_index=True, return_counts=True)
    	index = idx[np.argmax(counts)]
    	Yts[i]=Ytr[indx][index]
    	print(i,Yts[i],k)

    return Yts

def fold_split(X,Y,i):
    i = i*10000
    Xts = X[i:i+10000]
    Yts = Y[i:i+10000]
    Xtr=[]
    Ytr=[]
    for x in range(i):
        Xtr.append(X[x])
        Ytr.append(Y[x])
    for x in range(i+10000,60000):
        Xtr.append(X[x])
        Ytr.append(Y[x])
    Xtr=np.array(Xtr)
    Ytr=np.array(Ytr)
    return (Xtr,Ytr,Xts,Yts)

def main(): 

    # Get training and testing file names from the command line
    traindatafile = sys.argv[1]

    # The training file is in libSVM format
    tr_data = load_svmlight_file(traindatafile)

    X = tr_data[0].toarray();
    Y = tr_data[1];

    # The testing file is in libSVM format too
    #ts_data = load_svmlight_file(testdatafile)

    #Xts = ts_data[0].toarray();
    #Yts_correct=ts_data[1];
    # The test labels are useless for prediction. They are only used for evaluation

    # Load the learned metric
    #metric = np.load("model.npy")

    ### Do soemthing (if required) ###
    
    max_acc=0
    opt_k=0
    fold=6
    
    for k in range(1,21):
        acc=0
        for i in range(fold):
            (Xtr,Ytr,Xts,Yts_correct) = fold_split(X,Y,i)
            Yts = predict(Xtr, Ytr, Xts, k)
            acc+=checkacc(Yts,Yts_correct)
        acc = acc/6
        if(max_acc < acc):
            max_acc = acc
            opt_k=k

    print(opt_k)

    # Save predictions to a file
	# Warning: do not change this file name
    # np.savetxt("testY.dat", Yts)

if __name__ == '__main__':
    main()
