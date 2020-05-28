/*
 * simple_delay.h
 *
 * Created: 20.04.2014 18:35:04
 *  Author: knoerk
 */ 


#ifndef SIMPLE_DELAY_H_
#define SIMPLE_DELAY_H_

#include <avr/io.h>

extern volatile uint16_t milisecCounter4;

void simple_delay (uint16_t delayTime);

#endif /* SIMPLE_DELAY_H_ */