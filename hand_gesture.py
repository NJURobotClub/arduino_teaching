from serial import Serial  # add Serial library for serial communication
import pyautogui  # add pyautogui library for programmatically controlling the mouse and keyboard.]
import time

Arduino_Serial = Serial('COM5', 9600)  # Initialize serial and Create Serial port object called Arduino_Serial

while 1:
    incoming_data = str(Arduino_Serial.readline())  # read the serial data and print it as line
    print(incoming_data)  # print the incoming Serial data

    if 'left' in incoming_data:
        pyautogui.keyDown('left')
        time.sleep(0.1)
        pyautogui.keyUp('left')
    elif 'right' in incoming_data:
        pyautogui.keyDown('right')
        time.sleep(0.1)
        pyautogui.keyUp('right')

    incoming_data = ""  # clears the data
