

#ifndef SC_UART_H_
#define SC_UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

enum u_state
{
	no_string=0,
	rec_value=1,
	string_complete=2,
};	

typedef struct
{
	enum u_state uart_state; uint8_t buffer_count;	char uart_buffer[10];
} u_struct;	


volatile u_struct uart_struct;
extern volatile uint16_t milisecCounter2;

void uart_init (uint16_t ubrr);
void uart_put_c(char c);
void uart_put_s (char *s);
char receive_byte (void);
void receive_command();

#endif /* SC_UART_H_ */