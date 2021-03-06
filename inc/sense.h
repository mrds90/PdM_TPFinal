/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/08/10
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __SENSE_H__
#define __SENSE_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
#define ADC_BITS_RESOLUTION 10
/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/
void ADCConfig(void *ptr_function);

void ADCDisable(void);

void ADCRead(void);

bool_t ADCDataAvailable(void);

uint16_t ADCDataValue(void);
/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __SENSE_H__ */
