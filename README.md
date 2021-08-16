# Voltage sensor with binary representation

Read the voltage of a DC signal and show the value with binary code using 4 leds of the EDU-CIAA-NXP.

## Description

This aplication have 3 modes

| State  | Out                                                             |
| ------ | --------------------------------------------------------------- |
| Normal | Read the adc value and show it with the leds as a binary number |
| Resume | Use RGB leds to comunicate a high, normal or low voltage        |
| Sleep  | Do nothing                                                      |


## Dependences
### CIAA Software
The CIAA Softwar is necesary to compile and download the proyect.
The CIAA Software can be downloaded and installed following de [CIAA SOFTWARE TUTORIAL](https://github.com/epernia/software/)
### Firmware v3
The [firmware_v3](https://github.com/epernia/firmware_v3/) is the firmware that de CIAA Proyect develop to use the hardware.
From this firmware is used the ´´´sapi´´´ that is the HAL implemented in the proyect.

For more information to use the firmware_v3 you can read the [English Readme](https://github.com/epernia/firmware_v3/blob/master/documentation/firmware/readme/readme-en.md) or [Spanish Readme](https://github.com/epernia/firmware_v3/blob/master/documentation/firmware/readme/readme-es.md)

## Arqutecture

The PdM_TPFinal is the highest layer and use the services of the other layer. This files are:
* button
* led
* sense

### Main
This is the aplication layer. In this files the aplication use the services of the other layers to executes the states decribed on Description section.
In the figure there is the state representation of the system.
![alt text](https://github.com/mrds90/PdM_TPFinal/blob/main/docs/Mef.png?raw=true)

### Button
This layer is a 4 state FSM that check the state of the asked button. Each button may be in one of the four states.

This states are:
* UP
* FALLING
* DOWN
* RISING

In FALLING and RISING state the FSM check for a debounce efect. If the transition from UP to DOWN is confirmed the FSM report with a flag that the button was pressed. Similar behaviour for DOWN to UP transition.
### Led
This layer manage the lighting and shutdown of the leds.

## Download
Open a Terminal where you have the firwate_v3 proyects to download this proyect and write
```
git clone https://github.com/mrds90/PdM_TPFinal
```
## Compile

* Open the CIAA-Luncher and select the linux terminal

  ![alt text](https://github.com/mrds90/PdM_TPFinal/blob/main/docs/launcher-win.png?raw=true)
  
* use ´´´cd´´´ command and move to fimware_v3 path.
* select the program writing:
```
make select_program
```
* Choose the downladed repositorie (PdM_TPFinal)
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
This proyect use de CH1 of de Analgog inputs. An easy way to test this firmware is with the hardware setup of the following picture:
  ![alt text](https://github.com/mrds90/PdM_TPFinal/blob/main/docs/HardwareSetup.png?raw=true)
## Help

The selecte board could be incorrect. To resolve this you can write in the terminal
```
make select_board
```
and select edu_ciaa_nxp

Always the terminal must be in the root path of firmware_v3 to use the command with CIAA Launcher terminal.

## Autor

Marcos Dominguez
[@mrds90](https://github.com/mrds90)
