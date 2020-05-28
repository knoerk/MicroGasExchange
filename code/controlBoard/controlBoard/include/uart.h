

#ifndef SC_UART_H_
#define SC_UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

void uart_init (uint16_t ubrr);
void uart_put_c(char c);
void uart_put_s (char *s);
char receive_byte (void);
void receive_command();

enum u_state
{
	no_string=0,
	rec_value=1,
	string_complete=2,
};	

typedef struct
{
	enum u_state uart_state; uint8_t buffer_count;	char uart_buffer[20];
} u_struct;	

volatile u_struct uart_struct;


#endif /* SC_UART_H_ */