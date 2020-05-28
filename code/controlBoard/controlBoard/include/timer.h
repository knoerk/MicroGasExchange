/*
 * timer.h
 *
 * Created: 20.04.2014 09:47:46
 *  Author: knoerk
 */ 


#ifndef TIMER_H_
#define TIMER_H_


typedef struct
{
	uint8_t TCNT;
	uint8_t OCRA;
	uint8_t OCRB;
	uint8_t OCRC;
	uint8_t OCRD;
}s_timer;



#endif /* TIMER_H_ */