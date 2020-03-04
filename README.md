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

---

The original project proposal, submitted to GauchoSpace, can be found [here](proposal.pdf).

---

# Weekly Updates

## Week 6 Update

After an initial review by our TA ([Ryan Kirkpatrick](https://www.ece.ucsb.edu/~yoga/capstone/static/img/students/ryan_kirkpatrick.jpg)), along with some additional research about ways to implement our large button pads, we have decided to make the following changes to our project:

* Instead of using foil pads for our large buttons, we will look into using mechanical keyboard switches (specifically [NovelKeys x Kailh BOX Heavy Switches, Dark Yellow](https://novelkeys.xyz/collections/switches/products/novelkeys-x-kailh-box-heavy-switches)), since they have two legs and can be connected like a regular button. 
    * We have purchased two packs and will be testing this with our board once we receive them.
* The NFC functionality for inserting credits will be moved to the end of our project and set as a stretch goal, upon recommendation from Ryan, since I2C communication for the PN532 module has the potential to cause a lot of issues.
    * If time permits, we will try to implement this functionality, but it will be put on the side for now.
* We will initially start with only four large button pads for the four directions. The "Select" and "Back" buttons will either be added in later or simply be smaller buttons on the side.

## Week 7 Update

We have received our initial order of mechanical keyboard switches. We were able to wire them like buttons and successfully use them to trigger interrupts by reading standard GPIO input. 

The switch was connected as follows:

* One leg of the switch is connected to the 3V3 pin on the Discovery board.
* The other leg of the switch is connected via a breadboard to GPIO pin PB2 and one leg of a resistor.
* The other leg of the resistor is connected to GND.

When the switch is pressed, the two legs will be connected, allowing current to flow. The GPIO input pin reads the voltage after the switch and uses its state to trigger an interrupt.

This circuit was tested using the code from Lab 1, Part B. No changes were made to the code, and the circuit works as expected, so we will move forward with using mechanical keyboard switches to detect steps on our DDR pad.

We plan to perform the following tasks this weekend:

* Finish Lab 3 (which will allow us to better understand the operation of the HC-05 Bluetooth Module).
* Create / sketch the design for the DDR pad. This includes the wood base, springs, switch placement, wiring, LEDs, etc.
* Create a list of parts we will need to purchase, and come up with a plan for purchasing these parts.
* Using the code from Lab 1, Part B, as a start, write the code and interrupts for the four switches that will be used.

## Week 8 Update

We started this week by completing Lab 3. In doing so, however, we discovered that the HC-05 Bluetooth Module is unable to act as a HID device. Upon researching this issue, we discovered that it is theoretically possible to flash the firmware on the module to allow the module to act as an HID device ([see this Instructables article](https://www.instructables.com/id/Upgrade-Your-3-Bluetooth-Module-to-Have-HID-Firmwa/)), but doing so would require us to buy an additional breakout board just to flash the new image. 

As a result, we have opted to forego using this module to emulate a Bluetooth Keyboard. We will instead use standard UART communication over Bluetooth, like we did with Lab 3. In order to get our pad presses into the app, we wrote a simple Python script that will read input from the COM port that the HC-05 is connected to, and emulate a keypress using a library such as [pywin32](https://pypi.org/project/pywin32/) or [pyautogui](https://pyautogui.readthedocs.io/en/latest/).

During Wednesday's lab session, we combined parts of Lab 1B and Lab 3A starter code to use one of our mechanical keyboard switches to emulate the keypress of the character "a" on a computer. The code can be found [on GitHub](https://github.com/andrewhlu/ddr/tree/d73674e7bb15bfca19e8809a1d047ec9f7723af4).

We have also started to plan the design and come up with a list of materials that we need. [This image](week-8-planning.png) shows the preliminary sketches we made during Wednesday's lab session for the design of the pad. We agreed to purchase the springs from McMaster-Carr and purchase the rest of the components from Home Depot. The exact list of components will be decided over the weekend, when we can create a more exact design.
