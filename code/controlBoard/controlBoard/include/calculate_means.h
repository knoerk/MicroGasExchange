/*
 * calculate_means.h
 *
 * Created: 20.04.2014 10:58:19
 *  Author: knoerk
 */ 


#ifndef CALCULATE_MEANS_H_
#define CALCULATE_MEANS_H_

#include <avr/io.h>
#include "sensValues.h"
uint8_t calculate_means(volatile sensValues* values);



#endif /* CALCULATE_MEANS_H_ */