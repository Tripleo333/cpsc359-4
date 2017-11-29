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
	// get the response from the register
	bsc1[I2C_DLEN] = DLEN_BYTE;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1);  // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7) | (1 << 4) | 1; // I2CEN, ST, CLEAR, READ
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT)  ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	return bsc1[I2C_FIFO];
}

// TODO: IMPLEMENT THIS
unsigned short i2c_read_word_data(unsigned char dev_addr, unsigned char reg_addr) {
	int timeout = 0;
	bsc1[I2C_ADDR] = dev_addr;
	bsc1[I2C_DLEN] = DLEN_WORD;
	bsc1[I2C_FIFO] = reg_addr;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1); // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7); // I2CEN, ST
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT) ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	// get the response from the register
	bsc1[I2C_DLEN] = DLEN_BYTE;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1);  // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7) | (1 << 4) | 1; // I2CEN, ST, CLEAR, READ
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT)  ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	printf("TODO: IMPLEMENT i2c_read_word_data");
	return 0;
}

// TODO: IMPLEMENT THIS
void i2c_write_byte_data(unsigned char dev_addr, unsigned char reg_addr, unsigned char value) {
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
	// get the response from the register
	bsc1[I2C_DLEN] = DLEN_BYTE;
	bsc1[I2C_STATUS] = (1 << 9) | (1 << 8) | (1 << 1);  // clear CLKT, ERR, DONE
	bsc1[I2C_C] = (1 << 15) | (1 << 7) | (1 << 4); // I2CEN, ST, CLEAR, WRITE (last position left blank)
	// wait till done
	while( (!(bsc1[I2C_STATUS] & 0x02)) && (timeout < I2C_TIMEOUT)  ) {   // 0x02 masks DONE bit
		usleep(1000);
	}
	printf("TODO: IMPLEMENT i2c_write_byte_data");
}

int  main() {
	if (!my_init()) return -1;
	// printf("uc:%d us:%d\n",sizeof(unsigned char),sizeof(unsigned short));
	
	printf("dev_id: 0x%02x\n", i2c_read_byte_data(0x53, 0x00));
	
	my_uninit();
	return 0;
}
