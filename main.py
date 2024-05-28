import numpy as np
import cv2 
from matplotlib import pyplot as plt
import threading
import time
import serial
import imageio


def comuniction_setup():
    port = '/dev/ttyACM0'
    baund_rate = 115200
    global ser
    ser = serial.Serial(port,baund_rate,timeout=1)
    time.sleep(2)
    ser.reset_input_buffer()
    print("serial comunication setup done")
    #
def GetBoxColor():
    img = video_reader.get_next_data()
    # Calculate the average color per channel
    average_color_per_channel = np.mean(img, axis=0)
    average_color = np.mean(average_color_per_channel, axis=0)
    # Convert the average color to integers
    average_color = np.uint8(average_color)
    R,G,B = average_color
    if (R>B):
        box_color = "red"
    if (B>R):
        box_color = "blue"
    img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
    cv2.imwrite("hovno.jpg",img)
    #print('Average color (RGB):', average_color)
    return box_color

def WaitForCommand():
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line == "givecolor":
                break
def SendData(box_color):
    while True:
            ser.write(box_color.encode('utf-8'))
            ser.write("\n".encode('utf-8'))
            time.sleep(0.1)

##start of the program 
#comuniction_setup()
print("sending ready message")
#ser.write("ready\n".encode('utf-8'))

video_reader = imageio.get_reader('<video0>','ffmpeg')#inicializace kamery
for i in range(8):
    WaitForCommand()
    #SendData(GetBoxColor())
    print(GetBoxColor())




