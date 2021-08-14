/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/08/10
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/
#include "PdM_TPFinal.h"
#include "../inc/led.h"
#include "../inc/button.h"
#include "../inc/sense.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/
#define RESUME_STATUS_QTY 3
#define BINARY_MAX_REPRESENTATION 15
typedef enum {
   FSM_NORMAL,
   FSM_RESUME,
   FSM_SLEEP,
   FSM_ADQUISITION,

   FSM_STATE_QTY,
} fsm_state_t;
/*=====[Definitions of private functions]====================================*/
/**
 * @brief This function is the entry point of the main state machine.
 * 
 */
static void FSMMainPrgInit(void);

/**
 * @brief This function update the state of the main state machine.
 * 
 */
static void FSMMainPrgUpdate(void);
/**
 * @brief Update leds as a binary number. The binary number reresents the voltage read on the ADC.
 * 
 */
static void NormalStateFunc(void);
/**
 * @brief Update leds. There are 3 values: BLUE (low), GREEN (normal), RED (high)
 * 
 */
static void ResumeStateFunc(void);
/**
 * @brief don't do nothing until TEC1 is press. this turn on the system again.
 * 
 */
static void SleepStateFunc(void);
/**
 * @brief Make the conversion from count to a voltage value.
 * 
 */
static void AdquisitionStateFunc(void);
/**
 * @brief Interrupt routine from ADC that read the last value converted
 * 
 */
static void ISRAdquisition(void);

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/
static fsm_state_t state;
static uint8_t voltage_value = 0;
bool_t value_updated_flag = FALSE;
// __WFI
// sleepUntilNextInterrupt()

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   FSMMainPrgInit();
   // ----- Repeat for ever -------------------------
   while( true ) {
      FSMMainPrgUpdate();
   }
   return 0;
}


static void FSMMainPrgInit(void) {
   state = FSM_NORMAL;
   boardInit();
   FSMButtonInit(TEC2);
   FSMButtonInit(TEC3);
   ADCConfig(ISRAdquisition);
}

static void FSMMainPrgUpdate(void) {
   void (*ptrStateFunc[FSM_STATE_QTY])(void) = {NormalStateFunc, ResumeStateFunc, SleepStateFunc, AdquisitionStateFunc};
   ptrStateFunc[state]();
}

static void NormalStateFunc(void) {
   state = FSM_NORMAL;
   
   if (value_updated_flag) {
      value_updated_flag = FALSE;
      LEDOnSelection(voltage_value << (LEDB - LEDR)); //LEDB as LSB
      ADCConfig(ISRAdquisition);
   }

   FSMButtonUpdate(TEC3);
   if(CheckFallState(TEC3)){
      state = FSM_SLEEP;
      FSMButtonInit(TEC1);
      encenderLedUnico(0);// Turn off all leds.
      ADCDisable();
   }

   FSMButtonUpdate(TEC2);
   if(CheckFallState(TEC2)){
      state = FSM_RESUME;
      ADCDisable();
   }
}

static void ResumeStateFunc(void) {
   gpioMap_t resume_leds[] = {LEDB, LEDG, LEDR};
   
   state = FSM_RESUME;

   uint8_t resume_status = (voltage_value * RESUME_STATUS_QTY) >> ADC_BITS_RESOLUTION; //0 to 2 posible values.
   encenderLedUnico(resume_leds[resume_status]);

   FSMButtonUpdate(TEC2);
   if(CheckRaiseState(TEC2)){
      state = FSM_NORMAL;
      ADCConfig(ISRAdquisition);
      encenderLedUnico(0);//turn off all leds
   }
}

static void SleepStateFunc(void) {
   state = FSM_SLEEP;
   FSMButtonUpdate(TEC1);
   if(CheckFallState(TEC1)) {
      state = FSM_NORMAL;
      ADCConfig(ISRAdquisition);
   }

}

static void AdquisitionStateFunc(void) {
   voltage_value = (ADCDataValue() * BINARY_MAX_REPRESENTATION) >> ADC_BITS_RESOLUTION;
   value_updated_flag = TRUE;
   state = FSM_NORMAL;
}

static void ISRAdquisition(void) {
   state = FSM_ADQUISITION;
   ADCRead();
   ADCDisable();
}


