# Importing Libraries
from email.utils import parsedate_to_datetime
from pickletools import string1
from turtle import delay
import serial
import time

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
def write(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
def read():
    senData = arduino.readline() # read line form serial
    data = senData.decode() # convert the byte string to a unicode string
    parsedData = data.split('\r')
    if parsedData[0] != '':
       return int(parsedData[0])
    else:
        return 0
     
def water(counter):
    # record the time passed
    # two second dlay from start up
    start = time.time()
    # loop goes counts down watering
    while True:
        time.sleep(0.2)
        if time.time() - start > 1:
            start = time.time()
            counter = counter - 1

            # This will be updated once per second
            print(counter)

            if counter <= 0:
                write("0")
                break
            else:
                write("1")

wet = 0
flower = input("Enter your flower: ") # Taking input from user
print(flower)
seconds = 0
# give water depending on which flower
if flower == "dandelion":
    seconds = 3
if flower == "tulip":
    seconds = 4
if flower == "sunflower":
    seconds = 5
if flower == "daisy":
    seconds = 6
if flower == "rose":
    seconds = 7

while True:
    # make less than
    # if the moisture is less than value then water based on plant
    if wet < 800:
        water(seconds)
     # flip this for actual product
        wet = 1000
    else:
        wet = read()

    print(wet)
    time.sleep(0.2)