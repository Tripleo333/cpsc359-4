#include "RPI.h"

int my_init() {
	if ((fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0) {
		printf("Failed to open /dev/mem, try checking permissions.\n");
		return 0;
	}
	gpio = (unsigned int *)mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
	if (gpio == MAP_FAILED) {
		perror("mmap");
		return 0;
	} else printf("mmap successful: %d\n", GPIO_BASE);
	
	bsc1 = (unsigned int *)mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, BSC1_BASE);
	if (bsc1 == MAP_FAILED) {
		perror("mmap");
		return 0;
	} else printf("mmap successful: %d\n", BSC1_BASE);
	return 1;
}

void my_uninit() {
	munmap(gpio, BLOCK_SIZE);
	munmap(bsc1, BLOCK_SIZE);
	close(fd);
}
