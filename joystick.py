'''
class:
    joystick

Purpose:
    This is a child class of the controller class. It uses functions
    defined in the explorer hat to interpret different inputs on the joystick

Methods:
    __init__:
        constructor for the joystick controller. There should only be one
        joystick in the game.
    x_axis, y_axis:
        reads the values of the x, and y axes from the explorer hat
    left, right, up, down:
        takes values returned from x_axis, and y_axis and interprets them
        to be used in the game and adds a dead zone for inaccuracies in
        the input.
    click:
        This gets input from the explorer hat's input one and returns true
        when the button is clicked.
'''
import explorerhat

from controller import *


class Joystick(Controller):
    def __init__(self):
        super(Joystick, self).__init__()
        self.low_volt, self.high_volt = 0, 5
        self.mid_volt = round((self.high_volt - self.low_volt) / 2, 3)
        Controller.set_dead_zone(self.low_volt, self.high_volt, 0.3)

    def click(self):
        return explorerhat.input.one.read() == 1

    def x_axis(self):
        return -self.format_axis(explorerhat.analog.one.read(), self.low_volt, self.high_volt)

    def y_axis(self):
        return -self.format_axis(explorerhat.analog.two.read(), self.low_volt, self.high_volt)

    def z_axis(self):
        return Controller.RANGE_MID

    def left(self):
        return explorerhat.analog.one.read() > (self.mid_volt + Controller.get_dead_zone())

    def right(self):
        return explorerhat.analog.one.read() < (self.mid_volt - Controller.get_dead_zone())

    def up(self):
        return explorerhat.analog.two.read() < (self.mid_volt - Controller.get_dead_zone())

    def down(self):
        return explorerhat.analog.two.read() > (self.mid_volt + Controller.get_dead_zone())
