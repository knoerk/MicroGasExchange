/*
 * SPI.h
 *
 * Created: 03.12.2013 21:11:50
 *  Author: knoerk
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>


uint8_t spi_put_c( uint8_t data );
void spi_init();


#endif /* SPI_H_ */