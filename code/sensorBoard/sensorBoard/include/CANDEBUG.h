/*
 * CANDEBUG.h
 *
 * Created: 07.12.2013 12:05:20
 *  Author: knoerk
 */ 


#ifndef CANDEBUG_H_
#define CANDEBUG_H_


			case 'C':
			{
				mcp2515_bit_modify( CANCTRL, 0xE0, 0b10000000);
			}
			break;
			
			case 'N':
			{
				mcp2515_bit_modify( CANCTRL, 0xE0, 0);
			}
			break;
			
			case 'L':
			{
				mcp2515_bit_modify( CANCTRL, 0xE0, 0b01000000);
			}
			break;
			
			case 'I':
			{
				mcp2515_init() ;
			}
			break;
			
			case 'R':
			{
				PORTB &= ~(1<<PB2);
				delay(1);
				spi_put_c(SPI_RESET);
				delay(1);
				PORTB |= (1<<PB2);
			}
			break;
			
			case 'S':
			{
				mcp2515_bit_modify( CANCTRL, 0xE0, 0b00100000);
			}
			break;
			
			case 'W':
			{
				mcp2515_bit_modify( CANINTF, (1<<RX0IE), (1<<RX0IF) );
			}
			break;
			
			
			case 'E':
			{
				mcp2515_bit_modify( CANINTE, 0xff, 0xff );
			}
			break;
			
			case 'w':
			{
				mcp2515_write_register( value, 0b11111111 );
			}
			break;
			
			case 'q':
			{
				mcp2515_bit_modify( value,0x60, 0x60 );
			}
			break;
			
			
			case 'r':
			{
				uart_put_c('\n');
				char cOut[10];
				utoa(mcp2515_read_register(value),cOut,2);
				uart_put_s(cOut);
				uart_put_c('\n');
			}
			break;
			
			
			case 'c':
			{
							
				PORTB &= ~(1<<PB2);
				_delay_ms(1);
				//mcp2515_bit_modify( CANCTRL, 0xE0, 0b1000000);
				spi_put_c(SPI_RESET);
				_delay_ms(1);
	

				while ((mcp2515_read_register(CANSTAT) & 0xe0) != 0x80)
				{
					// wait for the new mode to become active
					uart_put_c('y');
				}
	
				PORTB |= (1<<PB2);
				_delay_ms(10);
			}
			break;
						
			case 'v':
			{
				//BRP = 7
				mcp2515_bit_modify( CNF1, (1<<BRP0)|(1<<BRP1)|(1<<BRP2),  (1<<BRP0)|(1<<BRP1)|(1<<BRP2) );
			}
			break;
						
			case 'b':
			{
					//	Prop Seg und Phase Seg1 einstellen
						mcp2515_bit_modify( CNF2,  (1<<BTLMODE) | (1<<PHSEG11), (1<<BTLMODE) | (1<<PHSEG11) );					
			}
			break;
						
			case 'n':
			{
					//  Wake-up Filter deaktivieren, Phase Seg2 einstellen
					mcp2515_bit_modify( CNF3, (1<<PHSEG21), (1<<PHSEG21) );
			}
			break;
						
			case 'm':
			{
					// Aktivieren der Rx Buffer Interrupts
					mcp2515_bit_modify( CANINTE,  (1<<RX1IE)|(1<<RX0IE) , (1<<RX1IE)|(1<<RX0IE) );
			}
			break;

			case ',':
			{
				// Aktivieren der Rx Buffer Interrupts
					mcp2515_write_register( RXB0CTRL, (1<<RXM1)|(1<<RXM0) );
			}
			break;
						
			case '.':
			{
				// Aktivieren der Rx Buffer Interrupts
				mcp2515_write_register( RXB1CTRL, (1<<RXM1)|(1<<RXM0) );
			}
			break;
#endif /* CANDEBUG_H_ */