

#include "include/uart.h"

void uart_init (uint16_t ubrr)
{
    UBRRH &= ~(1<<URSEL);
	UBRRH = (unsigned char)(ubrr>>8);
    UBRRL = (unsigned char)ubrr;
    UCSRB |= ( (1<<RXEN) | (1<<TXEN) | (1<<RXCIE) );
    UCSRC |= ( (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0) | (1<<USBS)); // URSEL = 1 when writing to UCSRC!!
    //OSCCAL=110;
}

void uart_put_c(char c)
{
    while (!(UCSRA & (1<<UDRE)))
    {
    }
    UDR = c;
}

void uart_put_s (char *s)
{
    while (*s)
    {
        uart_put_c(*s);
        s++;
    }
}

char receive_byte (void)
{
    while (!(UCSRA & (1 << RXC)));
    {
    }
    return UDR;
}

ISR(USART_RXC_vect)
{
    unsigned char temp=UDR;

    switch (temp)
    {
    case '#':
        uart_struct.uart_state=rec_value;
        uart_struct.buffer_count=0;
        break;

    case '\0':
        if (uart_struct.uart_state==rec_value && uart_struct.buffer_count>=1)
        {
            uart_struct.uart_buffer[uart_struct.buffer_count]=temp;
            uart_struct.uart_state=string_complete;
            uart_struct.buffer_count++;
        }
        if (uart_struct.uart_state==rec_value && uart_struct.buffer_count<1)
        {
            uart_struct.uart_state=no_string;
            uart_struct.buffer_count=0;
        }
        break;

    default:

        if (uart_struct.uart_state==rec_value && uart_struct.buffer_count<=19)
        {
            uart_struct.uart_buffer[uart_struct.buffer_count]=temp;
            uart_struct.buffer_count++;
        }
        if (uart_struct.uart_state==rec_value && uart_struct.buffer_count>9)
        {
            uart_struct.uart_state=no_string;
            uart_struct.buffer_count=0;
        }
    }
}


