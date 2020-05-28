/*
 * can.h
 *
 * Created: 04.12.2013 20:16:46
 *  Author: knoerk
 */ 


#ifndef CAN_H_
#define CAN_H_


#include <avr/io.h>
#include <util/atomic.h>
#include "sensValues.h"
#include "SPI.h"
#include "mcp2515_defs.h"
#include "simple_delay.h"


typedef struct
{
	uint16_t  id;
	uint8_t   rtr;
	uint8_t   length;
	uint8_t   data[8];
} CANMessage;

uint8_t handleCanMessage(volatile sensValues* acualVales);
void sendValuesViaCan (volatile sensValues values);
void sendMeanValuesViaCan (volatile sensValues values);
void mcp2515_init(uint16_t mask, uint16_t filter);
void mcp2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data);
void mcp2515_write_register( uint8_t adress, uint8_t data );
uint8_t mcp2515_read_register(uint8_t adress);
uint8_t can_send_message(CANMessage *p_message);
uint8_t can_get_message(CANMessage *p_message);
uint8_t mcp2515_read_rx_status(void);

#endif /* CAN_H_ */



