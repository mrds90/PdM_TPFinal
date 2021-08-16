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
![alt text](https://github.com/[username]/[reponame]/blob/[branch]/image.jpg?raw=true)

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
Open a Terminal where you want to download this proyect and write
```
git clone https://github.com/mrds90/PdM_TPFinal
```
## Compile

* Open the CIAA-Luncher and select the linux terminal
  
* Seleccionar el programa con el comando
```
make select_program
```
* Elegir la carpeta del repositorio descargado (PmC_Actividad3)
* Compilar el programa el programa en la misma terminal con:
```
make all
```
##  Descargar programa en edu_cia_nxp

* En la misma terminal y con la edu_ciaa_nxp conectada escribir

```
make download
```

## Help

Puede no tener seleccionado la placa correcta. Para corregir esto escriba
```
make select_board
```
y seleccione la edu_ciaa_nxp

Siempre debe estar en la ruta raiz de la carpeta clonada "firmware_v3" con la terminal de CIAA Launcher si desea usar los comandos.

Si el orden de los LEDs no son correspondientes debe comentar el #define del simbolo EDU_CIAA_OLD. (linea 15 del archivo semaforo.c)
```
// #define EDU_CIAA_OLD
```

## Autor

Marcos Dominguez
[@mrds90](https://github.com/mrds90)
