# Voltage sensor with binary representation

Read the voltage of a DC signal and show the value with binary code using 4 leds of the EDU-CIAA-NXP.

## Description

This aplication have 3 modes

| State  | Output                                                          |
| ------ | --------------------------------------------------------------- |
| Normal | Read the adc value and show it with the leds as a binary number |
| Resume | Use RGB leds to communicate a high, normal or low voltage       |
| Sleep  | Do nothing                                                      |


## Dependences
### CIAA Software
The CIAA Software is necessary to compile and download the project.
The CIAA Software can be downloaded and installed following the [CIAA SOFTWARE TUTORIAL](https://github.com/epernia/software/)
### Firmware v3
The [firmware_v3](https://github.com/epernia/firmware_v3/) is the firmware that the CIAA Project developed to use the hardware.
From this firmware is used the sapi that is the HAL implemented in the project.

For more information to use the firmware_v3 you can read the [English Readme](https://github.com/epernia/firmware_v3/blob/master/documentation/firmware/readme/readme-en.md) or [Spanish Readme](https://github.com/epernia/firmware_v3/blob/master/documentation/firmware/readme/readme-es.md)

## Arquitecture

The PdM_TPFinal is the main layer and use the services of the other layer. This second layer have 3 files:
* button
* led
* sense

### Main
This is the application layer. In this files the application use the services of the other layer to executes the states described on Description section.
In the figure there is the state representation of the system.
![alt text](https://github.com/mrds90/PdM_TPFinal/blob/main/docs/Mef.png?raw=true)

### Button
This layer is a 4 state FSM that check the state of the asked button. Each button may be in one of the four states.

This states are:
* UP
* FALLING
* DOWN
* RISING

In FALLING and RISING state the FSM check for a debounce effect. If the transition from UP to DOWN is confirmed the FSM report with a flag that the button was pressed. The behavior for DOWN to UP transition is similar.
### Led
This layer manage the lighting and shutdown of the leds.

### Sense
This layer manage the adc reading and interrupt.

## Download
* Open a Terminal in firmware_v3 projects path to download this project.
* Download the project writing:
```
git clone https://github.com/mrds90/PdM_TPFinal
```
## Compile

* Open the CIAA-Luncher and select the linux terminal

  ![alt text](https://github.com/mrds90/PdM_TPFinal/blob/main/docs/launcher-win.png?raw=true)
  
* use cd command and move to fimware_v3 path.
* select the program writing:
```
make select_program
```
* Choose the downloaded repositorie (PdM_TPFinal)
* Compile writing
```
make all
```
##  Download the firmware in the edu_cia_nxp

* Write in the terminal

```
make download
```
## Hardware Setup
This proyect use the CH1 of the Analgog inputs. An easy way to test this firmware is with the hardware setup of the following picture:
  ![alt text](https://github.com/mrds90/PdM_TPFinal/blob/main/docs/HardwareSetup.png?raw=true)
## Help

The selected board could be incorrect. To resolve this you can write in the terminal
```
make select_board
```
and select edu_ciaa_nxp

Always the terminal must be in the root path of firmware_v3 to use the make commands with CIAA Launcher terminal.

## Author

Marcos Dominguez
[@mrds90](https://github.com/mrds90)
