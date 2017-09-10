from sklearn.datasets import load_svmlight_file
import numpy as np
import sys
def main():
    testdatafile='test.dat'
    ts_data = load_svmlight_file(testdatafile)
    Yts=ts_data[1]
    
    result='testm'+str(1)+'.dat'
    r_data=load_svmlight_file(result)
    Rtr=r_data[1]
    j=0
    for i in range(Yts.shape[0]):
        if(Yts[i]!=Rtr[i]):
            j=j+1
    accuracy=(Yts.shape[0]-j)/Yts.shape[0]
    print(accuracy)
if __name__ == '__main__':
    main()    
    
    