#include<iostream>
#include<cstdio>
#include<cstdint>
#include<pthread.h>
#include<time.h>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
#define BIL 1000000000L

int n, nthreads, *array;
pthread_barrier_t barrier;

void* thr_func(void* arguments){
	int id = (intptr_t) arguments, i, j;
	
	for(i=0; (1<<i+1)<=n; i++){
		for(j=id*(1<<i+1); j<=n-1; j+=(nthreads)*(1<<i+1)){
			int tmp = array[j-1+(1<<i+1)];
			array[j-1+(1<<i+1)]+=array[j-1+(1<<i)];
			array[j-1+(1<<i)]=tmp;
		}
		pthread_barrier_wait(&barrier);
	}
	
	i--;
	for(;i>=0;i--){
		for(j=id*(1<<i+1); j<=n-1; j+=(nthreads)*(1<<i+1)){
			array[j-1+(1<<i)]=array[j-1+(1<<i+1)]-array[j-1+(1<<i)];
		}
		pthread_barrier_wait(&barrier);
	}	
	
	pthread_exit(NULL);
}

int main(int argc, char** argv){
	char* path;
	if(argc!=4){
		perror("Please give the number of elements and the path to the file containing the array\n");
		exit(EXIT_FAILURE);
	}
	nthreads = atoi(argv[1]);
	n = atoi(argv[2]);
	path = argv[3];

	int i=0;
	array = (int*)malloc(n*sizeof(int));
	ifstream ARRAY;
	ARRAY.open(path);
	while(i<n && !ARRAY.eof()){
		ARRAY>>array[i];
		i++;
	}
	ARRAY.close();
	
	struct timespec start, stop;
	long double time;

	pthread_t tid[nthreads];
	int error;
	pthread_barrier_init(&barrier, NULL, nthreads);

	if( clock_gettime( CLOCK_REALTIME, &start) == -1){
		perror("Error in clocking the program");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<nthreads;i++){
		error = pthread_create(&tid[i], NULL, thr_func, (void*)(intptr_t)i);
		if(error){
			cerr<<"ERROR: return code from pthread_create() is "<<error<<endl;
			exit(EXIT_FAILURE);
		}
	}
	
	for(i=0; i<nthreads; i++){
		pthread_join(tid[i], NULL);
	}

	if( clock_gettime( CLOCK_REALTIME, &stop) == -1){
		perror("Error in clocking the program");
		exit(EXIT_FAILURE);
	} 

	pthread_barrier_destroy(&barrier);
	time = (stop.tv_sec - start.tv_sec) + (long double) (stop.tv_nsec - start.tv_nsec) / BIL;
	
	cout<<"Execution time: "<<time<<"s"<<endl;
	for(i=0;i<n;i++)
		cout<<array[i]<<endl;

	free(array);
	pthread_exit(NULL);
	return 0;
}
