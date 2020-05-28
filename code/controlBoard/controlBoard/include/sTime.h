/*
 * sTime.h
 *
 * Created: 20.04.2014 09:45:00
 *  Author: knoerk
 */ 


#ifndef STIME_H_
#define STIME_H_

#include <avr/io.h>

typedef struct
{
	uint8_t days; uint32_t daySecs; uint32_t daySecsTEMP;
} timeStruct;
volatile timeStruct sTime;



#endif /* STIME_H_ */