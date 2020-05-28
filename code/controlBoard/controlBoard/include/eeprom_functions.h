/*
 * eeprom_functions.h
 *
 * Created: 20.04.2014 10:09:26
 *  Author: knoerk
 */ 


#ifndef EEPROM_FUNCTIONS_H_
#define EEPROM_FUNCTIONS_H_

#include <avr/io.h>
#include "sensValues.h"
#include "sensValues.h"
#include "sTime.h"
#include "I2C.h"

extern uint8_t treatment;
extern uint8_t repetition;

uint8_t eprom_write (volatile sensValues* values_1,volatile sensValues* values_2,volatile sensValues* values_3, uint32_t* memory_adress);
uint8_t eprom_read ();
#endif /* EEPROM_FUNCTIONS_H_ */