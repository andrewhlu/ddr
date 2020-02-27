import serial
import pyautogui

ser = serial.Serial(
    port='COM13',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)

while True:
    for line in ser.read():
        print(chr(line))
        if chr(line) == "A":
            pyautogui.keyDown('a')
        elif chr(line) == "B":
            pyautogui.keyUp('a')

ser.close()