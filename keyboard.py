import serial
import pyautogui

ser = serial.Serial(
    port='COM10',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)

direction = None
pressed = None

while True:
    buffer = ser.read()

    if(len(buffer) > 0):
        if direction == None:
            direction = buffer.decode("ascii")
        elif pressed == None:
            pressed = buffer.decode("ascii")

            # We now have everything we need to emulate keypress
            if direction == "U":
                if pressed == "P":
                    pyautogui.keyDown('w')
                elif pressed == "R":
                    pyautogui.keyUp('w')
            elif direction == "D":
                if pressed == "P":
                    pyautogui.keyDown('s')
                elif pressed == "R":
                    pyautogui.keyUp('s')
            elif direction == "L":
                if pressed == "P":
                    pyautogui.keyDown('a')
                elif pressed == "R":
                    pyautogui.keyUp('a')
            elif direction == "R":
                if pressed == "P":
                    pyautogui.keyDown('d')
                elif pressed == "R":
                    pyautogui.keyUp('d')
            
            # Clear direction and pressed
            direction = None
            pressed = None

# Theoretically, this should never happen
ser.close()