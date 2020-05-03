#!/usr/bin/env python
# @author Carl Saldanha <cjds92@gmail.com>
# @brief Web sserver to help move the robot
import RPi.GPIO as GPIO
import time


def test_wheel(input1, input2):
    # set up the GPIO lines
    print("First input %d. Second Input %d")
    gpio.setup(input1, GPIO.OUT)
    gpio.setup(input2, GPIO.OUT)
    
    # backward
    print("Back:")
    gpio.output(input1, False)
    gpio.output(input2, True)
    
    time.sleep(0.5)
    print("Forward:")
    # Forward
    gpio.output(input2, False)
    gpio.output(input1, True)
    time.sleep(0.5)
    gpio.output(input1, False)
    gpio.output(input2, False)

if __name__ == "__main__":
    GPIO.cleanup()
    GPIO.setmode(GPIO.BCM)

    gpio = GPIO

    print("Front Right Wheel")
    test_wheel(6, 13)
    print("Front Left Wheel")
    test_wheel(26, 19)

    GPIO.cleanup()
