import RPi.GPIO as GPIO
import time

GPIO.cleanup()
#GPIO.setmode(GPIO.BOARD)
GPIO.setmode(GPIO.BCM)

gpio = GPIO

in1 = 6
in2 = 13
in3 = 19
in4 = 26


in5 = 4
in6 = 17
in7 = 27
in8 = 22
# set up the GPIO lines
gpio.setup(in1, GPIO.OUT)
gpio.setup(in2, GPIO.OUT)
gpio.setup(in3, GPIO.OUT)
gpio.setup(in4, GPIO.OUT)
gpio.setup(in5, GPIO.OUT)
gpio.setup(in6, GPIO.OUT)
gpio.setup(in7, GPIO.OUT)
gpio.setup(in8, GPIO.OUT)


def move_robot(in1_in, in2_in, in3_in, in4_in, 
               in5_in, in6_in, in7_in, in8_in):
    
    gpio.output(in1, in1_in)
    gpio.output(in4, in2_in)
    gpio.output(in2, in3_in)
    gpio.output(in3, in4_in)
    
    gpio.output(in5, in5_in)
    gpio.output(in6, in6_in)
    gpio.output(in7, in7_in)
    gpio.output(in8, in8_in)
    
# all 4 forward
#move_robot(False, True, True, True, True, True, True, False)
#move_robot(True, True, True, True, True, True, True, False)
#time.sleep(0.5)

"""
# All 4 wheels forward
move_robot(True, True, False, False, False, False, True, True)
time.sleep(0.5)
# All 4 wheels backwoard
move_robot(False, False, True, True, True, True, False, False)
time.sleep(0.5)
"""
# Move right
move_robot(False, True, True, False, False, True, False, True)
time.sleep(0.5)
# Move left
move_robot(True, False, False, True,  True, False, True, False)
time.sleep(0.5)
"""
move_robot(True, False, True, False, True, False, True, False)
time.sleep(0.5)
move_robot(False, True, False, True, False, True, False, True)
time.sleep(0.5)
"""
# input from channel 0

# output to channel 1
move_robot(False, False, False, False,
               False, False, False, False)

GPIO.cleanup()
