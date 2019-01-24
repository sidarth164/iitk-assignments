#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define BIL 1000000000L

int main(int argc, char** argv){
	int n;
	char *path1, *path2;

	if(argc!=4){
		cerr<<"Please enter the number of elements in the arrays and the path to the files containing the arrays";
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]);
	path1 = argv[2];
	path2 = argv[3];
	
	int i=0, *array1, *array2;
	array1=(int*)malloc(n*sizeof(int));
	array2=(int*)malloc(n*sizeof(int));
	ifstream ARRAY1, ARRAY2;
	ARRAY1.open(path1);
	ARRAY2.open(path2);
	while(i<n && !ARRAY1.eof()){
		ARRAY1>>array1[i];
		i++;
	}
	i=0;
	while(i<n && !ARRAY2.eof()){
		ARRAY2>>array2[i];
		i++;
	}
	ARRAY1.close();
	ARRAY2.close();
	int nsim=0;
//	int *list_sim;
//	list_sim = (int *)malloc(n*n*sizeof(n));
	struct timespec start, stop;
	long double time;
	
	if( clock_gettime( CLOCK_REALTIME, &start) == -1){
		perror("Error in clocking the program");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if(array1[i]==array2[j]){
			//	list_sim[nsim++]=array1[i];
				nsim++;
			}
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1){
		perror("Error in clocking the program");
		exit(EXIT_FAILURE);
	} 

	time = (stop.tv_sec - start.tv_sec) + (long double) (stop.tv_nsec - start.tv_nsec) / BIL;
	
	cout<<"Execution time: "<<time<<"s"<<endl;
	cout<<"Number of similar elements: "<<nsim<<endl;
//	cout<<"List of similar elements:\n";
	/*
	for(i=0; i<nsim; i++)
		cout<<list_sim[i]<<endl;
	*/

	free(array1);
	free(array2);
//	free(list_sim);
	return 0;
}
