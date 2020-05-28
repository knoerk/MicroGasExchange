/*
 * debug.h
 *
 * Created: 20.04.2014 11:15:37
 *  Author: knoerk
 */ 


#ifndef DEBUG_H_
#define DEBUG_H_

#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"
#include "sensValues.h"
#include "eepromValues.h"
#include "sTime.h"

extern uint8_t treatment;
extern uint8_t repetition;
extern uint8_t saveToEpromEnabled;

void debug(volatile sensValues* values_1,volatile sensValues* values_2,volatile sensValues* values_3, volatile eepromValues* eValues);

#endif /* DEBUG_H_ */