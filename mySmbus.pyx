#RPI.C

#my_init
cdef extern from "RPI.c":
    int my_init()
cpdef my_my_init():
    my_init()


#my_uninit
cdef extern from "RPI.c":
    void my_uninit()
cpdef my_my_uninit():
    my_uninit()
    

#exphat.c

#i2c_read_byte_data
cdef extern from "exphat.c":
    unsigned char i2c_read_byte_data(unsigned char dev_addr, unsigned char reg_addr)
cpdef my_i2c_read_byte_data(unsigned char dev_addr, unsigned char reg_addr):
    return i2c_read_byte_data(dev_addr, reg_addr)

#i2c_read_word_data
cdef extern from "exphat.c":
    unsigned short i2c_read_word_data(unsigned char dev_addr, unsigned char reg_addr)
cpdef my_i2c_read_word_data(unsigned char dev_addr, unsigned char reg_addr):
    return i2c_read_word_data(dev_addr, reg_addr)

#i2c_write_byte_data
cdef extern from "exphat.c":
    void i2c_write_byte_data(unsigned char dev_addr, unsigned char reg_addr, unsigned char value)
cpdef my_i2c_write_byte_data(unsigned char dev_addr, unsigned char reg_addr, unsigned char value):
    i2c_write_byte_data(dev_addr, reg_addr,value)