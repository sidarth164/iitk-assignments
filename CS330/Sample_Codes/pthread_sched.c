#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 1000000000

int *a, num_threads;
unsigned long long *private_sum;

void *solver (void *param)
{
	int i, id = *(int*)(param), j;
	private_sum[id] = 0;
	
        if (num_threads == 2) {
           for (i=SIZE/2; i<SIZE; i++) {
                private_sum[id] += a[i];
           }
        }
        else {
           j = (SIZE/num_threads)*(id+1);
           for (i=(SIZE/num_threads)*id; i<j; i++) {
                private_sum[id] += a[i];
           }
        }
}	

int main (int argc, char *argv[])
{
	int i, j, *tid, sched_scope, sched_policy;
	pthread_t *threads;
	pthread_attr_t attr;
	struct sched_param param;
        struct timeval tp_start, tp_end;
        unsigned long long sum=0;

	if (argc != 2) {
		printf ("Need number of threads.\n");
		exit(1);
	}
	num_threads = atoi(argv[1]);
	threads = (pthread_t*)malloc(num_threads*sizeof(pthread_t));
	private_sum = (unsigned long long*)malloc(num_threads*sizeof(unsigned long long));
        tid = (int*)malloc(num_threads*sizeof(int));
        for (i=0; i<num_threads; i++) tid[i] = i;

        a = (int*)malloc(SIZE*sizeof(int));
        for (i=0; i<SIZE; i++) a[i] = i;

	pthread_attr_init(&attr);

	if (pthread_attr_getscope(&attr, &sched_scope) != 0) {
       		fprintf(stderr, "Unable to get scheduling scope.\n");
	}
	else if (sched_scope == PTHREAD_SCOPE_PROCESS) {
		printf("Current scope is SCOPE_PROCESS.\n");
	}
	else if (sched_scope == PTHREAD_SCOPE_SYSTEM) {
		printf("Current scope is SCOPE_SYSTEM.\n");
	}
	else {
		fprintf(stderr, "Unable to decipher the current scope.\n");
	}

	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

	if (pthread_attr_getschedpolicy(&attr, &sched_policy) != 0) {
		fprintf(stderr, "Unable to get scheduling policy.\n");
	}
	else if (sched_policy == SCHED_OTHER) {
		printf("Default scheduling policy.\n");
	}
	else if (sched_policy == SCHED_RR) {
		printf("Round-robin scheduling policy.\n");
	}
	else if (sched_policy == SCHED_FIFO) {
		printf("First-in-first-out scheduling policy.\n");
	}
	else {
		fprintf(stderr, "Unable to decipher the current scheduling policy.\n");
	}

	if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
		fprintf(stderr, "Unable to set scheduling policy.\n");
	}
	else {
		printf("Scheduling policy is set to SCHED_FIFO.\n");
	}

	if (pthread_attr_getschedparam(&attr, &param) != 0) {
                fprintf(stderr, "Unable to get scheduling parameters.\n");
        }
        else {
                printf("Current scheduling priority is %d\n", param.sched_priority);
        }

        gettimeofday(&tp_start, NULL);

	for (i=1; i<num_threads; i++) {
		pthread_create(&threads[i], &attr, solver, &tid[i]);
		param.sched_priority = (param.sched_priority+1)%100;
		if (pthread_attr_setschedparam(&attr, &param) != 0) {
			fprintf(stderr, "Unable to set scheduling priority.\n");
		}
   	}

        if (num_threads == 1) {
           for (i=0; i<SIZE; i++) {
                sum += a[i];
           }
        }
        else if (num_threads == 2) {
           for (i=0; i<SIZE/2; i++) {
                sum += a[i];
           }
        }
        else {
           j = SIZE/num_threads;
           for (i=0; i<j; i++) {
                sum += a[i];
           }
        }
	
	for (i=1; i<num_threads; i++) {
		pthread_join(threads[i], NULL);
		sum += private_sum[i];
	}

	printf("SUM: %llu\n", sum);
  
        gettimeofday(&tp_end, NULL);
        printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
	return 0;
}
