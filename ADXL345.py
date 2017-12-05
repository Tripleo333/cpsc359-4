'''
class:
    ADXL345
Purpose:
    This class is used to communicate through the SMbus and collect
    information from the accelerometer.

Methods:
    Constants:
        These constants are used throughout the code of the ADXL345 class
        and have been provided by the manufacturer.

    __init__:
        constructor for the ADXL345

    begin:
        Used to check that the accelerometer is connected properly to pi
        and the explorer hat and that eveything is communicating properly
        to each other.

    write_register:
        takes a value and gives it to the accelerometer through smbus methods
        while making sure to open and close lines of communication properly

    read_register:
        similar to previous method except it returns a value from the ADXL345
        but it needs a register to be given to know which one to read from
        values for used registers are defined in the constants at the top
        of the class.

    read_16:
        used to read a word instead of just a byte by reading a byte,
        shifting it to the higher bits then reading another byte.

    get_x, get_y, get_z:
        returns properly formatted data from the accelerometer with the
        length of a word for each of the x, y, and z axes respectively.

'''
import mySmbus


class ADXL345:
    ADXL345_ADDRESS = 0x53  # Assumes ALT address pin low
    ADXL345_REG_DEVID = 0x00  # Device ID
    ADXL345_REG_POWER_CTL = 0x2D  # Power-saving features control
    ADXL345_REG_DATAX0 = 0x32  # X-axis data 0
    ADXL345_REG_DATAY0 = 0x34  # Y-axis data 0
    ADXL345_REG_DATAZ0 = 0x36  # Z-axis data 0

    def __init__(self):
        self.mySmbus = mySmbus
#        self.bus = smbus.SMBus()
        self.BUS_ID = 1
        self.range = 0

    def begin(self):
        # check connection
        self.mySmbus.my_my_init()
        device_id = self.read_register(self.ADXL345_REG_DEVID)
        if device_id != 0xe5:
            # No ADXL345 detected ... return false
            #print(format(device_id, '02x'))
#           print(device_id)
            return False
        # enable measurements
        self.write_register(self.ADXL345_REG_POWER_CTL, 0x08)
        self.mySmbus.my_my_uninit()
        return True

    def write_register(self, reg, value):
#        self.bus.open(self.BUS_ID)
        self.mySmbus.my_my_init()
        self.mySmbus.my_i2c_write_byte_data(self.ADXL345_ADDRESS, reg, value)
        self.mySmbus.my_my_uninit()
#        self.bus.close()

    def read_register(self, reg):
#        self.bus.open(self.BUS_ID)
        temp = self.mySmbus.my_my_init()
        reply = self.mySmbus.my_i2c_read_byte_data(self.ADXL345_ADDRESS, reg)
        self.mySmbus.my_my_uninit()
#        self.bus.close()
        return reply

    def read_16(self, reg):
#        self.bus.open(self.BUS_ID)
        self.mySmbus.my_my_init()
        reply = self.mySmbus.my_i2c_read_word_data(self.ADXL345_ADDRESS, reg)
        self.mySmbus.my_my_uninit()
#        self.bus.close()
        return reply

    def get_x(self):
        return self.read_16(self.ADXL345_REG_DATAX0)

    def get_y(self):
        return self.read_16(self.ADXL345_REG_DATAY0)

    def get_z(self):
        return self.read_16(self.ADXL345_REG_DATAZ0)
