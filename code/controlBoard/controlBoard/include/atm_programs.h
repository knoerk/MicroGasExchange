/*
 * atm_programs.h
 *
 * Created: 20.04.2014 09:52:39
 *  Author: knoerk
 */ 


#ifndef ATM_PROGRAMS_H_
#define ATM_PROGRAMS_H_

#include <avr/io.h>
#include <stdlib.h>
#include "regelung.h"
#include "uart.h"

typedef struct
{
	uint16_t min;
	uint16_t max;
	uint16_t step;
	uint8_t active;
	uint8_t up;
	uint8_t down;
	uint8_t init;
	uint16_t duration;
	uint16_t timer;
}
program;

enum humMode
{
	specHum_in=1,
	vpd_out=2
};
uint8_t HUMmode;

extern PID_values PID_values_specHum_in;
extern PID_values PID_values_preHeat;
extern PID_values PID_values_inHeat;
extern PID_values PID_values_vpd_in;

void set_program(program* Program,uint16_t min,uint16_t max,int16_t step,uint16_t duration);
void stop_and_reset_program(program* Program);
uint8_t exec_program (program* Program, PID_values* pidValues);

#endif /* ATM_PROGRAMS_H_ */