

#ifndef CONTROLBOARD_H_
#define CONTROLBOARD_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

#include "interrupts.h"
#include "simple_delay.h"
#include "sTime.h"
#include "eepromValues.h"
#include "eeprom_functions.h"
#include "can.h"
#include "comm.h"
#include "atm_programs.h"
#include "uart.h"
#include "I2C.h"
#include "SPI.h"
#include "regelung.h"
#include "sensValues.h"
#include "timer.h"
#include "sensValues.h"
#include "calculate_means.h"
#include "recieve_command.h"
#include "debug.h"


uint8_t HUMmode;
PID_values PID_values_preHeat;
PID_values PID_values_inHeat;
PID_values PID_values_specHum_in;
PID_values PID_values_vpd_in;
PID_values PID_values_co2;
	
program spec_hum_in_program;
program preHeat_program;
program inHeat_program;
program vpd_in_program;

int16_t AC1;
int16_t AC2;
int16_t AC3;
uint16_t AC4;
uint16_t AC5;
uint16_t AC6;
int16_t B1;
int16_t B2;
int16_t MB;
int16_t MC;
int16_t MD;

s_timer TIMER3;


uint8_t checkByteIn;
uint8_t checkByteOut;



extern volatile uint8_t tick,entprellsperre;
extern volatile int16_t milisecCounter,milisecCounter2,milisecCounter3, milisecCounter4;


uint8_t saveToEpromEnabled;
uint8_t buffer_update_flag;
uint8_t treatment;
uint8_t repetition;
uint8_t lightValues[5];
uint32_t memoryAdress;

extern volatile uint8_t can_new_message;
extern uint8_t CanErrorStatus;
extern volatile uint8_t can_new_interrupt;
extern uint8_t PCF8574_byte;

void init ();


#endif /* SENSORBOARD_H_ */