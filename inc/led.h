/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/08/01
 * Version: 1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __LED_H__
#define __LED_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
/**
 * @brief With this macro you can set the color of the led. Is a 6 bit value that define wich leds will be used.
 * Example: 00110101 -> leds: LEDR, LEDB, LED2 y LED3
 * This should be write as: leds =  LEDR_ON | LEDB_ON | LED2_ON | LED3_ON
 * 
 */
#define LEDR_ON      (1 << (LEDR - LEDR)) // LEDR ON
#define LEDG_ON      (1 << (LEDG - LEDR)) // LEDG ON
#define LEDB_ON      (1 << (LEDB - LEDR)) // LEDB ON
#define LED1_ON      (1 << (LED1 - LEDR)) // LED1 ON
#define LED2_ON      (1 << (LED2 - LEDR)) // LED2 ON
#define LED3_ON      (1 << (LED3 - LEDR)) // LED3 ON

/*=====[Public function-like macros]=========================================*/
/**
 * @brief Enciende el led que le defino
 * 
 * @param led gpioMap_t
 * @return bool_t (true si logro encender)
 */
#define encenderLed(led) gpioWrite(led, 1)

/**
 * @brief apago el led que le defino
 * 
 * @param led gpioMap_t
 * @return bool_t (true si logro apagar)
 */
#define apagarLed(led) gpioWrite(led, 0)
/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/
/**
 * @brief Turn on one led and shutdown the others
 * 
 * @param led gpioMap_t
 * @return bool_t (TRUE if it was possible to turn on the led)
 */
bool_t LedTurnOnOne(gpioMap_t led);
/**
 * @brief Turn off all leds
 * 
 * @return bool_t 
 */
bool_t LedTurnOffAll(void);
/**
 * @brief Select the LED to turn on by a binary mask. LEDR_ON, LEDG_ON, LEDB_ON , LED1_ON , LED2_ON , LED3_ON macros are the reference for the mask.
 * 
 * @param code 
 */
void LedTurnOnSeveral(uint8_t code);
/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __ACTIVIDAD2_H__ */
