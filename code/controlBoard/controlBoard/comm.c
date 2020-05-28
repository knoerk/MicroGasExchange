


//#define debug_can
#include "include/comm.h"

uint8_t sent_to_panel(uint8_t* lightValues)
{
	i2c_comm(lightValues,5,0,0);
	return 1;
}

uint8_t PCF8574_write(uint8_t value)
{
	volatile uint8_t data[2];
	data[0]=64;
	data[1]=value;
	i2c_comm(data,2,0,0);
	return 0;
}



