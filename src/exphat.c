#include "RPI.h"

unsigned char i2c_read_byte_data(unsigned char dev_addr, unsigned char reg_addr);
unsigned short	i2c_read_word_data(unsigned char dev_addr, unsigned char reg_addr);
void i2c_write_byte_data(unsigned char dev_addr, unsigned char reg_addr, unsigned char value);

unsigned char i2c_read_byte_data(unsigned char dev_addr, unsigned char reg_addr) {
	int timeout = 0;
	bsc1[I2C_ADDR] = dev_addr;
	bsc1[I2C_DLEN] = DLEN_BYTE;
	bsc1[I2C_FIFO] = reg_addr;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1); // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7); // I2CEN, ST
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT) ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	usleep(50);
	// get the response from the register
	bsc1[I2C_DLEN] = DLEN_BYTE;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1);  // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7) | (1 << 4) | 1; // I2CEN, ST, CLEAR, READ
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT)  ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	usleep(50);
	return bsc1[I2C_FIFO];
	return 0;
}

unsigned short i2c_read_word_data(unsigned char dev_addr, unsigned char reg_addr) {
	int timeout = 0;
	unsigned short ret = 0;
	unsigned char fifo_val = 0;
	bsc1[I2C_ADDR] = dev_addr;
	bsc1[I2C_DLEN] = DLEN_BYTE;
	bsc1[I2C_FIFO] = reg_addr;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1); // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7); // I2CEN, ST
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT) ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	usleep(50);
	// get the response from the register
	bsc1[I2C_DLEN] =  DLEN_WORD ;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1);  // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7) | (1 << 4) | 1; // I2CEN, ST, CLEAR, READ
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT)  ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	usleep(50);
	// TODO: probably change the order of the writes to ret of fifo_val
	// read first 8 bits from FIFO
	fifo_val = bsc1[I2C_FIFO];
	printf("fifo_val: 0x%02x\n", fifo_val);// REMOVE
	// load into lower half of ret
	ret |= fifo_val;
	// shift lower byte into upper byte of ret
	ret <<= 8;
	fifo_val = bsc1[I2C_FIFO];
	printf("fifo_val: 0x%02x\n", fifo_val); // REMOVE
	// load lower byte of ret with fifo_val
	ret |= fifo_val;
	return ret;
}

void i2c_write_byte_data(unsigned char dev_addr, unsigned char reg_addr, unsigned char value) {
	int timeout = 0;
	bsc1[I2C_ADDR] = dev_addr;
	bsc1[I2C_DLEN] = DLEN_WORD;
	bsc1[I2C_FIFO] = reg_addr;
	bsc1[I2C_FIFO] = value;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1); // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7); // I2CEN, ST
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT) ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	usleep(50);
}

int  main() {
	if (!my_init()) return -1;

	/*
	printf("dev_id: 0x%02x\n", i2c_read_byte_data(0x53, 0x00));
	printf("read_word: 0x%04x\n", i2c_read_word_data(0x53, 0x00));
	i2c_write_byte_data(0x53, 0x2d, 0x08);
	printf("DATAX0: 0x%04x\n", i2c_read_word_data(0x53, 0x32));
	*/

	my_uninit();
	return 0;
}
