/*
 * interrupts.h
 *
 * Created: 20.04.2014 11:54:29
 *  Author: knoerk
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sTime.h"
#include "timer.h"

volatile int16_t milisecCounter,milisecCounter2,milisecCounter3, milisecCounter4;
volatile uint8_t tick,entprellsperre;

extern s_timer TIMER3;
extern uint8_t saveToEpromEnabled;
extern volatile uint8_t can_new_interrupt;


#endif /* INTERRUPTS_H_ */