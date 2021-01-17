# -*- coding: utf-8 -*-
"""
Created on Sun Jan 10 17:14:56 2021

@author: Marco Rouge
"""
import serial

serial_data = 0

def decoder(var, var_type, byteorder = "big", signed = False):

    if var_type == str:
        return var.decode("utf-8")

    if var_type == int:
        return int.from_bytes(var, byteorder = byteorder, signed = signed)

try:
    ser = serial.Serial('COM9', timeout=5)  # open serial port

    if ser.isOpen():
        print("{} sucessfully opened".format(ser.name)) # check which port was really used
    else:
        raise SystemExit()


    while(True):
        serial_data = ser.read(size = 3)  # read characters

        if serial_data == None:
            break

        print(decoder(serial_data, int))
        serial_data = None

finally:
    ser.close()             # close port
    print("{} sucessfully closed".format(ser.name))