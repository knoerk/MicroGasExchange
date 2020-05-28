
#include "include/controlBoard.h"

void init ()
{
	//Timer0 fuer Zeit:
	TCCR0 |= (1<<WGM01);
	TCCR0 |= ( (1<<CS01));// | (1<<CS00) );		//clkT2S/64
	TIMSK |= (1<<OCIE0);
	OCR0 = 125;
	
	//Timer1 fuer Heiz innen und aussen
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10); //PWM phase correct 8-bit; Clear OC1A+OC1B on compare match when up-counting
	TCCR1B |= (1<<CS10) | (1<<CS12);				//Prescaler = 1024
	OCR1A=0;
	OCR1B=0;
	
	//Timer2 fuer Feucht
	TCCR2 |= (1<<WGM20) | (1<<COM21) | (1<<CS21) ; //PWM phase correct ; Clear OC2 on compare match when up-counting, PS = 8
	OCR2=0;
	
	//Timer3:
	TIMER3.TCNT=0;
	TIMER3.OCRA=0;
	TIMER3.OCRB=0;
	TIMER3.OCRC=0;
	TIMER3.OCRD=100;
	
	//Can Interrupt:
	DDRB  &= ~(1<<DDB2);
	GICR |= (1<<INT2) ;
	MCUCSR &= ~(1<<ISC2);
	
	
	//Taster Interrupt:
	DDRD  &= ~(1<<DDD2) | (1<<DDD3);
	PORTD |=  (1<<PD2) | (1<<PD3);
	MCUCR |= (1<<ISC00) | (1<<ISC01) | (1<<ISC10) | (1<<ISC11);
	GICR |= (1<<INT0) | (1<<INT1);
	
	//Outputs:
	DDRD |= ( (1<<DDD4) | (1<<DDD5) | (1<<DDD6) | (1<<DDD7) );
	DDRC |= ( (1<<DDC2) | (1<<DDC4) | (1<<DDC5) | (1<<DDC6) | (1<<DDC7) );
	
	PORTD &= ~( (1<< PD4) | (1<< PD5) | (1<< PD6) | (1<< PD7) );
	PORTC &= ~( (1<< PC4) | (1<< PC5) | (1<< PC6) | (1<< PC7) );
	
	PORTD |= (1<< PD7);
	PORTC |= (1<< PC2);
	//ADC-Pins
	//PINC  &= ~(1<<PC0);
	//PINC  &= ~(1<<PC1);
	//DDRC   &= ~(1<<DDC0);
	//DDRC   &= ~(1<<DDC1);

	//ADC-VRef
	ADMUX  |=  (1<<REFS0) ;
	ADMUX  &=  ~(1<<REFS1) ;
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) ;
	
	
	entprellsperre=0;
	HUMmode=specHum_in;
	
	init_PID_values(&PID_values_preHeat,48,2,92,0,0,250,1,32,0);  //OCRA1
	init_PID_values(&PID_values_inHeat,64,1,512,0,0,250,1,32,0);	//OCR1B
	init_PID_values(&PID_values_specHum_in,8,0,1,0,10,10000,1,128,0);	//OCR2
	init_PID_values(&PID_values_vpd_in,12,0,128,6000,10,2000,1,16,1);	//OCR2
	init_PID_values(&PID_values_co2,5,1,3,10,10,3500,1,64,0);
		
	sei();
	
	uart_init(8);
	twi_init();
	spi_init();
	delay(1);
	mcp2515_init(0,0);
				
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

	PCF8574_byte=0;
	
	can_new_message=0;
	can_new_interrupt=0;
	buffer_update_flag=0;
	
	treatment=0;
	repetition=0;
	tick=1;
	saveToEpromEnabled=0;
	memoryAdress=64;
	CanErrorStatus=0;
	
	sTime.days=0;
	sTime.daySecs=1;
	sTime.daySecsTEMP=0;
}

