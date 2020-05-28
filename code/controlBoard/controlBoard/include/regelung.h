/*
 * regelung.h
 *
 * Created: 20.04.2014 10:55:06
 *  Author: knoerk
 */ 


#ifndef REGELUNG_H_
#define REGELUNG_H_


#include <avr/io.h>

typedef struct
{
	int16_t err[3];
	uint8_t  tau;
	int32_t esum;
	int32_t pidoutput;
	int16_t setValue;
	int32_t P;
	int32_t I;
	int32_t D;
	uint16_t min;
	int16_t deadband;
	int16_t scale;
	uint8_t invert;
}PID_values;

uint8_t calculate_pid(PID_values* values, int16_t temp);
void init_PID_values(PID_values* values,uint16_t p, uint8_t i, uint16_t d,uint16_t stellValue, uint16_t min,uint16_t Deadband,uint8_t Tau, uint16_t Scale,uint8_t Invert);

#endif /* REGELUNG_H_ */