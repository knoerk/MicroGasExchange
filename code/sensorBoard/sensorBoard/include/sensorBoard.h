/*
 * sensorBoard.h
 *
 * Created: 09.11.2013 17:56:01
 *  Author: knoerk
 */ 


#ifndef SENSORBOARD_H_
#define SENSORBOARD_H_



#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include "can.h"
#include "simple_delay.h"
#include "ADC.h"
#include "uart.h"
#include "I2C.h"
#include "SPI.h"
#include "sensValues.h"
#include "sTime.h"
#include "senderID.h"
#include "comm.h"



volatile timeStruct sTime;

volatile uint8_t tick;
uint8_t can_new_message;
volatile uint8_t can_new_interrupt;
uint8_t send_always;
uint8_t message_request;
uint8_t meansRequest;
uint32_t intervall;
volatile uint8_t entprellsperre;
uint8_t CanErrorStatus;

volatile uint16_t milisecCounter,milisecCounter2,milisecCounter3, milisecCounter4;
char cOut[10];

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
		



void init (volatile sensValues* actualValues);



#endif /* SENSORBOARD_H_ */