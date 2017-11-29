#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

#define SIZE 1000000000

int main (void)
{
	int *a, i, mmap_fd;
	unsigned long long child_sum=0, parent_sum=0, *global_sum;
        struct timeval tp_start, tp_end;

 	mmap_fd = open("/dev/zero", O_RDWR);
    	if (mmap_fd == -1) {
 		printf("Cannot open /dev/zero!\nAborting...\n");
		exit(1);
	}

	global_sum = (unsigned long long*)mmap(NULL, sizeof(unsigned long long), PROT_READ|PROT_WRITE, MAP_SHARED, mmap_fd, 0);
	if (global_sum == MAP_FAILED) {
		printf("mmap failed!\nAborting...\n");
		exit(1);
	}

        a = (int*)malloc(SIZE*sizeof(int));
        for (i=0; i<SIZE; i++) a[i] = i;

        gettimeofday(&tp_start, NULL);

	if (fork() == 0) {
		// This is child
		for (i=0; i<SIZE/2; i++) child_sum += a[i];
		printf("Child saying: my sum is %llu\n", child_sum);
		*global_sum = child_sum;
        }
        else {
		for (i=SIZE/2; i<SIZE; i++) parent_sum += a[i];
		printf("Parent saying: my sum is %llu\n", parent_sum);
		wait(NULL);
                printf("Total sum: %llu\n", *global_sum+parent_sum);
                gettimeofday(&tp_end, NULL);
                printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
	}
	munmap(global_sum, sizeof(unsigned long long));
        close(mmap_fd);
	return 0;
}
