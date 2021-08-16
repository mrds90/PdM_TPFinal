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
#define WINDOW_SIZE 8
#define WINDOW_SIZE_BIT 3
#define DELAY_TIME_MS 30

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
// __WFI
// sleepUntilNextInterrupt()

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/
static fsm_state_t state;//<! current state of the state machine
static uint8_t voltage_value = 0;//<! voltage value read from the ADC conversion
static bool_t value_updated_flag = FALSE;//<! flag that indicates if the voltage value has been updated
static delay_t delay_main;//<! delay timer for the main state machine

/*=====[Main function, program entry point after power on or reset]==========*/

int main(void) {
   // ----- Setup -----------------------------------
   FSMMainPrgInit();
   // ----- Repeat for ever -------------------------
   while(TRUE) {
      FSMMainPrgUpdate();
   }
   return 0;
}


static void FSMMainPrgInit(void) {
   state = FSM_SLEEP;
   delayConfig(&delay_main, DELAY_TIME_MS);
   boardInit();
   FSMButtonInit(TEC1);
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
   static uint8_t v_window[WINDOW_SIZE] = {0};
   static uint8_t index = 0;
   static uint16_t v_acum = 0;
   
   if (value_updated_flag && delayRead(&delay_main)) {//<! if the voltage value has been updated and the delay timer has expired
      value_updated_flag = FALSE;//<! reset the flag
      /* 8 bytes buffer FIFO to implement a low pass filter (moving average) */
      v_acum += voltage_value;//<! add the new voltage value to the acumulator
      v_acum -= v_window[index];//<! subtract the old voltage value from the acumulator
      v_window[index] = voltage_value;//<! save the new voltage value in the buffer
      index = (index + 1) % WINDOW_SIZE;//<! increment the index
      uint8_t v_avrg = v_acum >> WINDOW_SIZE_BIT;//<! calculate the average voltage value
      
      LedTurnOnSeveral(v_avrg << (LEDB - LEDR)); //LEDB as LSB
   }
   //FSM_SLEEP input
   FSMButtonUpdate(TEC3);
   if(CheckFallState(TEC3)) {
      ADCDisable();
      LedTurnOffAll();//<! turn off the leds
      state = FSM_SLEEP;
   }
   //FSM_RESUME input
   FSMButtonUpdate(TEC2);
   if(CheckFallState(TEC2)){
      ADCDisable();
      state = FSM_RESUME;
   }
}

static void ResumeStateFunc(void) {
   gpioMap_t resume_leds[] = {LEDB, LEDG, LEDR};//<! resume leds in order
   
   state = FSM_RESUME;

   uint8_t resume_status = voltage_value / (BINARY_MAX_REPRESENTATION / 3); //0 to 2 posible values.
   LedTurnOnOne(resume_leds[resume_status]);

   FSMButtonUpdate(TEC2);
   if(CheckRaiseState(TEC2)){
      state = FSM_NORMAL;
      ADCConfig(ISRAdquisition);
      LedTurnOnOne(0);//turn off all leds
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

/*=====[Implementation of private interrupt functions]=================*/

static void ISRAdquisition(void) {
   ADCRead();
   state = FSM_ADQUISITION;
}


