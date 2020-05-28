/*
 * eeprom_functions.c
 *
 * Created: 20.04.2014 10:09:36
 *  Author: knoerk
 */ 

#include "include/eeprom_functions.h"


uint8_t eprom_write (volatile sensValues* values_1,volatile sensValues* values_2,volatile sensValues* values_3, uint32_t* memory_adress)
{
	volatile uint8_t daten[20];
	uint8_t i=0;
	
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		daten[0]= 160 | (uint8_t) (*memory_adress>>15 & 0b00000010);
		daten[1]= (uint8_t) (*memory_adress>>8);
		daten[2]= (uint8_t) *memory_adress;
		
		daten[3]=sTime.days;
		daten[4]=(uint8_t)(sTime.daySecs>>16);
		daten[5]=(uint8_t)(sTime.daySecs>>8);
		daten[6]=(uint8_t)(sTime.daySecs);
		
		daten[7]=treatment;
		daten[8]=(uint8_t)values_1->MinH;
		
		daten[9]=(uint8_t)(values_3->MhytTemp>>8);
		daten[10]=(uint8_t)(values_3->MhytTemp);
		
		daten[11]=(uint8_t)(values_3->Mfeuchte>>8);
		daten[12]=(uint8_t)(values_3->Mfeuchte);
		
		daten[13]=(uint8_t)(values_3->Mpressure>>24);
		daten[14]=(uint8_t)(values_3->Mpressure>>16);
		daten[15]=(uint8_t)(values_3->Mpressure>>8);
		daten[16]=(uint8_t)(values_3->Mpressure);
		
		daten[17]=(uint8_t)(values_3->Mco>>8);
		daten[18]=(uint8_t)values_3->Mco;
	}
	i=0;
	do
	{
		i++;
		i2c_comm(daten,19,0,0);
	} while (I2CBuffer.succesBit && (i<100) );
	*memory_adress+=16;
	
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		daten[0]= 160 | (uint8_t) (*memory_adress>>15 & 0b00000010);
		daten[1]= (uint8_t) (*memory_adress>>8);
		daten[2]= (uint8_t) *memory_adress;
		
		daten[3]=(uint8_t)(values_1->MhytTemp>>8);
		daten[4]=(uint8_t)(values_1->MhytTemp);
		
		daten[5]=(uint8_t)(values_1->Mfeuchte>>8);
		daten[6]=(uint8_t)(values_1->Mfeuchte);
		
		daten[7]=(uint8_t)(values_1->Mpressure>>24);
		daten[8]=(uint8_t)(values_1->Mpressure>>16);
		daten[9]=(uint8_t)(values_1->Mpressure>>8);
		daten[10]=(uint8_t)(values_1->Mpressure);
		
		daten[11]=(uint8_t)(values_1->Mco>>8);
		daten[12]=(uint8_t)values_1->Mco;
		
		daten[13]=(uint8_t)(values_1->Mppfd>>8);
		daten[14]=(uint8_t)(values_1->Mppfd);
		
		daten[15]=(uint8_t)((uint16_t)values_1->MVPD>>8);
		daten[16]=(uint8_t)((uint16_t)values_1->MVPD);
		
		daten[17]=(uint8_t)((uint16_t)values_1->MAF>>8);
		daten[18]=(uint8_t)((uint16_t)values_1->MAF);
	}
	i=0;
	do
	{
		i++;
		i2c_comm(daten,19,0,0);
	} while (I2CBuffer.succesBit && (i<100) );
	*memory_adress+=16;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		daten[0]= 160 | (uint8_t) (*memory_adress>>15 & 0b00000010);
		daten[1]= (uint8_t) (*memory_adress>>8);
		daten[2]= (uint8_t) *memory_adress;
		
		daten[3]=(uint8_t)(values_2->MhytTemp>>8);
		daten[4]=(uint8_t)(values_2->MhytTemp);
		
		daten[5]=(uint8_t)(values_2->Mfeuchte>>8);
		daten[6]=(uint8_t)(values_2->Mfeuchte);
		
		daten[7]=(uint8_t)(values_2->Mpressure>>24);
		daten[8]=(uint8_t)(values_2->Mpressure>>16);
		daten[9]=(uint8_t)(values_2->Mpressure>>8);
		daten[10]=(uint8_t)(values_2->Mpressure);
		
		daten[11]=(uint8_t)(values_2->Mco>>8);
		daten[12]=(uint8_t)values_2->Mco;
		
		daten[13]=(uint8_t)(values_2->Mppfd>>8);
		daten[14]=(uint8_t)(values_2->Mppfd);
		
		daten[15]=(uint8_t)(values_2->MVPD>>8);
		daten[16]=(uint8_t)(values_2->MVPD);
		
		daten[17]=(uint8_t)(values_2->MAF>>8);
		daten[18]=(uint8_t)(values_2->MAF);
	}
	i=0;
	do
	{
		i++;
		i2c_comm(daten,19,0,0);
	} while (I2CBuffer.succesBit && (i<100) );
	*memory_adress+=16;
	
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		daten[0]= 160 | (uint8_t) (*memory_adress>>15 & 0b00000010);
		daten[1]= (uint8_t) (*memory_adress>>8);
		daten[2]= (uint8_t) *memory_adress;
		
		daten[3]=251;
		daten[4]=252;
		daten[5]=253;
		daten[6]=254;
	}
	i=0;
	do
	{
		i++;
		i2c_comm(daten,7,0,0);
	} while (I2CBuffer.succesBit && (i<100) );
	
	return 1;
}


uint8_t eprom_read ()
{
	//uint8_t TCCR0Backup=TCCR0;
	//TCCR0 = 0;
		
	volatile uint32_t adress=64;
	volatile uint8_t daten[16];
	volatile uint8_t AdressDaten[3];
	uint32_t tmp[8];
	volatile uint8_t *values;
	uint8_t i=0;
	uint8_t lastByte=0;
	char cdaten[8];
	
	AdressDaten[0]=0;
	AdressDaten[1]=0;
	
	while ( !lastByte )
	{
		AdressDaten[0]= 160 | (uint8_t) ( (adress>>15) & 0b00000010);
		AdressDaten[1]= adress>>8;
		AdressDaten[2]= adress;
		
		//Status-Paket + RHO und S
		do
		{
			i++;
			values = i2c_comm(AdressDaten,3,16,1);
		} while (I2CBuffer.succesBit && (i<100) );
		i=0;
		adress+=16;
		
		
		for (int j = 0; j< 16 ; j++)
		{
			daten [j] = *values;
			values++;
		}
		
		if ((daten[0] == 251) &  (daten[1] == 252) & (daten[2] == 253) &  (daten[3] == 254))
		{
			break;
		}
		tmp[0]  = ((uint8_t)daten[0])		;
		
		tmp[1] =  ((uint32_t)daten[1])<<16		;
		tmp[1] |= ((uint32_t)daten[2])<<8	;
		tmp[1] |= ((uint32_t)daten[3])			;
		
		tmp[2] = (int32_t)daten[4]			;
		tmp[3] = (int32_t)daten[5]			;
		
		tmp[4] = ((int16_t)daten[6])<<8			;
		tmp[4] |= (int16_t)daten[7]			;
		
		tmp[5] = ((int16_t)daten[8])<<8			;
		tmp[5] |=(int16_t)daten[9]			;
		
		tmp[6]  = ((int32_t)daten[10])<<24		;
		tmp[6] |= ((int32_t)daten[11])<<16		;
		tmp[6] |= ((int32_t)daten[12])<<8		;
		tmp[6] |= (int32_t)daten[13]			;
		
		tmp[7] = ((int16_t)daten[14])<<8			;
		tmp[7] |=(int16_t)daten[15]			;

		
		for	 (uint8_t k = 0 ; k < 8; k++)
		{
			ltoa ( tmp[k],cdaten,10);
			uart_put_s(cdaten);
			uart_put_c(';');
		}
		
		//Die beiden Daten-Pakete
		for (uint8_t messagecounter=0; messagecounter<2;messagecounter++)
		{
			AdressDaten[0]= 160 | (uint8_t) ( (adress>>15) & 0b00000010);
			AdressDaten[1]= adress>>8;
			AdressDaten[2]= adress;
			
			do
			{
				i++;
				values = i2c_comm(AdressDaten,3,16,1);
			} while (I2CBuffer.succesBit && (i<100) );
			
			i=0;
			adress+=16;
			
			
			for (int j = 0; j< 16 ; j++)
			{
				daten [j] = *values;
				values++;
			}
			if ((daten[0] == 251) &  (daten[1] == 252) & (daten[2] == 253) &  (daten[3] == 254))
			{
				break;
			}
			
			tmp[0]  = ((int16_t)daten[0])<<8		;
			tmp[0] |= (int16_t)daten[1]			;
			
			tmp[1]  = ((int16_t)daten[2])<<8		;
			tmp[1] |= (int16_t)daten[3]			;
			
			tmp[2]  = ((int32_t)daten[4])<<24		;
			tmp[2] |= ((int32_t)daten[5])<<16		;
			tmp[2] |= ((int32_t)daten[6])<<8		;
			tmp[2] |= (int32_t)daten[7]			;
			
			tmp[3]  = ((int16_t)daten[8])<<8		;
			tmp[3] |= (int16_t)daten[9]			;
			
			tmp[4]  = ((int16_t)daten[10])<<8		;
			tmp[4] |= (int16_t)daten[11]		;
			
			tmp[5]  = ((int16_t)daten[12])<<8		;
			tmp[5] |= (int16_t)daten[13]			;
			
			tmp[6]  = ((int16_t)daten[14])<<8		;
			tmp[6] |= (int16_t)daten[15]		;
			

			char cdaten[8];
			for	 (uint8_t k = 0 ; k < 7; k++)
			{
				ltoa ( tmp[k],cdaten,10);
				uart_put_s(cdaten);
				uart_put_c(';');
			}
		}
		uart_put_c('\n');
	}
	
	//TCCR0 = TCCR0Backup;
	return 1;
}
