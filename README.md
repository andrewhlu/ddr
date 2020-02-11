# DDR Pad 

Norman Chung, Andrew Lu.

ECE 153B, Winter 2020, Professor Isukapalli.

---

## Overview

The goal of this project is to create a dance pad designed to play the “Dance Dance Revolution” game commonly found in arcades. The dance pad will consist of a large 3x3 grid with up, down, left, and right arrows which will serve as large buttons. When playing the game, users can step on the large buttons, which will complete foil circuits. This will cause an interrupt to send a keystroke over Bluetooth to the computer running the game. We will also utilize an NFC reader to manage credits like a standard arcade machine, and keep a scoreboard.

## Peripherals

* 4-8 custom-made button pads
    * The button pad will consist of two sheets of aluminum foil, separated by springs and/or cardboard. When the button is compressed by a user stepping on it, the foil will connect, creating a connection in the circuit.
* HC-05 Bluetooth Module
    * Used to send keystrokes to a host computer.
    * Communicates with the STM32 board using UART.
* PN532 NFC Reader
    * Reads NFC tags, which will be linked to specific people for keeping track of credits and scores.
    * Communicates with the STM32 board using either I2C or SPI (this module has support for both).
* LED Strips (SMD5050 chipset)
    * Layered on the side of the pads, so when a user steps on it, the strip lights up.
* Wood, Acrylic, and/or Cardboard for the assembly of the frame.
* Computer (used to play Dance Dance Revolution)

## Software Design

* Each of the buttons will be connected to a GPIO input pin. When the user steps on the pad, the circuit in the pad will be connected and trigger the interrupt for that GPIO pin. 
* If the interrupt is caused by a rising edge (stepping on the pad), the interrupt handler will send a Bluetooth keystroke via the HC-05 bluetooth module to the host computer. 
* When the user steps off the pad, the interrupt caused by the falling edge will stop the Bluetooth keypress.
* In addition, when the interrupt is triggered, we will light up the LED strip to full brightness for that pad. When the user steps off, the brightness of that LED strip will gradually dim until it turns off, or if it is stepped on again.
* The NFC module will disable the button pads until a valid NFC tag with credits is presented to the reader, allowing the user to play.

## Block Diagram

![Block Diagram](block.png)

## Goals

* Construct 4-8 button pads capable of withstanding continued footsteps (in a way that will not ruin the springs or the foil in the long run).
    * Determine what materials will allow us to keep the foil separate when not stepped on.
* Create an interrupt, triggered on both rising and falling edges, to translate pad steps to keyboard strokes communicated over Bluetooth to the computer running the game.
* When reading in the rising edge or falling edge, change the state of the LED lights accordingly.
* Store user credits and scores on the STM32 board, or find a way to delegate it elsewhere.
* Make sure the NFC reader works accurately, and add a feature to count credits.
    * Include feature to add credits and subtract upon each game.

## Group Responsibilities

* Andrew will design and assemble the button pads, and find the best materials to use.
* Norman will assist in creating the frame for the button pads, and mount the LEDs.
* When working on software, Andrew will work on implementing NFC functionality, while Norman will work on setting up the GPIO interrupts and Bluetooth functionality.
