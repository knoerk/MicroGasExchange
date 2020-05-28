/*
 * eepromValues.c
 *
 * Created: 20.04.2014 10:48:29
 *  Author: knoerk
 */ 

#include "include/eepromValues.h"

void init_eValues(volatile eepromValues* eValues,uint16_t i, uint8_t srt)
{
	//eValues->meanSensValues1=NULL;
	//eValues->meanSensValues2=NULL;
	
	eValues->signalRunTime=srt;
	eValues->signalRunTimeBuffer=srt;
	eValues->intervall=i;
	eValues->intervall_Buffer=i;
	
	eValues->BufferCounter1=0;
	eValues->BufferCounter2=0;
	eValues->BufferCounter3=0;
	eValues->delayTimer=0;
	eValues->delayTimer3=0;
	eValues->full=0;
}