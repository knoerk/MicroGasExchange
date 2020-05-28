

#include "include/ADC.h"

uint16_t adc_read (uint8_t mux)
{

	uint16_t result=0;
	uint8_t e=0;
	ADMUX &= ~(15<<0);
	ADMUX |= mux;
	//ADMUX |=(1<<ADLAR);
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADPS2)| (1<<ADPS0);

	while (ADCSRA & (1<<ADSC))
	{
	}
	for (e=0; e<4; e++)
	{
		ADCSRA |=  (1<<ADSC);
		while (ADCSRA & (1<<ADSC))
		{
		}
		result+=ADCW;
	}
	
	result=(result/4);
	
	ADCSRA &= ~(1<<ADEN);
	return result;
}