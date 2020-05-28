

#include "include/SPI.h"

void spi_init()
{
	// Aktivieren der Pins für das SPI Interface
	
	DDRB   |= (1<<DDB4);
	PORTB  |= (1<<PB4);	
	
	DDRB  |= (1<<DDB5) | (1<<DDB7);
	PORTB &= ~( (1<<PB5) | (1<<PB6) | (1<<PB7) );
	

	
	// Aktivieren des SPI Master Interfaces, fosc = fclk / 16
	SPCR = ( (1<<SPE) | (1<<MSTR)  |(0<<SPR0) );
	SPSR = (1<<SPI2X);
}


uint8_t spi_put_c( uint8_t data )
{
		while( ( SPSR & (1<<SPIF) ) )
		{
		}
	
		SPDR = data;

		while( !( SPSR & (1<<SPIF) ) )
		{
		}
				
		return SPDR;
}





