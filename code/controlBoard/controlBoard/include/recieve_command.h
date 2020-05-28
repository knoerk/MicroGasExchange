/*
 * recieve_command.h
 *
 * Created: 20.04.2014 08:37:14
 *  Author: knoerk
 */ 


#ifndef RECIEVE_COMMAND_H_
#define RECIEVE_COMMAND_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include "sensValues.h"
#include "eepromValues.h"
#include "eeprom_functions.h"
#include "uart.h"
#include "regelung.h"
#include "sTime.h"
#include "atm_programs.h"
#include "can.h"
#include "comm.h"
#include "timer.h"

extern	volatile sensValues actualValues_1;
extern	volatile sensValues actualValues_2;
extern	volatile sensValues actualValues_3;
extern	volatile eepromValues eValues;
extern uint32_t memoryAdress;

extern	PID_values PID_values_preHeat;
extern	PID_values PID_values_inHeat;
extern	PID_values PID_values_specHum_in;
extern	PID_values PID_values_vpd_in;
extern	PID_values PID_values_co2;
	
extern uint8_t treatment;
extern uint8_t repetition;
extern uint8_t lightValues[5];
extern uint8_t buffer_update_flag;
extern uint8_t saveToEpromEnabled;
extern uint8_t CanErrorStatus;
extern volatile uint8_t can_new_interrupt;

extern s_timer TIMER3;
extern program spec_hum_in_program;
extern program preHeat_program;
extern program inHeat_program;
extern program vpd_in_program;

void recieve_command(volatile sensValues* values_1,volatile sensValues* values_2,volatile eepromValues* eValues);



#endif /* RECIEVE_COMMAND_H_ */