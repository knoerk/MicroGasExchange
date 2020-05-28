/*
* atm_programs.c
*
* Created: 20.04.2014 09:52:22
*  Author: knoerk
*/


#include "include/atm_programs.h"

void set_program(program* Program,uint16_t min,uint16_t max,int16_t step,uint16_t duration)
{
	Program->min=min;
	Program->max=max;
	Program->step=step;
	Program->active=1;
	Program->up=0;
	Program->down=1;
	Program->init=1;
	Program->duration=duration;
	Program->timer=duration;
}
void stop_and_reset_program(program* Program)
{
	Program->min=0;
	Program->max=0;
	Program->step=0;
	Program->active=0;
	Program->up=0;
	Program->down=0;
	Program->init=0;
	Program->duration=0;
	Program->timer=0;
}

uint8_t exec_program (program* Program, PID_values* pidValues)
{
	if (Program->init)
	{
		pidValues->setValue=Program->max;
		Program->init=0;
	}

	Program->timer--;

	if (!Program->timer)
	{
		if (Program->down)
		{
			pidValues->setValue=pidValues->setValue-Program->step;
		}
		else
		{
			pidValues->setValue=pidValues->setValue+Program->step;
		}
		
		if (pidValues->setValue<=Program->min)
		{
			Program->up=1;
			Program->down=0;
		}
		if (pidValues->setValue>=Program->max)
		{
			Program->up=0;
			Program->down=1;
		}
		Program->timer=Program->duration;

		char cDebug[10];
		ltoa(pidValues->setValue,cDebug,10);
		uart_put_s(cDebug);
		
		uart_put_c(';');
		
		ltoa(Program->up,cDebug,10);
		uart_put_s(cDebug);
		
		uart_put_c(';');
		
		ltoa(Program->down,cDebug,10);
		uart_put_s(cDebug);
		
		uart_put_c('\n');
	}
	return 1;
}