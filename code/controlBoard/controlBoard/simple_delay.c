/*
 * delay.c
 *
 * Created: 20.04.2014 09:36:24
 *  Author: knoerk
 */ 


#include "include/simple_delay.h"


void delay (uint16_t delayTime)
{
	milisecCounter4=0;
	while (milisecCounter4<(delayTime*8))
	{
		
	}
}