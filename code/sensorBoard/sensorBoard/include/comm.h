/*
 * comm.h
 *
 * Created: 20.04.2014 18:37:55
 *  Author: knoerk
 */ 


#ifndef COMM_H_
#define COMM_H_
#include <avr/io.h>
#include <avr/io.h>
#include <util/atomic.h>
#include <stdlib.h>
#include <util/delay.h>
#include "ADC.h"
#include "I2C.h"
#include "simple_delay.h"
#include "sensValues.h"
#include "can.h"
#include "sTime.h"
#include "senderID.h"


extern int16_t AC1;
extern int16_t AC2;
extern int16_t AC3;
extern uint16_t AC4;
extern uint16_t AC5;
extern uint16_t AC6;
extern int16_t B1;
extern int16_t B2;
extern int16_t MB;
extern int16_t MC;
extern int16_t MD;
extern volatile uint16_t milisecCounter3;
extern uint8_t message_request;
extern uint8_t send_always;
extern uint8_t can_new_message;
extern volatile uint8_t can_new_interrupt;
extern uint32_t intervall;
extern uint8_t meansRequest;
extern uint8_t CanErrorStatus;
extern volatile timeStruct sTime;

uint8_t hyt_get_values(volatile int16_t* hytTemp,volatile int16_t* feuchte);
uint8_t hyt_change_adress(uint8_t address_o, uint8_t adress_n);
uint8_t comm_mode_hyt (uint8_t adress);
uint8_t ra_hyt(uint8_t adress);
uint8_t wa_hyt(uint8_t adress, uint8_t adressNew);
uint8_t k30_get_values(volatile int16_t* co,volatile uint8_t* status);
uint8_t k30_set_ABC();
uint8_t k30_set_FRAC();
void bmp_get_cal();
void bmp_get_values(volatile int16_t *temp,volatile int32_t *pressure);
uint8_t getValues(volatile sensValues* actualValues);
void sendValuesViaUart (volatile sensValues actualValues);
void receive_command();
#endif /* COMM_H_ */