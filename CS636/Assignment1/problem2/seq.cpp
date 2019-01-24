#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<string>
using namespace std;
#define BIL 1000000000L

int main(int argc, char** argv){
	int n;
	char* path;
	if(argc!=3){
		perror("Please give the number of elements and the path to the file containing the array\n");
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]);
	path = argv[2];

	int i=0, *array;
	array=(int*)malloc(n*sizeof(int));
	ifstream ARRAY;
	ARRAY.open(path);
	while(i<n && !ARRAY.eof())
		ARRAY>>array[i++];
	ARRAY.close();
	
	struct timespec start, stop;
	long double time;
	
	if( clock_gettime( CLOCK_REALTIME, &start) == -1){
		perror("Error in clocking the program");
		exit(EXIT_FAILURE);
	}

	for(i=1;i<n;i++)
		array[i]=array[i-1]+array[i];

	if( clock_gettime( CLOCK_REALTIME, &stop) == -1){
		perror("Error in clocking the program");
		exit(EXIT_FAILURE);
	} 
	

	time = (stop.tv_sec - start.tv_sec) + (long double) (stop.tv_nsec - start.tv_nsec) / BIL;
	
	cout<<"Execution time: "<<time<<"s"<<endl;
	for(i=0;i<n;i++)
		cout<<array[i]<<endl;
	
	free(array);
	return 0;
}
