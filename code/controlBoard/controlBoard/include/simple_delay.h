/*
 * simple_delay.h
 *
 * Created: 20.04.2014 09:36:14
 *  Author: knoerk
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#include <avr/io.h>

extern volatile int16_t milisecCounter4;

void delay (uint16_t delayTime);

#endif /* DELAY_H_ */