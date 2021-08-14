/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/08/01
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "led.h"

bool_t apagarLeds(void) {
	bool_t no_error;
	uint8_t i;
	for (i = LEDR ; i <= LED3 ; i++) {
		if (!apagarLed(i)) {
			no_error = false;
			break;
		}
	}
	return no_error;
}

bool_t encenderLedUnico(gpioMap_t led) {
	bool_t no_error;
	uint8_t i;
	for (i = LEDR ; i <= LED3 ; i++) {
		if (i == led) {
			no_error = encenderLed(i);
		}
		else {
			no_error = apagarLed(i);
		} 
		if (!no_error) {
			break;
		}
	}
	return no_error;
}

/**
 * @brief Función que decodifica los led que hay que encender y apagar segun el valor de la variable secuencia en ptrLed.
 * 
 */
void LEDOnSelection(uint8_t code) {
   uint8_t led;
   for (led = 0; led < (LED3 - LEDR + 1); led++) {
      if (code & (1<<led)) {
         encenderLed(led+LEDR);
      }
      else {
         apagarLed(led+LEDR);
      }
   }
}

