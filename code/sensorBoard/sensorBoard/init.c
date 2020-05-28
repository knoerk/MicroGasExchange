
#include "include/sensorBoard.h"


void init (volatile sensValues* actualValues)
{
	//Timer2 fuer Zeit:
	TCCR2A |= (1<<WGM21);
	TCCR2B |= ( (1<<CS21) | (1<<CS20) );
	TIMSK2 |= (1<<OCIE2A);
	OCR2A = 250;
	
	//Can Interrupt:
	DDRD  &= ~(1<<DDD3);
	//PORTD |= ~(1<<PD3);
	EICRA |= (1<<ISC11);
	EIMSK |= (1<<INT1) ;
	
	//Taster Interrupt:
	DDRD  &= ~(1<<DDD2);
	PORTD |=  (1<<PD2);
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0) ;
		
	//LEDs:
	DDRD |= (1<<DDD7) ;
	DDRB |= (1<<DDB0) ;

	//TWI HUB
	DDRC |=  ((1<<DDC2) | (1<<DDC3));
	PORTC &= ~(1<<PC3);
	PORTC &= ~(1<<PC2);
	
	//ADC-Pins

	DDRC   &= ~(1<<DDC0);
	DDRC   &= ~(1<<DDC1);

	//ADC-VRef
	ADMUX  |=  (1<<REFS0) ;
	ADMUX  &=  ~(1<<REFS1) ;
	ADCSRA |= (1<<ADEN)  ;
	DIDR0|= (1<<ADC0D) | (1<<ADC1D);
	
	
	entprellsperre=0;
	
	sei();
	
	uart_init(51);
	twi_init();	
	_delay_ms(10);
	spi_init();
	_delay_ms(1);
	mcp2515_init(0X7FF,senderID<<4);
	
	AC1=0;
	AC2=0;
	AC3=0;
	AC4=0;
	AC5=0;
	AC6=0;
	B1=0;
	B2=0;
	MB=0;
	MC=0;
	MD=0;
	
	actualValues->boschTemp=-9999;
	actualValues->co=-9999;
	actualValues->feuchte=-9999;
	actualValues->hytTemp=-9999;
	actualValues->k30Status=0;
	actualValues->ppfd=-9999;
	actualValues->pressure=-9999;
	actualValues->RHO=-9999;
	actualValues->S=-9999;
	actualValues->AF=-9999;
	actualValues->VPD=-9999;
	
	actualValues->Mppfd=0;
	actualValues->Mco=0;
	actualValues->MhytTemp=0;
	actualValues->Mfeuchte=0;
	actualValues->Mpressure=0;
	actualValues->MboschTemp=0;
	actualValues->MRHO=0;
	actualValues->MS=0;
	actualValues->MAF=0;
	actualValues->MVPD=0;
	
	actualValues->Bppfd=0;
	actualValues->Bco=0;
	actualValues->BhytTemp=0;
	actualValues->Bfeuchte=0;
	actualValues->Bpressure=0;
	actualValues->BboschTemp=0;
	actualValues->BRHO=0;
	actualValues->BS=0;
	actualValues->BAF=0;
	actualValues->BVPD=0;
	
	actualValues->BppfdCounter=0;
	actualValues->BcoCounter=0;
	actualValues->BhytTempCounter=0;
	actualValues->BfeuchteCounter=0;
	actualValues->BpressureCounter=0;
	actualValues->BboschTempCounter=0;
	actualValues->BRHOCounter=0;
	actualValues->BSCounter=0;
	actualValues->BAFCounter=0;
	actualValues->BVPDCounter=0;
	
	actualValues->BufferCounter=0;
	actualValues->status=0;
	
	can_new_message=0;
	can_new_interrupt=0;
	send_always=1;
	message_request=0;
	intervall=10;
	meansRequest=0;
	CanErrorStatus=0;
}