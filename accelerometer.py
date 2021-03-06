'''
class:
    accelerometer.

Purpose:
    This is the accelerometer class for the game. It is a child of the
    controller class. This class interprets information from the ADXL345
    class and gives it to the game by implementing the abstract methods
    of the controller class.

Methods:
    __init__:
        constructor for the accelerometer.

    begin:
        initiates the ADXL345.

    twos_comp:
        converts returned values from the ADXL345 class from twos comp.

    click:
        not implemented since the click is in the joystick class.

    x_axis, y_axis, z_axis:
        used to return properly formatted values from the ADXL345 module.

    right, left, up, down, upside_down:
        used by the game because it returns a properly formatted value
        that can easily be interpreted by the game as accelerometer input.

'''

from ADXL345 import *
from controller import *


class Accelerometer(Controller):
    def __init__(self):
        super(Accelerometer, self).__init__()
        self.adxl = None
        self.adxl_range = 256  # value output from ADXL345 accel sensors +/-256 2scomp
        Controller.set_dead_zone(Controller.RANGE_LOWER, Controller.RANGE_UPPER, 0.2)

    def begin(self):
        self.adxl = ADXL345()
        if not self.adxl.begin():  # start ADXL345
            #raise RuntimeError("No ADXL345 detected")
            print()

    def twos_comp(self, val):
        val = ((val + 0x00008000) & 0x0000FFFF) - 0x00008000
        return val

    def click(self):
        return False

    def x_axis(self):
        x_val = self.twos_comp(self.adxl.get_x())
        return -self.format_axis(x_val, self.adxl_range)

    def y_axis(self):
        y_val = self.twos_comp(self.adxl.get_y())
        return self.format_axis(y_val, self.adxl_range)

    def z_axis(self):
        z_val = self.twos_comp(self.adxl.get_z())
        return self.format_axis(z_val, self.adxl_range)

    def right(self):
        return self.x_axis() > (Controller.RANGE_MID + Controller.get_dead_zone()) and \
               self.z_axis() < (Controller.RANGE_UPPER - Controller.get_dead_zone())

    def left(self):
        return self.x_axis() < -(Controller.RANGE_MID + Controller.get_dead_zone()) and \
               self.z_axis() < (Controller.RANGE_UPPER - Controller.get_dead_zone())

    def up(self):
        return self.y_axis() < -(Controller.RANGE_MID + Controller.get_dead_zone()) and \
               self.z_axis() < (Controller.RANGE_UPPER - Controller.get_dead_zone())

    def down(self):
        return self.y_axis() > (Controller.RANGE_MID + Controller.get_dead_zone()) and \
               self.z_axis() < (Controller.RANGE_UPPER - Controller.get_dead_zone())

    def upside_down(self):
        return self.z_axis() < (Controller.RANGE_MID - Controller.get_dead_zone())
