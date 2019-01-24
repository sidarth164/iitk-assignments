#include <cstdint>
#include <iostream>
#include <pthread.h>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define BIL 1000000000L
pthread_mutex_t lock;
int nsim=0, num_threads, n;
// int *list_sim;
struct thr_args{
	int id;
	int *array1;
	int *array2;
};

void *thr_func(void* arguments){
	struct thr_args *tmp = static_cast<struct thr_args*>(arguments);
	int*ar1 = tmp->array1;
	int*ar2 = tmp->array2;
	int i, j, id = tmp->id;
	for(i=id;i<n;i+=num_threads)
		for(j=0;j<n;j++)
			if(ar1[i]==ar2[j]){
				 pthread_mutex_lock(&lock);
			//	 list_sim[nsim++]=ar1[i];
				 nsim++;
				 pthread_mutex_unlock(&lock);
			}
	pthread_exit(NULL);
}

int main(int argc, char** argv){
	char *path1, *path2;

	if(argc!=5){
		cerr<<"Please enter the number of threads, number of elements in the arrays and the path to the files containing the arrays";
		exit(EXIT_FAILURE);
	}
	num_threads = atoi(argv[1]);
	n = atoi(argv[2]);
	path1 = argv[3];
	path2 = argv[4];
	
	int i=0,*array1,*array2;
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

//	list_sim = (int *)malloc(n*n*sizeof(n));
	struct timespec start, stop;
	long double time;

	//pthread declarations and initializations
	pthread_t tid[num_threads];
	int error;
	struct thr_args arg[num_threads] = {0};
	
	if( clock_gettime( CLOCK_REALTIME, &start) == -1){
		perror("Error in clocking the program");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<num_threads; i++){
		arg[i].id=i;
		arg[i].array1=array1;
		arg[i].array2=array2;
		error = pthread_create(&tid[i], NULL, thr_func, arg+i);

		if(error){
			cerr<<"ERROR: return code from pthread_create() is "<<error<<endl;
			exit(EXIT_FAILURE);
		}
	}
	
	for(i=0; i<num_threads; i++){
		pthread_join(tid[i], NULL);
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
	pthread_exit(NULL);
	return 0;
}
