

#include "include/I2C.h"


//#define DEBUG_TWI  //EEPROM Functions won't work


int twi_init()
{
    TWSR |= (1<<TWPS1);
    TWSR |=  (1<<TWPS0);
    TWBR = 1;
    return TWSR;
}


uint8_t* i2c_comm (volatile uint8_t* buffer,uint8_t write_length,uint8_t read_length,uint8_t rs)
{
    I2CBuffer.write_buffer=(uint8_t*)buffer;
    I2CBuffer.inpos=(uint8_t*)buffer;

    I2CBuffer.rs=rs;
    I2CBuffer.position=0;
    I2CBuffer.succesBit=9;

    I2CBuffer.read_length=read_length;
    I2CBuffer.write_length=write_length;

    TWCR = ( (1<<TWEN) | (1<<TWSTA) | (1<<TWINT) | (1<<TWIE) );
	
	milisecCounter2=0;
    while (I2CBuffer.succesBit==9)
    {
		if (milisecCounter2>=20)
		{
			I2CBuffer.succesBit=3;
		}
    }
	if (I2CBuffer.succesBit)
	{
		//TwiReset();
	}
    return (uint8_t*) I2CBuffer.read_buffer;
}


ISR(TWI_vect)
{
	#ifdef DEBUG_TWI
    char deb[8];
    char db[6];
    utoa(TWSR&0xF8,db,16);
    uart_put_s("TWSR: ");
    uart_put_s(db);
    uart_put_c('-');
    utoa(TWDR,deb,2);
    uart_put_s(deb);
    uart_put_c('\n');
	#endif
	
	
    uint8_t twi_status = TWSR&0xF8;
    switch (twi_status)
    {
    case 0x08:								//start transmitted
        if ( (I2CBuffer.position==I2CBuffer.write_length) && I2CBuffer.read_length)
        {
            I2CBuffer.write_buffer=I2CBuffer.inpos;
            *I2CBuffer.write_buffer |= 1;
            I2CBuffer.position=0;
            TWDR = *I2CBuffer.write_buffer;
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
        }
        else
        {
            I2CBuffer.position=0;
            I2CBuffer.write_buffer=I2CBuffer.inpos;
            TWDR = *I2CBuffer.write_buffer;
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
            I2CBuffer.write_buffer++;
            I2CBuffer.position++;
        }
        break;

    case 0x10:
        if (I2CBuffer.position==I2CBuffer.write_length && I2CBuffer.read_length)
        {
            I2CBuffer.write_buffer=I2CBuffer.inpos;
            *I2CBuffer.write_buffer |= 1;
            I2CBuffer.position=0;
            TWDR = *I2CBuffer.write_buffer;
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
        }
        else
        {
            //rep start transmitted
            I2CBuffer.position=0;
            I2CBuffer.write_buffer=I2CBuffer.inpos;
            TWDR = *I2CBuffer.write_buffer;
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
        }
        break;

    case 0x18:										//SLA+W transmitted ACK received
        if (I2CBuffer.position==I2CBuffer.write_length && !I2CBuffer.read_length)
        {
            TWCR = ( (1<<TWINT) | (1<<TWSTO) );
            I2CBuffer.succesBit=0;
        }
        else if (I2CBuffer.position==I2CBuffer.write_length && I2CBuffer.read_length)
        {
            TWCR = ( (1<<TWINT) | (1<<TWSTA)  | (1<<TWEN) | (1<<TWIE) | (1<<TWSTO) );//
        }
        else
        {
            TWDR = *I2CBuffer.write_buffer;
            I2CBuffer.write_buffer++;
            I2CBuffer.position++;
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
        }
        break;

    case 0x20:										//SLA+W transmitted NACK received
        TWCR = ( (1<<TWINT) | (1<<TWSTO) );
        I2CBuffer.succesBit=2;
        break;

    case 0x28:										//Data byte transmitted ACK received
        if (I2CBuffer.position==I2CBuffer.write_length && !I2CBuffer.read_length)
        {
            TWCR = ( (1<<TWINT) | (1<<TWSTO) | (1<<TWEN));
            I2CBuffer.succesBit=0;
        }
        else if (I2CBuffer.position==I2CBuffer.write_length && I2CBuffer.read_length && !I2CBuffer.rs)
        {
            TWCR = ( (1<<TWINT) | (1<<TWSTA)  | (1<<TWSTO)| (1<<TWEN) | (1<<TWIE) );
        }
        else if (I2CBuffer.position==I2CBuffer.write_length && I2CBuffer.read_length && I2CBuffer.rs)
        {
            TWCR = ( (1<<TWINT) | (1<<TWSTA)  | (1<<TWEN) | (1<<TWIE) );
        }
        else
        {
            TWDR = *I2CBuffer.write_buffer;
            I2CBuffer.write_buffer++;
            I2CBuffer.position++;
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
        }
        break;

    case 0x30:										//Data byte transmitted NACK received
        TWCR = ( (1<<TWINT) | (1<<TWSTO) );
        I2CBuffer.succesBit=2;

        break;

    case 0x38:										//Arbitration lost in SLA+W or data bytes
        TWCR = (1<<TWINT);
        break;

    case 0x40:										//SLA+R transmitted ACK
        if (I2CBuffer.read_length==1)
        {
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
        }
        else
        {
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA) );
        }
        break;

    case 0x48: 										//SLA+R transmitted NACK
        TWCR = ( (1<<TWINT) | (1<<TWSTO) );
        I2CBuffer.succesBit=2;
        break;

    case 0x50:										 //Data byte received ACK returned
	
        I2CBuffer.read_buffer[I2CBuffer.position++]=TWDR;

        if (I2CBuffer.position==I2CBuffer.read_length-1)
        {
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) );
        }
        else
        {
            TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA) );
        }
        break;

    case 0x58:										//Data byte received NACK returned
        I2CBuffer.read_buffer[I2CBuffer.position]=TWDR;
        TWCR = ( (1<<TWINT) | (1<<TWSTO) );
        I2CBuffer.succesBit=0;
        break;

    case 0x00:										//BUS ERROR
        TWCR = ( (1<<TWINT) | (1<<TWSTO) );
        I2CBuffer.succesBit=1;
        break;

    default:
        TWCR = ( (1<<TWINT) | (1<<TWSTO) );
        I2CBuffer.succesBit=1;
        break;
    }
}


void TwiReset ()
{
	
	//SDA= PC4
	//SCL= PC5
	
	TWCR &= ~(1<<TWEN);
	DDRC |= ( (1<<PC4) | (1<<PC5) );
	
	PORTC &= ~(1<<PC4);
	for (uint8_t i =0; i<9 ; i++)
	{	
		PORTC |= (1<<PC5);
		delay(1);
		PORTC &= ~(1<<PC5);
		delay(1);
	}
	PORTC |= (1<<PC5);
	delay(1);
	PORTC |= (1<<PC5);
	
	twi_init();
	//TWCR = ( (1<<TWEN) | (1<<TWINT) | (1<<TWSTO) );
}


void display_status()
{
    char c_TWSR[10]="000";
    utoa (TWSR&0xF8,c_TWSR,16);
    uart_put_s(c_TWSR);
    uart_put_c('\n');
}
