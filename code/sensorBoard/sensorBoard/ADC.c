
#include "include/ADC.h"



uint16_t adc_read (uint8_t mux)
{

	uint32_t result=0;
	uint8_t e=0;
	ADMUX &= ~(15<<0);
	ADMUX |= mux;
	ADCSRA |=  (1<<ADSC)| (1<<ADPS0)| (1<<ADPS1)| (1<<ADPS2);
	
	while (ADCSRA & (1<<ADSC))
	{
	}
	
	for (e=0; e<24; e++)
	{
		ADCSRA |=  (1<<ADSC);
		while (ADCSRA & (1<<ADSC))
		{
		}
		result+=ADCW;
	}
	
	result=(result/24);
	
	//ADCSRA &= ~(1<<ADEN);
	return result;
}