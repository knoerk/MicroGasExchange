
#include "include/can.h"
// #define DEBUG_CAN

uint8_t mcp2515_read_register(uint8_t adress)
{
	uint8_t data=0;
	PORTB &= ~(1<<PB4);
	spi_put_c(SPI_READ);
	spi_put_c(adress);
	data = spi_put_c(0xA0);
	PORTB |= (1<<PB4);
	return data;
}

void mcp2515_write_register( uint8_t adress, uint8_t data )
{
	PORTB &= ~(1<<PB4);
	spi_put_c(SPI_WRITE);
	spi_put_c(adress);
	spi_put_c(data);
	PORTB |= (1<<PB4);
}

void mcp2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data)
{
	PORTB &= ~(1<<PB4);
	spi_put_c(SPI_BIT_MODIFY);
	spi_put_c(adress);
	spi_put_c(mask);
	spi_put_c(data);
	PORTB |= (1<<PB4);
}

#ifdef DEBUG_CAN
void CanDebug()
{
	uart_put_c('-');
	utoa(mcp2515_read_register(CANSTAT),cOut,2);
	uart_put_s(cOut);
	uart_put_c('-');
}
#endif

void mcp2515_init(uint16_t mask, uint16_t filter)
{

		PORTB &= ~(1<<PB2);
		spi_put_c(SPI_RESET);
		while ((mcp2515_read_register(CANSTAT) & 0xe0) != 0x80)
		{
		}
		PORTB |= (1<<PB2);
		delay(10);
		//BRP = 7
		mcp2515_bit_modify( CNF1, (1<<BRP0)|(1<<BRP1)|(1<<BRP2),  (1<<BRP0)|(1<<BRP1)|(1<<BRP2) );
		
		//	Prop Seg und Phase Seg1 einstellen
		mcp2515_bit_modify( CNF2,  (1<<BTLMODE) | (1<<PHSEG11), (1<<BTLMODE) | (1<<PHSEG11) );
		
		//  Wake-up Filter deaktivieren, Phase Seg2 einstellen
		mcp2515_bit_modify( CNF3, (1<<PHSEG21), (1<<PHSEG21) );
		
		// Aktivieren der Rx Buffer Interrupts
		mcp2515_bit_modify( CANINTE,  (1<<RX1IE) | (1<<RX0IE) | (1<<ERRIE), (1<<RX1IE) | (1<<RX0IE) | (1<<ERRIE) );

		
		//Empfangsmasken Einschalten:
		mcp2515_bit_modify( RXB0CTRL, (1<<RXM0) | (1<<RXM1) | (1<<BUKT), (1<<RXM0) | (1<<BUKT) );
		mcp2515_bit_modify( RXB1CTRL, (1<<RXM0) | (1<<RXM1), (1<<RXM0) ) ;
		
		//Masken setzen:
		mcp2515_write_register( RXM0SIDH, mask>>3 );
		mcp2515_bit_modify( RXM0SIDL, 0xE0,mask<<5 );
		
		mcp2515_write_register( RXM1SIDH, mask>>3 );
		mcp2515_bit_modify( RXM1SIDL, 0xE0,mask<<5 );
		
		//Filter setzen:
		mcp2515_bit_modify( RXF0SIDH, 0xFF, filter>>3 );
		mcp2515_bit_modify( RXF0SIDL, 224,filter<<5 );
		
		mcp2515_bit_modify( RXF1SIDH, 0xFF, filter>>3 );
		mcp2515_bit_modify( RXF1SIDL, 224,filter<<5 );
		
		mcp2515_bit_modify( RXF2SIDH, 0xFF, filter>>3 );
		mcp2515_bit_modify( RXF2SIDL, 224,filter<<5 );
		
		mcp2515_bit_modify( RXF3SIDH, 0xFF, filter>>3 );
		mcp2515_bit_modify( RXF3SIDL, 224,filter<<5 );
		
		mcp2515_bit_modify( RXF4SIDH, 0xFF, filter>>3 );
		mcp2515_bit_modify( RXF4SIDH, 224,filter<<5 );
		
		mcp2515_bit_modify( RXF5SIDH, 0xFF, filter>>3 );
		mcp2515_bit_modify( RXF5SIDH, 224,filter<<5 );
		
		
		// Deaktivieren der Pins RXnBF Pins (High Impedance State)
		mcp2515_bit_modify( BFPCTRL,0xFF, 0 );
		
		// TXnRTS Bits als Inputs schalten
		mcp2515_bit_modify( TXRTSCTRL,0xFF, 0 );
		
		// Device zurueck in den normalen Modus versetzten
		mcp2515_bit_modify( CANCTRL, 0xE0, 0);
		
		//Loopback modus
		//mcp2515_bit_modify( CANCTRL, 0xE0, 0b01000000);
		
		PORTB |= (1<<PB2);
}


uint8_t can_send_message(CANMessage *p_message)
{
	uint8_t status, address;
	
	// Status des MCP2515 auslesen
	PORTB &= ~(1<<PB4);
	spi_put_c(SPI_READ_STATUS);
	status = spi_put_c(0xff);
	spi_put_c(0xff);
	PORTB |= (1<<PB4);
	
	/* Statusbyte:
	*
	* Bit  Funktion
	*  2   TXB0CNTRL.TXREQ
	*  4   TXB1CNTRL.TXREQ
	*  6   TXB2CNTRL.TXREQ
	*/
	
	if (bit_is_clear(status, 2))
	{
		address = 0x00;
	}
	else if (bit_is_clear(status, 4))
	{
		address = 0x02;
	}
	else if (bit_is_clear(status, 6))
	{
		address = 0x04;
	}
	else
	{
		/* Alle Puffer sind belegt,
		Nachricht kann nicht verschickt werden */
		return 0;
	}
	
	PORTB &= ~(1<<PB4);    // CS Low
	spi_put_c(SPI_WRITE_TX | address);
	
	// Standard ID einstellen
	spi_put_c((uint8_t) (p_message->id>>3));
	spi_put_c((uint8_t) (p_message->id<<5));
	
	// Extended ID
	spi_put_c(0x00);
	spi_put_c(0x00);
	
	uint8_t length = p_message->length;
	
	if (length > 8)
	{
		length = 8;
	}
	
	// Ist die Nachricht ein "Remote Transmit Request" ?
	if (p_message->rtr)
	{
		/* Ein RTR hat zwar eine Laenge,
		aber enthaelt keine Daten */
		
		// Nachrichten Laenge + RTR einstellen
		spi_put_c((1<<RTR) | length);
	}
	else
	{
		// Nachrichten Laenge einstellen
		spi_put_c(length);
		
		// Daten
		for (uint8_t i=0;i<length;i++)
		{
			spi_put_c(p_message->data[i]);
		}
	}
	PORTB |= (1<<PB4);      // CS auf High
	
	asm volatile ("nop");
	
	/* CAN Nachricht verschicken
	die letzten drei Bit im RTS Kommando geben an welcher
	Puffer gesendet werden soll */
	PORTB &= ~(1<<PB4);    // CS wieder Low
	if (address == 0x00)
	{
		spi_put_c(SPI_RTS | 0x01);
	}
	else
	{
		spi_put_c(SPI_RTS | address);
	}
	PORTB |= (1<<PB4);      // CS auf High
	
	return 1;
}


uint8_t mcp2515_read_rx_status(void)
{
	uint8_t data;
	
	// /CS des MCP2515 auf Low ziehen
	PORTB &= ~(1<<PB4);
	
	spi_put_c(SPI_RX_STATUS);
	data = spi_put_c(0xff);
	
	// Die Daten werden noch einmal wiederholt gesendet,
	// man braucht also nur eins der beiden Bytes auswerten.
	spi_put_c(0xff);
	
	// /CS Leitung wieder freigeben
	PORTB |= (1<<PB4);
	
	return data;
}

uint8_t can_get_message(CANMessage *p_message)
{
	// Status auslesen
	uint8_t status = mcp2515_read_rx_status();

	if (bit_is_set(status,6))
	{
		// Nachricht in Puffer 0
		PORTB &= ~(1<<PB4);	    // CS Low
		spi_put_c(SPI_READ_RX);
	}
	else if (bit_is_set(status,7))
	{
		// Nachricht in Puffer 1
		PORTB &= ~(1<<PB4);    // CS Low
		spi_put_c(SPI_READ_RX | 0x04);
	}
	else
	{
		/* Fehler: Keine neue Nachricht vorhanden */
		return 0xff;
	}
	
	// Standard ID auslesen
	p_message->id =  (uint16_t) spi_put_c(0xff) << 3;
	p_message->id |= (uint16_t) spi_put_c(0xff) >> 5;
	
	spi_put_c(0xff);
	spi_put_c(0xff);
	
	// Laenge auslesen
	uint8_t length = spi_put_c(0xff) & 0x0f;
	p_message->length = length;
	
	// Daten auslesen
	for (uint8_t i=0;i<length;i++)
	{
		p_message->data[i] = spi_put_c(0xff);
	}
	
	PORTB |= (1<<PB4);
	
	if (bit_is_set(status,3))
	{
		p_message->rtr = 1;
	}
	else
	{
		p_message->rtr = 0;
	}
	
	// Interrupt Flag loeschen
	if (bit_is_set(status,6))
	{
		mcp2515_bit_modify(CANINTF, (1<<RX0IF), 0);
	}
	else
	{
		mcp2515_bit_modify(CANINTF, (1<<RX1IF), 0);
	}
	
	return (status);
}


uint8_t handleCanMessage(volatile sensValues* actualValues_1,volatile sensValues* actualValues_2)
{
	CANMessage inMessage;
	if (can_get_message(&inMessage) != 0xff)
	{
		unsigned char MessageSenderId=0;
		unsigned char MessageNumber=0;
		MessageSenderId = inMessage.id >> 4;
		MessageNumber = inMessage.id & 0b00001111;
		
		switch (MessageSenderId)
		{
			case 1:
			
			if ( (MessageNumber) == 1)
			{
				actualValues_1->boschTemp  =	(int16_t)inMessage.data[0]<<8;
				actualValues_1->boschTemp |=	(int16_t)inMessage.data[1];
				actualValues_1->co         =	(int16_t)inMessage.data[2]<<8;
				actualValues_1->co        |=	(int16_t)inMessage.data[3];
				actualValues_1->hytTemp    =	(uint16_t)inMessage.data[4]<<8;
				actualValues_1->hytTemp   |=	(uint16_t)inMessage.data[5];
				actualValues_1->feuchte    =	(uint16_t)inMessage.data[6]<<8;
				actualValues_1->feuchte   |=	(uint16_t)inMessage.data[7];
			}
			
			else if ( MessageNumber == 2)
			{
				actualValues_1->pressure =	 (int32_t)inMessage.data[0]<<24;
				actualValues_1->pressure |=	 (int32_t)inMessage.data[1]<<16;
				actualValues_1->pressure |=	 (int32_t)inMessage.data[2]<<8;
				actualValues_1->pressure |=  (int32_t)inMessage.data[3];
				actualValues_1->k30Status =	inMessage.data[4];
				actualValues_1->ppfd = (int16_t)inMessage.data[5]<<8;
				actualValues_1->ppfd |= (int16_t)inMessage.data[6];
				
			}
			else if (MessageNumber ==3 )
			{
				actualValues_1->RHO =  (int16_t)inMessage.data[0]<<8;
				actualValues_1->RHO |=  (int16_t)inMessage.data[1];
				actualValues_1->S =  (int16_t)inMessage.data[2]<<8;
				actualValues_1->S |=  (int16_t)inMessage.data[3];
				
				actualValues_1->AF   =  (int16_t)inMessage.data[4]<<8;
				actualValues_1->AF  |=  (int16_t)inMessage.data[5];
				actualValues_1->VPD   =  (int16_t)inMessage.data[6]<<8;
				actualValues_1->VPD  |=  (int16_t)inMessage.data[7];
			}
			
			break;
			
			
			case 2:
			
			if ( MessageNumber == 1 )
			{
				actualValues_2->boschTemp  =	(int16_t)inMessage.data[0]<<8;
				actualValues_2->boschTemp |=	(int16_t)inMessage.data[1];
				actualValues_2->co         =	(int16_t)inMessage.data[2]<<8;
				actualValues_2->co        |=	(int16_t)inMessage.data[3];
				actualValues_2->hytTemp    =	(uint16_t)inMessage.data[4]<<8;
				actualValues_2->hytTemp   |=	(uint16_t)inMessage.data[5];
				actualValues_2->feuchte    =	(uint16_t)inMessage.data[6]<<8;
				actualValues_2->feuchte   |=	(uint16_t)inMessage.data[7];
			}
			
			else if ( MessageNumber == 2 )
			{
				actualValues_2->pressure =	 (int32_t)inMessage.data[0]<<24;
				actualValues_2->pressure |=	 (int32_t)inMessage.data[1]<<16;
				actualValues_2->pressure |=	 (int32_t)inMessage.data[2]<<8;
				actualValues_2->pressure |=  (int32_t)inMessage.data[3];
				actualValues_2->k30Status =	inMessage.data[4];
				actualValues_2->ppfd = (int16_t)inMessage.data[5]<<8;
				actualValues_2->ppfd |= (int16_t)inMessage.data[6];
			}
			else if (MessageNumber ==3 )
			{
				actualValues_2->RHO =  (int16_t)inMessage.data[0]<<8;
				actualValues_2->RHO |=  (int16_t)inMessage.data[1];
				actualValues_2->S =  (int16_t)inMessage.data[2]<<8;
				actualValues_2->S |=  (int16_t)inMessage.data[3];
				actualValues_2->AF   =  (int16_t)inMessage.data[4]<<8;
				actualValues_2->AF  |=  (int16_t)inMessage.data[5];
				actualValues_2->VPD   =  (int16_t)inMessage.data[6]<<8;
				actualValues_2->VPD  |=  (int16_t)inMessage.data[7];
			}
			
			break;
			
			default:
			
			break;
		}
		return 1;
	}
	else if (mcp2515_read_register(CANINTF) & (1<<ERRIF) )
	{
		CanErrorStatus=mcp2515_read_register(EFLG);
		mcp2515_bit_modify(EFLG, CanErrorStatus, CanErrorStatus);
		mcp2515_bit_modify(CANINTF, 1<<ERRIF, 1<<ERRIF);
		return 0;
	}
	can_new_interrupt=0;
	return 0;
}