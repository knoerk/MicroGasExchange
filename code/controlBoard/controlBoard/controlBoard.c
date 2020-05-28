
#include "include/controlBoard.h"


int main(void)
{
	init();

	CANMessage outMessage;
	
	uint8_t kuehlDeadTimeTicker=0;
	
	
	volatile sensValues actualValues_1;
	volatile sensValues actualValues_2;
	volatile sensValues actualValues_3;
	volatile eepromValues eValues;
	

	init_sensValues(&actualValues_1);
	init_sensValues(&actualValues_2);
	init_sensValues(&actualValues_3);
	init_eValues(&eValues,60,5);
	

	
	while(1)
	{
		actualValues_3.hytTemp=actualValues_2.hytTemp;
		actualValues_3.feuchte=actualValues_2.feuchte;
		actualValues_3.pressure=actualValues_2.pressure;
		actualValues_3.co=actualValues_2.co;
		
		if(can_new_interrupt)
		{
			handleCanMessage(&actualValues_1,&actualValues_2);
		}
		
		if (tick)
		{

			if ((actualValues_1.hytTemp != -9999) && (actualValues_1.hytTemp != -8888) )
			{
				OCR1A=calculate_pid(&PID_values_preHeat,actualValues_1.hytTemp);
			}
			
			if ( (actualValues_1.hytTemp-PID_values_preHeat.setValue>10) & (PID_values_preHeat.setValue>1000) )
			{
				PORTD |= (1<<PD6);
				kuehlDeadTimeTicker=4;
			}
			else if (kuehlDeadTimeTicker)
			{
				kuehlDeadTimeTicker--;
				if (!kuehlDeadTimeTicker)
				{
					PORTD &= ~(1<<PD6);
				}
			}
			
			if ( (actualValues_2.hytTemp != -9999) && (actualValues_2.hytTemp != -8888) )
			{
				OCR1B=calculate_pid(&PID_values_inHeat,actualValues_2.hytTemp);
			}
			
			
			switch (HUMmode)
			{
				
				case specHum_in:
				if ( (actualValues_1.S != -9999) && (actualValues_1.S != -8888) )
				{
					uint8_t OCR2new = calculate_pid(&PID_values_specHum_in,actualValues_1.S);
					
					if ( (OCR2 == 0) && (OCR2new != 0 ) )
					{
						OCR2 = 255;
					}
					else
					{
						OCR2 = OCR2new;
					}
				}
				break;
				
				case vpd_out:
				if ( (actualValues_2.VPD != -9999) && (actualValues_2.VPD != -8888) )
				{
					uint8_t OCR2new = calculate_pid(&PID_values_vpd_in,actualValues_2.VPD);
					
					if ( (OCR2 == 0) && (OCR2new != 0 ) )
					{
						OCR2 = 255;
					}
					else
					{
						OCR2 = OCR2new;
					}
				}
				break;
			}



			
			PCF8574_byte = 255;
			PCF8574_write(PCF8574_byte);
			
			if (uart_struct.uart_state == string_complete)
			{
				recieve_command(&actualValues_1,&actualValues_2,&eValues);
			}
			
			

			if (memoryAdress>=63872)
			{
				saveToEpromEnabled=2;
			}
			
			calculate_means(&actualValues_1);
			eValues.BufferCounter1++;
			if (eValues.BufferCounter1>=eValues.intervall)
			{
				eValues.meanSensValues1=actualValues_1;
				zeroMeansInsensValues(&actualValues_1);
				eValues.BufferCounter1=0;
				eValues.full++;
			}
			
			if (eValues.delayTimer>=eValues.signalRunTime)
			{
				calculate_means(&actualValues_2);
				eValues.BufferCounter2++;
				if (eValues.BufferCounter2>=eValues.intervall)
				{
					eValues.meanSensValues2=actualValues_2;
					zeroMeansInsensValues(&actualValues_2);
					eValues.BufferCounter2=0;
					eValues.full++;
				}
			}
			else
			{
				eValues.delayTimer++;
			}
			
			if ( (eValues.BufferCounter2>=eValues.intervall-4) || (eValues.BufferCounter3>0) )
			{
				calculate_means(&actualValues_3);
				eValues.BufferCounter3++;
				if (eValues.BufferCounter3>=9)
				{
					eValues.meanSensValues3=actualValues_3;
					zeroMeansInsensValues(&actualValues_3);
					eValues.BufferCounter3=0;
					eValues.full++;
				}
			}
			
			if  (eValues.full==3)
			{
				eValues.full=0;
				if (saveToEpromEnabled==1)
				{
					eprom_write(&eValues.meanSensValues1,&eValues.meanSensValues2,&eValues.meanSensValues3,&memoryAdress);
				}
				
				if (buffer_update_flag)
				{
					init_eValues(&eValues,eValues.intervall_Buffer,eValues.signalRunTimeBuffer);
					zeroMeansInsensValues(&actualValues_1);
					zeroMeansInsensValues(&actualValues_2);
					zeroMeansInsensValues(&actualValues_3);
					buffer_update_flag=0;
				}
			}

			if (spec_hum_in_program.active)
			{
				exec_program(&spec_hum_in_program,&PID_values_specHum_in);
			}

			if (preHeat_program.active)
			{
				exec_program(&preHeat_program,&PID_values_preHeat);
			}

			if (inHeat_program.active)
			{
				exec_program(&inHeat_program,&PID_values_inHeat);
			}

			if (vpd_in_program.active)
			{
				exec_program(&vpd_in_program,&PID_values_vpd_in);
			}

			debug(&actualValues_1,&actualValues_2,&actualValues_3,&eValues);
			
			outMessage.id = (uint16_t) (1<<4);
			outMessage.rtr = 0;
			outMessage.length = 2;
			outMessage.data[0]=1;
			
			uint8_t count=0;
			while( ( !can_send_message(&outMessage) ) & (count<250) )
			{
				count++;
			}
			outMessage.id = (2<<4);
			delay(10);
			count=0;
			while( ( !can_send_message(&outMessage) ) & (count<250) )
			{
				count++;
			}
			
			zero_sensValues(&actualValues_1);
			zero_sensValues(&actualValues_2);
			
			tick=0;
		}
	}
}


