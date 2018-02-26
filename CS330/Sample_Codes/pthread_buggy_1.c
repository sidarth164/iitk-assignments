#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int num_threads, count, iter;

void *solver (void *param)
{
        int i;

        for (i=0; i<iter; i++) count=count+1;
}	

int main (int argc, char *argv[])
{
	int i, *tid;
	pthread_t *threads;
	pthread_attr_t attr;

	if (argc != 4) {
		printf ("Need number of threads, initial counter value, and the number of iterations.\n");
		exit(1);
	}
	num_threads = atoi(argv[1]);
        count = atoi(argv[2]);
        iter = atoi(argv[3]);
	threads = (pthread_t*)malloc(num_threads*sizeof(pthread_t));
        tid = (int*)malloc(num_threads*sizeof(int));
        for (i=0; i<num_threads; i++) tid[i] = i;

	pthread_attr_init(&attr);

	for (i=1; i<num_threads; i++) {
                /* pthread_create arguments: thread pointer,
                                             attribute pointer,
                                             function pointer,
                                             argument pointer to the function
                */
		pthread_create(&threads[i], &attr, solver, &tid[i]);
   	}
	
        for (i=0; i<iter; i++) count=count+1;

	for (i=1; i<num_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("COUNT: %d\n", count);

	return 0;
}
