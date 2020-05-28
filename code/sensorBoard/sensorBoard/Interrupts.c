

#include "include/Interrupts.h"

ISR(TIMER2_COMPA_vect)
{
    milisecCounter++;
    if (milisecCounter>=997)
    {
        milisecCounter=0;
        tick=1;
        sTime.daySecs++;
	}

		
    if (entprellsperre)
    {
        entprellsperre--;
    }
    milisecCounter2++;
	milisecCounter3++;
	milisecCounter4++;
}


ISR(INT0_vect)
{
    if (!entprellsperre)
    {
		entprellsperre=200;	
		send_always ^= (1<<0);
    }

    EIFR |= (1<<INT0);
}

ISR(INT1_vect)
{
		can_new_interrupt=1;
}








