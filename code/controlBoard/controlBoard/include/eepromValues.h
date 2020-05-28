/*
 * eepromValues.h
 *
 * Created: 20.04.2014 09:30:47
 *  Author: knoerk
 */ 


#ifndef EEPROMVALUES_H_
#define EEPROMVALUES_H_

#include "sensValues.h"

typedef struct
{
	sensValues meanSensValues1;
	sensValues meanSensValues2;
	sensValues meanSensValues3;
	
	uint8_t signalRunTime;
	uint8_t signalRunTimeBuffer;
	int16_t intervall;
	int16_t intervall_Buffer;
	
	uint16_t BufferCounter1;
	uint16_t BufferCounter2;
	uint8_t BufferCounter3;
	
	uint8_t delayTimer;
	uint8_t delayTimer3;
	uint8_t full;
	
}eepromValues;

void init_eValues(volatile eepromValues* eValues,uint16_t i, uint8_t srt);

#endif /* EEPROMVALUES_H_ */