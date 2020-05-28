/*
 * ADC.h
 *
 * Created: 20.04.2014 18:33:47
 *  Author: knoerk
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

uint16_t adc_read (uint8_t mux);

#endif /* ADC_H_ */