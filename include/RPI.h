#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

#define GPIO_BASE	0x3f200000
#define BSC1_BASE	0x3f804000
#define BLOCK_SIZE	4096

#define GPFSEL0 0
#define GPFSEL1 1
#define GPFSEL2 2
#define GPFSEL3 3
#define GPFSEL4 4
#define GPFSEL5 5

#define GPSET0	7
#define GPSET1	8

#define	GPCLR0	10
#define	GPCLR1	11

#define	GPLEV0	13
#define	GPLEV1	14

#define SDA1	2
#define	SCL1	3

#define I2C_C		0
#define I2C_STATUS	1
#define I2C_DLEN	2
#define I2C_ADDR	3
#define I2C_FIFO	4

#define DLEN_BYTE	1
#define	DLEN_WORD	2

#define I2C_TIMEOUT	10

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |= (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio + GPSET0)
#define GPIO_CLR *(gpio + GPCLR0)
#define	GPIO_READ(g) *(gpio + GPLEV0) &= (1<<(g))

static unsigned int *gpio;
static unsigned int *bsc1;
static int fd;

int my_init();
void my_uninit();
