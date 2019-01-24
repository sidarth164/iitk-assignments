#include<iostream>
#include<cstdio>
#include<cstdint>
#include<pthread.h>
#include<time.h>
#include<fstream>
#include<string>
using namespace std;
#define NUM_THREADS 2
ofstream OUTPUT;
pthread_mutex_t lock;
int shared_counter=0, limit;

void* thr_func(void* arg){
	int id = (intptr_t) arg;
	while(1){
		pthread_mutex_lock(&lock);
		if(shared_counter>limit){
			pthread_mutex_unlock(&lock);
			break;
		}
		if(shared_counter%2==1 && id==1){
			OUTPUT<<"Thread "<<id<<": "<<shared_counter<<endl;
			shared_counter++;
		}
		else if(shared_counter%2==0 && id==0){
			OUTPUT<<"Thread "<<id<<": "<<shared_counter<<endl;
			shared_counter++;
		}
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}

int main(int argc, char**argv){
	if(argc!=2){
		cerr<<"Please specify the limit of shared counter";
		exit(EXIT_FAILURE);
	}
	limit = atoi(argv[1]);
	OUTPUT.open("prob3.log", ios_base::out);
	int i;
	pthread_t tid[NUM_THREADS];
	int error;

	for(i=0;i<NUM_THREADS;i++){
		error = pthread_create(&tid[i], NULL, thr_func, (void*)(intptr_t)i);
		if(error){
			cerr<<"ERROR: return code from pthread_create() is "<<error<<endl;
			exit(EXIT_FAILURE);
		}
	}

	for(i=0;i<NUM_THREADS;i++)
		pthread_join(tid[i], NULL);
	
	OUTPUT.close();
	pthread_exit(NULL);

	return 0;
}
