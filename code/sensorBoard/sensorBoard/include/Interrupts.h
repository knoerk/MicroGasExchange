/*
 * Interrupts.h
 *
 * Created: 20.04.2014 19:50:58
 *  Author: knoerk
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "sTime.h"

extern volatile timeStruct sTime;
extern volatile uint16_t milisecCounter,milisecCounter2,milisecCounter3, milisecCounter4;
extern volatile uint8_t tick;
extern volatile uint8_t entprellsperre;
extern uint8_t send_always;
extern volatile uint8_t can_new_interrupt;

#endif /* INTERRUPTS_H_ */