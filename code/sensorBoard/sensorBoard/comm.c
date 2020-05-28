
#include "include/comm.h"

#define Special_Functions
//#define debug_can




void bmp_get_cal()
{
	uint8_t *values;
	volatile uint8_t data[3];
	
	if (1)
	{
		data[0]=238;
		data[1]=0xAA;
		PORTC |= (1<<PC3);
		values=i2c_comm(data, 2,22,1);
		PORTC &= ~(1<<PC3);

		AC1 = (int16_t)( ( ( (uint16_t)(values[0]) )<<8 ) | values[1] );
		AC2 = (int16_t)( ( ( (uint16_t)(values[2]) )<<8 ) | values[3] );
		AC3 = (int16_t)( ( ( (uint16_t)(values[4]) )<<8 ) | values[5] );
		AC4 = (((uint16_t)values[6])<<8) | values[7];
		AC5 = (((uint16_t)values[8])<<8) | values[9];
		AC6 = (((uint16_t)values[10])<<8) | values[11];
		B1 = (int16_t)( ( ( (uint16_t)(values[12]) )<<8 ) | values[13] );
		B2 = (int16_t)( ( ( (uint16_t)(values[14]) )<<8 ) | values[15] );
		MB = (int16_t)( ( ( (uint16_t)(values[16]) )<<8 ) | values[17] );
		MC = (int16_t)( ( ( (uint16_t)(values[18]) )<<8 ) | values[19] );
		MD = (int16_t)( ( ( (uint16_t)(values[20]) )<<8 ) | values[21] );
	}
}

void bmp_reset()
{
	volatile uint8_t data[3];
	data[0]=238;
	data[1]=0xE0;
	data[2]=0xB6;
	PORTC |= (1<<PC3);
	i2c_comm(data, 2,0,0);
	PORTC &= ~(1<<PC3);
}

void bmp_get_values(volatile int16_t *temp,volatile int32_t *pressure)
{
	uint8_t *values;
	uint8_t oss = 3;
	volatile uint8_t data[3];
	
	data[0]=238;
	data[1]=0xF4;
	data[2]=0x2E;
	TWBR = 1;
	PORTC |= (1<<PC3);
	
	uint8_t count=0;
	do
	{
		i2c_comm(data, 3,0,0);
		count++;
	} while (I2CBuffer.succesBit && (count<3) );
	
	simple_delay(30);
	
	data[0]=238;
	data[1]=0xF6;
	
	count=0;
	do
	{
		values=i2c_comm(data, 2,2,1);
		simple_delay(1);
		count++;
	} while (I2CBuffer.succesBit && (count<3) );
	
	simple_delay(30);
	int32_t UT = (uint32_t) ( ( (  (uint16_t)values[0] )<<8 ) | values[1] );
	
	data[0]=238;
	data[1]=0xF4;
	data[2]=0x34 + (oss<<6);
	count=0;
	do
	{
		i2c_comm(data, 3,0,0);
		simple_delay(1);
		count++;
	} while (I2CBuffer.succesBit && (count<3) );
	
	simple_delay(30);
	
	data[0]=238;
	data[1]=0xF6;
	
	count=0;
	do
	{
		values=i2c_comm(data, 2,3,1);
		simple_delay(1);
		count++;
	} while (I2CBuffer.succesBit && (count<3) );


	PORTC &= ~(1<<PC3);
	if (I2CBuffer.succesBit==0)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			int32_t UP =  ( ( ( (uint32_t)values[0] )<<16) | ( ( (uint16_t)values[1])<<8 ) | values[2] ) >> (8-oss) ;
			
			int32_t X1, X2, B5, B6, X3, B3, p;//,t,pressure;
			uint32_t B4, B7;
			
			X1 = ((int32_t)UT - (int32_t)AC6) * (int32_t)AC5 >> 15;
			X2 = ((int32_t)MC << 11) / (X1 + MD);
			B5 = X1 + X2;
			*temp = (int16_t) ( (B5 + 8) >> 4);
			
			B6 = B5 - 4000;
			X1 = (B2 * ((B6 * B6) >> 12)) >> 11;
			X2 = (AC2 * B6) >> 11;
			X3 = X1 + X2;
			B3 = (((((int32_t) AC1) * 4 + X3)<<oss) + 2)>> 2;
			X1 = (AC3 * B6) >> 13;
			X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
			X3 = ((X1 + X2) + 2) >> 2;
			B4 = (AC4 * (uint32_t) (X3 + 32768)) >> 15;
			B7 = ((uint32_t) (UP - B3) * (50000 >> oss));
			//p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
			
			if (B7 < 0x80000000)
			{
				p = (B7 << 1) / B4;
			}
			else
			{
				p = (B7 / B4) << 1;
			}

			X1 = (p >> 8) * (p >> 8);
			X1 = (X1 * 3038) >> 16;
			X2 = (-7357 * p) >> 16;
			*pressure = p + ((X1 + X2 + 3791) >> 4);
		}
	}
	else
	{
		*temp = - 9999;
		*pressure = -9999;
	}
}



uint8_t k30_get_values(volatile int16_t* co,volatile uint8_t* status)
{
	TWBR = 16;
	PORTC |= (1<<PC2);

	volatile uint8_t data[5];
	data[0]=208;
	data[1]=0x22;
	data[2]=0x00;
	data[3]=0x08;
	data[4]=0x2A;
	*status=0;

	
	volatile uint8_t *values;
	values=0;
	
	milisecCounter3=0;
	do
	{
		i2c_comm(data, 5,0,0);
		simple_delay(30);
		if (I2CBuffer.succesBit==0)
		{
			values=i2c_comm(data,0,4,0);
			if (!I2CBuffer.succesBit)
			{
				break;
			}
			else
			{
				simple_delay(30);
			}
		}
	} while ( (I2CBuffer.succesBit) && (milisecCounter3 < 200) );

	
	PORTC &= ~(1<<PC2);
	TWBR = 1;

	
	if(I2CBuffer.succesBit==0)
	{
		if ( values[0] & 0b00000001 )
		{
			*status = values[0];
			*co=(int16_t)values[2];
			*co |= (int16_t) (values[1]<<8);
			*co = *co ;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		*co=-9999;
		return 0;
	}
}


uint8_t hyt_get_values(volatile int16_t* hytTemp,volatile int16_t* feuchte)
{
	int32_t tmpTemp=0;
	int32_t tmpFeuchte=0;
	volatile uint8_t data[1];
	data[0]=80;//80;
	uint8_t *values;
	

	simple_delay(5);
	i2c_comm(data, 1,0,0);
	do
	{
		simple_delay(5);
		values= i2c_comm(data, 0,4,0);
	}
	while ( (values[0] & 0b01000000) && milisecCounter3<200);


	if(I2CBuffer.succesBit==0)
	{
		values[0] &= 0b00111111;
		values[3]  = (values[3]>>2);
		values[3] |= (values[2]<<6);
		values[2]  = (values[2]>>2);

		tmpFeuchte = values[0]<<8;
		tmpFeuchte |= values[1];

		tmpTemp = values[2]<<8;
		tmpTemp |= values[3];

		tmpTemp= ( ( ( tmpTemp * 16500) + 8192) >> 14 ) -4000;
		tmpFeuchte= ( ( ( tmpFeuchte * 10000) + 8192) >> 14 );
		*hytTemp=(int16_t)tmpTemp;
		*feuchte=(int16_t)tmpFeuchte;
		
		twi_error_flag=0;
	}
	else if (I2CBuffer.succesBit)
	{
		*hytTemp=-9999;
		*feuchte=-9999;
		twi_error_flag=I2CBuffer.succesBit;
	}

	return 1;
}


#ifdef Special_Functions

uint8_t hyt_change_adress(uint8_t address_o, uint8_t adress_n)
{
	//sensor  (+) must be connected to ADC1 pin (PC1)
	DDRC |= (1<<DDC1);
	PORTC &= ~(1<<PC1);
	simple_delay(100);
	PORTC |= (1<<PC1);
	simple_delay(1);
	comm_mode_hyt(address_o);
	adress_n=adress_n>>1;
	wa_hyt(address_o,adress_n);
	ra_hyt(adress_n);
		return 0;
	
}

uint8_t comm_mode_hyt (uint8_t adress)
{
	//DEBUG Funktionen abschalten!
	uint8_t *values;
	uint8_t data[4];
	data[0]=adress;
	data[1]=0xA0;
	data[2]=0x00;
	data[3]=0x00;
	i2c_comm(data,4,0,0);
	_delay_ms(1);

	values = i2c_comm(data,0,1,0);
	uart_put_c('\n');
	char deb[9];
	uint8_t i = 0;
	for (i=0; i<1; i++)
	{
		utoa(values[i],deb,2);
		uart_put_s(deb);
		uart_put_c('\n');
	}
	uart_put_c('\n');
	return 1;
}

uint8_t ra_hyt(uint8_t adress)
{
	uart_put_s("read adress..");
	uart_put_c('\n');
	uint8_t *values;
	uint8_t data[4];
	data[0]=adress;
	data[1]=0x1C;
	data[2]=0x00;
	data[3]=0x00;
	i2c_comm(data,4,0,0);
	_delay_us(150);
	values = i2c_comm(data,0,3,0);
	char deb[9];
	uint8_t i = 0;
	uart_put_c('\n');
	for (i=0; i<3; i++)
	{
		utoa(values[i],deb,2);
		uart_put_s(deb);
		uart_put_c('\n');
	}
	uart_put_c('\n');
	uart_put_s("read adress finished");
	uart_put_c('\n');
	return 1;
}

uint8_t wa_hyt(uint8_t adress, uint8_t adressNew)
{
	uint8_t *values;
	uint8_t data[4];
	data[0]=adress;
	data[1]=0x5C;
	data[2]=0x00;
	data[3]=adressNew;
	i2c_comm(data,4,0,0);
	_delay_us(150);
	values = i2c_comm(data,0,3,0);
	char deb[9];
	uint8_t i = 0;
	uart_put_c('\n');
	for (i=0; i<3; i++)
	{
		utoa(values[i],deb,2);
		uart_put_s(deb);
		uart_put_c('\n');
	}
	uart_put_c('\n');
	return 1;
}

uint8_t read_meter_control_from_k30()
{
	TWBR = 16;
	PORTC |= (1<<PC2);
	
	uint8_t *values;
	volatile uint8_t data[6];
	
	//Read Meter Control from RAM
	simple_delay(30);
	data[0]=208;  //adress
	data[1]=0x41; //eeprom eeprom + 1 byte to read
	data[2]=0x00; //eeprom adress first byte
	data[3]=0x3E;//3E; //eeprom adress 2nd byte
	data[4]=data[1]+data[2]+data[3];
	i2c_comm(data, 5,0,0);
	simple_delay(30);
	
	data[0]=208;
	values=i2c_comm(data,0,3,0);  //read status, data bytes and checksum
	//uint8_t checkSum = values[0]+values[1];

	PORTC &= ~(1<<PC2);
	TWBR = 1;
	
	if (I2CBuffer.succesBit != 0)
	{
		//fail
		return  250;
	}
	
	if (I2CBuffer.succesBit == 0)
	{
		//success
		return values[1];
	}
		return 0;
}

uint8_t write_meter_control_to_k30(uint8_t mConNew)
{
	TWBR = 16;
	PORTC |= (1<<PC2);
	simple_delay(30);
	volatile uint8_t data[6];
	uint8_t *values=0;
	*values=0;
	//write Meter Control to RAM
	data[0]=208;  //adress
	data[1]=0x31; //write eeprom + 1 byte to read
	data[2]=0x00; //write adress first byte
	data[3]=0x3E;//3E; //eeprom adress 2nd byte
	data[4]=mConNew; //data
	data[5]=data[1]+data[2]+data[3]+data[4];
	i2c_comm(data, 6,0,0);
	
	simple_delay(30);
	data[0]=208;
	values=i2c_comm(data,0,2,0);  //read status and checksum
	PORTC &= ~(1<<PC2);
	TWBR = 1;
	
	if (I2CBuffer.succesBit != 0)
	{
		return 0;
	}
	
	if (I2CBuffer.succesBit == 0)
	{
		return 1;
	}
		return 0;


}

uint8_t k30_change_mCon(uint8_t task)
{
	char cVal[9];
	uint8_t oldMcon = read_meter_control_from_k30();
	//uint8_t checkSum=0;
	uint8_t state=0;
	if	( oldMcon != 250)
	{
		uart_put_s("Actual mCon: ");
		utoa (oldMcon,cVal,2);
		uart_put_s(cVal);
		uart_put_c('\n');
		
		if (task == 0)
		{
			uart_put_s("will disable ABC with: ");
			uint8_t mConNew = oldMcon | 0x02;
			utoa(mConNew,cVal,2);
			uart_put_s(cVal);
			uart_put_c('\n');
			state=write_meter_control_to_k30(mConNew);
		}
		else if (task == 1)
		{
			uart_put_s("will enable ABC with: ");
			uint8_t mConNew = oldMcon & 0xFD;
			utoa(mConNew,cVal,2);
			uart_put_s(cVal);
			uart_put_c('\n');
			state=write_meter_control_to_k30(mConNew);
		}
		else if (task == 2)
		{
			uart_put_s("will disable FRAC with :");
			uint8_t mConNew = oldMcon | 0x04;
			utoa(mConNew,cVal,2);
			uart_put_s(cVal);
			uart_put_c('\n');
			state=write_meter_control_to_k30(mConNew);
		}
		else if (task == 3)
		{
			uart_put_s("will enable FRAC with:");
			uint8_t mConNew = oldMcon & 0xFB;
			utoa(mConNew,cVal,2);
			uart_put_s(cVal);
			uart_put_c('\n');
			state=write_meter_control_to_k30(mConNew);
		}
		else if (task == 4)
		{
			uart_put_s("will disable dFRAC with :");
			uint8_t mConNew = oldMcon | 0x08;
			utoa(mConNew,cVal,2);
			uart_put_s(cVal);
			uart_put_c('\n');
			state=write_meter_control_to_k30(mConNew);
		}
		else if (task == 5)
		{
			uart_put_s("will enable dFRAC with:");
			uint8_t mConNew = oldMcon & 0xF7;
			utoa(mConNew,cVal,2);
			uart_put_s(cVal);
			uart_put_c('\n');
			state=write_meter_control_to_k30(mConNew);
		}
		else if (task == 6)
		{
			uart_put_s("Read request only.");
			uart_put_c('\n');
			state=2;
		}
		else
		{
			uart_put_s("wrong Task.");
			uart_put_c('\n');
			state=0;
		}
		
		if (state == 0)
		{
			uart_put_s("fail");
			uart_put_c('\n');
		}
		else if (state == 1)
		{
			uart_put_s("written!");
			uart_put_c('\n');
		}
		else if (state == 2)
		{
		}
		
		uart_put_s("Actual mCon: ");
		utoa(read_meter_control_from_k30(),cVal,2);
		uart_put_s(cVal);
		uart_put_c('\n');
	}
	else
	{
		uart_put_s("I2C fail while read mCon.");
		uart_put_c('\n');
	}
	return 0;
}



#endif


uint8_t handleCanMessage(volatile sensValues* acualVales)
{
	PORTB ^=  (1<<PB0);
	CANMessage inMessage;
	
	if (can_get_message(&inMessage) != 0xff)
	{
		can_get_message(&inMessage);
		
		if (inMessage.data[0] == 1)  //hier erfolgt die nachrichtenbehandlung
		{
			message_request=1;
			send_always=0;
		}
		else if (inMessage.data[0] == 2)  //intervall
		{
			intervall  = (uint32_t) inMessage.data[1]<<16;
			intervall |= (uint32_t)inMessage.data[2]<<8;
			intervall |= (uint32_t)inMessage.data[3];
		}
		else if (inMessage.data[0] == 3)
		{
			meansRequest=1;
		}
	}
	
	else if (mcp2515_read_register(CANINTF) & (1<<ERRIF) )
	{
		CanErrorStatus=mcp2515_read_register(EFLG);
		mcp2515_bit_modify(EFLG, CanErrorStatus, CanErrorStatus);
		mcp2515_bit_modify(CANINTF, 1<<ERRIF, 1<<ERRIF);
	}
	can_new_interrupt=0;
	
	return 1;
}


void sendValuesViaCan (volatile sensValues values)
{
	CANMessage message;
	
	message.id = (senderID<<4) | 1;
	message.rtr = 0;
	message.length = 8;
	message.data[0]=(uint8_t)(values.boschTemp>>8);
	message.data[1]=(uint8_t)values.boschTemp;
	message.data[2]=(uint8_t)(values.co>>8);
	message.data[3]=(uint8_t)values.co;
	message.data[4]=(uint8_t)(values.hytTemp>>8);
	message.data[5]=(uint8_t)(values.hytTemp);
	message.data[6]=(uint8_t)(values.feuchte>>8);
	message.data[7]=(uint8_t)(values.feuchte);
	
	char i=0;
	while( ( !can_send_message(&message) ) & (i<250) )
	{
		i++;
	}
	
	message.id = (senderID<<4) | 2;
	message.rtr = 0;
	message.length = 7;
	message.data[0]=(uint8_t)(values.pressure>>24);
	message.data[1]=(uint8_t)(values.pressure>>16);
	message.data[2]=(uint8_t)(values.pressure>>8);
	message.data[3]=(uint8_t)(values.pressure);
	message.data[4]=(uint8_t)(values.k30Status);
	message.data[5]=(uint8_t)(values.ppfd>>8);
	message.data[6]=(uint8_t)(values.ppfd);

	i=0;
	while( ( !can_send_message(&message) ) & (i<250) )
	{
		i++;
	}
	
	message.id = (senderID<<4) | 3;
	message.rtr = 0;
	message.length = 8;
	message.data[0]=(uint8_t)(values.RHO>>8);
	message.data[1]=(uint8_t)(values.RHO);
	message.data[2]=(uint8_t)(values.MS>>8);
	message.data[3]=(uint8_t)(values.MS);
	message.data[4]=(uint8_t)(values.AF>>8);
	message.data[5]=(uint8_t)(values.AF);
	message.data[6]=(uint8_t)(values.VPD>>8);
	message.data[7]=(uint8_t)(values.VPD);
	
	i=0;
	while( ( !can_send_message(&message) ) & (i<250) )
	{
		i++;
	}
}


void sendMeanValuesViaCan (volatile sensValues values)
{
	CANMessage message;

	
	message.id = (senderID<<4) | 4;
	message.rtr = 0;
	message.length = 8;
	message.data[0]=(uint8_t)(values.MboschTemp>>8);
	message.data[1]=(uint8_t)values.MboschTemp;
	message.data[2]=(uint8_t)(values.Mco>>8);
	message.data[3]=(uint8_t)values.Mco;
	message.data[4]=(uint8_t)(values.MhytTemp>>8);
	message.data[5]=(uint8_t)(values.MhytTemp);
	message.data[6]=(uint8_t)(values.Mfeuchte>>8);
	message.data[7]=(uint8_t)(values.Mfeuchte);

	char i=0;
	while( ( !can_send_message(&message) ) & (i<250) )
	{
		i++;
	}
	
	message.id = (senderID<<4) | 5;
	message.rtr = 0;
	message.length = 6;
	message.data[0]=(uint8_t)(values.Mpressure>>24);
	message.data[1]=(uint8_t)(values.Mpressure>>16);
	message.data[2]=(uint8_t)(values.Mpressure>>8);
	message.data[3]=(uint8_t)(values.Mpressure);
	message.data[4]=(uint8_t)(values.Mppfd>>8);
	message.data[5]=(uint8_t)(values.Mppfd);

	
	i=0;
	while( ( !can_send_message(&message) ) & (i<250) )
	{
		i++;
	}
	
	message.id = (senderID<<4) | 6;
	message.rtr = 0;
	message.length = 8;
	message.data[0]=(uint8_t)(values.MRHO>>8);
	message.data[1]=(uint8_t)(values.MRHO);
	message.data[2]=(uint8_t)(values.MS>>8);
	message.data[3]=(uint8_t)(values.MS);
	message.data[4]=(uint8_t)(values.MAF>>8);
	message.data[5]=(uint8_t)(values.MAF);
	message.data[6]=(uint8_t)(values.MVPD>>8);
	message.data[7]=(uint8_t)(values.MVPD);

	i=0;
	while( ( !can_send_message(&message) ) & (i<250) )
	{
		i++;
	}
	
	

	

}


void sendValuesViaUart (volatile sensValues actualValues)
{
	char cDebugValue[8];
	int32_t debugArray[30];
	
	debugArray[0]=sTime.days;
	debugArray[1]=sTime.daySecs;
	debugArray[2]=actualValues.hytTemp;
	debugArray[3]=actualValues.feuchte;
	debugArray[4]=actualValues.pressure;
	debugArray[5]=actualValues.co;
	debugArray[6]=actualValues.k30Status;
	debugArray[7]=actualValues.ppfd;
	debugArray[8]=actualValues.RHO;
	debugArray[9]=actualValues.S;
	debugArray[10]=actualValues.AF;
	debugArray[11]=actualValues.VPD;
	
	
	debugArray[12]=actualValues.MhytTemp;
	debugArray[13]=actualValues.Mfeuchte;
	debugArray[14]=actualValues.Mpressure;
	debugArray[15]=actualValues.Mco;
	debugArray[16]=actualValues.Mppfd;
	debugArray[17]=actualValues.MRHO;
	debugArray[18]=actualValues.MS;
	debugArray[19]=actualValues.MAF;
	debugArray[20]=actualValues.MVPD;
	debugArray[21]=actualValues.BufferCounter;
	
	debugArray[22]=actualValues.status;
	
	//debugArray[23]=mcp2515_read_register(CANSTAT);
	//debugArray[24]=mcp2515_read_register(CanErrorStatus);
	//debugArray[25]=mcp2515_read_register(CANINTE);
	//debugArray[26]=mcp2515_read_register(CANINTF);
	//debugArray[27]=mcp2515_read_register(REC);
	//debugArray[28]=mcp2515_read_register(TEC);
	debugArray[23]=0xF0F0F0;

	for	 (uint8_t i = 0 ; debugArray[i]!=0xF0F0F0; i++)
	{
		ltoa ( debugArray[i],cDebugValue,10);
		uart_put_s(cDebugValue);
		uart_put_c(';');
	}
	uart_put_c('\n');
}


uint8_t getValues(volatile sensValues* actualValues)
{
	double sdd=0, dd=0,vpd=0,af=0, rf=0,rho=0,s=0,temp32=0, hum32=0, p32=0;
	
	k30_get_values(&actualValues->co,&actualValues->k30Status);
	simple_delay(10);
	hyt_get_values(&actualValues->hytTemp,&actualValues->feuchte);
	simple_delay(10);
	bmp_get_values(&actualValues->boschTemp,&actualValues->pressure);
	actualValues->ppfd=adc_read(0);
	
	if ( (actualValues->hytTemp != -9999) && (actualValues->feuchte != -9999) )
	{
		temp32 = (double)actualValues->hytTemp/100.0;
		hum32 = (double)actualValues->feuchte/100.0;
		p32 = (double)actualValues->pressure/100.0;
		const double r1=287.058;
		const double r2=461.523;
		
		sdd=(6.1094*exp((17.625*(temp32))/(243.04+(temp32))))*(1.00071*exp(0.0000045*(p32)));
		dd=sdd*(hum32/100.0);
		rf=r1/(1.0-(hum32/100.0)*sdd/p32*(1.0-r1/r2));
		rho=(p32*100.0)/(rf*((temp32)+273.15));
		s=(621.98001*dd)/(p32-0.37802*dd);
		af=(dd*100.0)*100.0/(r2*(temp32+273.15));
		vpd=sdd-(sdd*(hum32/100.0));
		
		actualValues->RHO = (int16_t)(rho*1000);
		actualValues->S = (int16_t)(s*1000);
		actualValues->AF = (int16_t)(af*1000);
		actualValues->VPD = (int16_t)(vpd*100);
	}
	else
	{
		actualValues->RHO = -9999;
		actualValues->S = -9999;
		actualValues->AF = -9999;
		actualValues->VPD = -9999;
	}
	//char cdebug[10];
	//
	//ltoa(actualValues->RHO,cdebug,10);
	//uart_put_s(cdebug);
	//uart_put_c('\n');
	//ltoa((int16_t)(s*1000),cdebug,10);
	//uart_put_s(cdebug);
	//uart_put_c('\n');
	//ltoa((int16_t)(af*1000),cdebug,10);
	//uart_put_s(cdebug);
	//uart_put_c('\n');
	//ltoa((int16_t)(vpd*100),cdebug,10);
	//uart_put_s(cdebug);
	//uart_put_c('\n');

	
	if (actualValues->BufferCounter>=intervall)
	{
		actualValues->Mppfd=-9999;
		actualValues->Mco=-9999;
		actualValues->MhytTemp=-9999;
		actualValues->Mfeuchte=-9999;
		actualValues->Mpressure=-9999;
		actualValues->MboschTemp=-9999;
		actualValues->MRHO=-9999;
		actualValues->MS=-9999;
		actualValues->MAF=-9999;
		actualValues->MVPD=-9999;
		
		actualValues->BufferCounter=0;
		actualValues->Bppfd=0;
		actualValues->Bco=0;
		actualValues->BhytTemp=0;
		actualValues->Bfeuchte=0;
		actualValues->Bpressure=0;
		actualValues->BboschTemp=0;
		actualValues->BRHO=0;
		actualValues->BS=0;
		actualValues->BAF=0;
		actualValues->BVPD=0;
		
		actualValues->BppfdCounter=0;
		actualValues->BcoCounter=0;
		actualValues->BhytTempCounter=0;
		actualValues->BfeuchteCounter=0;
		actualValues->BpressureCounter=0;
		actualValues->BboschTempCounter=0;
		actualValues->BRHOCounter=0;
		actualValues->BSCounter=0;
		actualValues->BAFCounter=0;
		actualValues->BVPDCounter=0;
	}
	actualValues->BufferCounter++;
	
	actualValues->BppfdCounter++;
	actualValues->Bppfd+=actualValues->ppfd;
	actualValues->Mppfd=(actualValues->Bppfd+(actualValues->BppfdCounter/2) ) / actualValues->BppfdCounter;

	if (actualValues->co!=-9999)
	{
		actualValues->BcoCounter++;
		actualValues->Bco+=actualValues->co;
		actualValues->Mco=(actualValues->Bco+(actualValues->BcoCounter/2) ) / actualValues->BcoCounter;
		actualValues->status &= ~(1<<0);
	}
	else
	{
		actualValues->status |= (1<<0);
	}
	

	if (actualValues->hytTemp!=-9999)
	{
		actualValues->BhytTempCounter++;
		actualValues->BhytTemp+=actualValues->hytTemp;
		actualValues->MhytTemp=(actualValues->BhytTemp+(actualValues->BhytTempCounter/2) ) / actualValues->BhytTempCounter;
		actualValues->status &= ~(1<<1);
	}
	else
	{
		actualValues->status |= (1<<1);
	}
	
	

	if (actualValues->feuchte != -9999)
	{
		actualValues->BfeuchteCounter++;
		actualValues->Bfeuchte+=actualValues->feuchte;
		actualValues->Mfeuchte=(actualValues->Bfeuchte+(actualValues->BfeuchteCounter/2) ) / actualValues->BfeuchteCounter;

		actualValues->status &= ~(1<<2);
	}
	else
	{
		actualValues->status |= (1<<2);
	}
	

	if (actualValues->pressure != -9999)
	{
		actualValues->BpressureCounter++;
		actualValues->Bpressure+=actualValues->pressure;
		actualValues->Mpressure=(actualValues->Bpressure+(actualValues->BpressureCounter/2) ) / actualValues->BpressureCounter;
		actualValues->status &= ~(1<<3);
	}
	else
	{
		actualValues->status |= (1<<3);
	}
	
	if (actualValues->boschTemp != -9999)
	{
		actualValues->BboschTempCounter++;
		actualValues->BboschTemp+=actualValues->boschTemp;
		actualValues->MboschTemp=(actualValues->BboschTemp+(actualValues->BboschTempCounter/2) ) / actualValues->BboschTempCounter;
		actualValues->status &= ~(1<<4);
	}
	else
	{
		actualValues->status |= (1<<4);
	}
	
	if (actualValues->RHO != -9999)
	{
		actualValues->BRHOCounter++;
		actualValues->BRHO+=actualValues->RHO;
		actualValues->MRHO=(actualValues->BRHO+(actualValues->BRHOCounter/2) ) / actualValues->BRHOCounter;
	}
	else
	{
		actualValues->BRHO+=actualValues->MRHO;
	}
	

	if (actualValues->S != -9999)
	{
		actualValues->BSCounter++;
		actualValues->BS+=actualValues->S;
		actualValues->MS=(actualValues->BS+(actualValues->BSCounter/2) ) / actualValues->BSCounter;
	}
	else
	{
		actualValues->BS+=actualValues->MS;
	}
	
	if (actualValues->AF != -9999)
	{
		actualValues->BAFCounter++;
		actualValues->BAF+=actualValues->AF;
		actualValues->MAF=(actualValues->BAF+(actualValues->BAFCounter/2) ) / actualValues->BAFCounter;
	}
	else
	{
		actualValues->BAF+=actualValues->MAF;
	}
	

	if (actualValues->VPD != -9999)
	{
		actualValues->BVPDCounter++;
		actualValues->BVPD+=actualValues->VPD;
		actualValues->MVPD=(actualValues->BVPD+(actualValues->BVPDCounter/2) ) / actualValues->BVPDCounter;
	}
	else
	{
		actualValues->BVPD+=actualValues->MVPD;
	}
	


	if (actualValues->BufferCounter>=intervall)
	{
		sendMeanValuesViaCan(*actualValues);
	}

	return 1;
}


void receive_command()
{

	unsigned char category = uart_struct.uart_buffer[0];
	unsigned char cValue[9];
	int32_t value=0;
	unsigned char i=0;

	while (uart_struct.uart_buffer[i]!='\0')
	{
		i++;
		cValue[i-1]=uart_struct.uart_buffer[i];
	}
	value=atol ( (char*)cValue);


	switch(category)
	{
		case 'A':
		{
			for (uint8_t i=0; i<255; i++)
			{
				uart_put_c(i);
				volatile uint8_t data[1];
				data[0]=i;
				i2c_comm(data,1,0,0);
				simple_delay(5);
			}
		}
		break;
		
		case 'T':
		{
			if (value>=0 && value<=255)
			{
				volatile uint8_t data[1];
				data[0]=value;//80;
				i2c_comm(data,1,0,0);
			}
		}
		break;
		
		#ifdef Special_Functions
		case 'e':
		{
			if (value < 7)
			{
				k30_change_mCon(value);
			}
			
		}
		break;

		
		#endif
		#ifdef can_debug
		#include "CANDEBUG.h"
		#endif
		
		default:
		uart_put_s("bullshit string");
	}
	uart_struct.uart_state=no_string;
}