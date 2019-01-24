#include <cstdint>
#include <iostream>
#include <pthread.h>
using namespace std;
#define NUM_THREADS 10

void *thr_func(void* thread_id) {
	uint32_t id = (intptr_t) thread_id;
	cout<< "Hello World from Thread " << id << "\n";
	pthread_exit(NULL);
}

int main(){
	pthread_t threads[NUM_THREADS];
	int errcode;
	uint32_t id;
	for(id=0;id<NUM_THREADS;id++){
		cout<<"In main: creating thread: "<<id<<endl;

		errcode = pthread_create(&threads[id], NULL, thr_func, (void*)(intptr_t)id);

		if(errcode) {
			cout<<"ERROR: return code from pthread_create() is "<<errcode<<endl;
			exit(EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);
}
