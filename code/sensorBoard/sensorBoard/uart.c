

#include "include/uart.h"

void uart_init (uint16_t ubrr)
{
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B |= ( (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) );
    UCSR0C |= ( (1<<UCSZ01) | (1<<UCSZ00) | (1<<USBS0));
    //OSCCAL=110;
}

void uart_put_c(char c)
{
    while (!(UCSR0A & (1<<UDRE0)))
    {
    }
    UDR0 = c;
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
    while (!(UCSR0A & (1 << RXC0)));
    {
    }
    return UDR0;
}

ISR(USART_RX_vect)
{
    unsigned char temp=UDR0;

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

        if (uart_struct.uart_state==rec_value && uart_struct.buffer_count<=9)
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


