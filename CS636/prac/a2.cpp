#include <cstdint>
#include <iostream>
#include <pthread.h>
using namespace std;
#define NUM_THREADS 10
uint32_t counter;
pthread_mutex_t count_mutex;
pthread_barrier_t my_barrier;
struct thr_args{
	uint16_t id;
};
void *thrBody(void* arguments){
	struct thr_args *tmp = static_cast<struct thr_args*>(arguments);
	pthread_mutex_lock(&count_mutex);
	for(uint32_t i=0; i<1000; i++){
		counter+=1;
	}
	pthread_mutex_unlock(&count_mutex);
	pthread_barrier_wait(&my_barrier);
	pthread_exit(NULL);
}

int main(){
	int i=0;
	int error;
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_barrier_init(&my_barrier, NULL, NUM_THREADS+1);
	struct thr_args args[NUM_THREADS] = {0};

	while(i<NUM_THREADS){
		args[i].id = i;
		error = pthread_create(&tid[i], &attr, thrBody, args+i);
		i++;
	}
	pthread_attr_destroy(&attr);
	pthread_barrier_wait(&my_barrier);
	
//	for(i=0;i<NUM_THREADS;i++){
//		pthread_join(tid[i],NULL);
//	}
	
	pthread_barrier_destroy(&my_barrier);
	cout<<"Value of Counter: "<<counter<<endl;
	pthread_exit(NULL);
	return 0;
}
