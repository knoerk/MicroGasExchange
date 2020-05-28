

#ifndef SC_I2C_H_
#define SC_I2C_H_

#include <avr/interrupt.h>
#include "uart.h"
#include "simple_delay.h"

extern volatile int16_t milisecCounter2;

typedef volatile struct  
{
	uint8_t *write_buffer; uint8_t read_buffer[18]; uint8_t* inpos; uint8_t write_length; uint8_t read_length ; uint8_t position; uint8_t succesBit; uint8_t rs;
} I2CBufferStruct;
 I2CBufferStruct I2CBuffer;

void debug ();
int twi_init();
void TwiReset  ();
uint8_t* i2c_comm (volatile uint8_t* buffer,uint8_t write_length,uint8_t read_length,uint8_t rs);

uint8_t i2cTimeOut, twi_error_flag;

#endif

