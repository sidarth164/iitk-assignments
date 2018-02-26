#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main (void)
{
        char *buffer;
	int i, mmap_fd;

 	mmap_fd = open("something.txt", O_RDWR);
    	if (mmap_fd == -1) {
 		printf("Cannot open file!\nAborting...\n");
		exit(1);
	}

	buffer = (char*)mmap(NULL, sizeof(char)*1000, PROT_READ|PROT_WRITE, MAP_SHARED, mmap_fd, 0);
	if (buffer == MAP_FAILED) {
		printf("mmap failed!\nAborting...\n");
		exit(1);
	}

        for (i=0; i<100; i++) {
           printf("%c", buffer[i]);
        }
        printf("\n");

        for (i=0; i<10; i++) {
           buffer[i] = 'a'+i;
        }

	for (i=0; i<100; i++) {
           printf("%c", buffer[i]);
        }
        printf("\n");

	munmap(buffer, sizeof(char)*1000);
        close(mmap_fd);
	return 0;
}
