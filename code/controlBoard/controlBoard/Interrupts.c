

#include "include/interrupts.h"


ISR(TIMER0_COMP_vect)
{
	milisecCounter++;
	if (milisecCounter>=7976)
	{
		milisecCounter=0;
		tick=1;
		sTime.daySecs++;
	}


	if (entprellsperre)
	{
		entprellsperre--;
	}

	if (!(milisecCounter%8))
	{
		milisecCounter2++;
		milisecCounter3++;
		milisecCounter4++;		
	}

	
	if (TIMER3.TCNT > 99)
	{
		TIMER3.TCNT=0;
	}
	
	if ( (TIMER3.TCNT>= TIMER3.OCRA) && (TIMER3.OCRA != 100) )
	{
		PORTC &= ~(1<<PC7);
	}
	if ( (TIMER3.TCNT>= TIMER3.OCRB) && (TIMER3.OCRB != 100) )
	{
		PORTC &= ~(1<<PC6);
	}
	if ( (TIMER3.TCNT>= TIMER3.OCRC) && (TIMER3.OCRC != 100) )
	{
		PORTC &= ~(1<<PC5);
	}
	if ( (TIMER3.TCNT>= TIMER3.OCRD) && (TIMER3.OCRD != 100) )
	{
		PORTC &= ~(1<<PC4);
	}

	if (TIMER3.TCNT == 0)
	{
		if ( TIMER3.OCRA )
		{
			PORTC |= (1<<PC7);
		}
		if ( TIMER3.OCRB )
		{
			PORTC |= (1<<PC6);
		}
		if ( TIMER3.OCRC )
		{
			PORTC |= (1<<PC5);
		}
		if ( TIMER3.OCRD )
		{
			PORTC |= (1<<PC4);
		}
	}
	TIMER3.TCNT++;
}


ISR(INT0_vect)
{
	if (!entprellsperre)
	{
		entprellsperre=200;
		saveToEpromEnabled ^= (1<<0);
	}
	GIFR |= (1<<INTF0);
}


ISR(INT1_vect)
{
	if (!entprellsperre)
	{
		entprellsperre=200;
		PORTD ^= (1<< PD7);
	}
	GIFR |= (1<<INTF1);
}


ISR(INT2_vect)
{
	can_new_interrupt=1;
}








