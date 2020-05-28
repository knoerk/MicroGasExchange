/*
 * comm.h
 *
 * Created: 20.04.2014 10:23:24
 *  Author: knoerk
 */ 


#ifndef COMM_H_
#define COMM_H_

#include <avr/io.h>
#include "I2C.h"

uint8_t sent_to_panel(uint8_t* lightValues);
uint8_t PCF8574_write(uint8_t value);

uint8_t PCF8574_byte;

#endif /* COMM_H_ */