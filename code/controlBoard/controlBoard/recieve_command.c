

#include "include/recieve_command.h"


void recieve_command(volatile sensValues* values_1,volatile sensValues* values_2,volatile eepromValues* eValues)
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
		
		
		case 'a':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_preHeat.P=value;
		}
		break;
		
		case 'b':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_preHeat.I=value;
		}
		break;
		
		case 'c':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_preHeat.D=value;
		}
		break;
		
		case 'd':
		if ( (value>=0) && (value<=4000) )
		{
			PID_values_preHeat.setValue=value;
		}
		break;
		
		case 'e':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_inHeat.P=value;
		}
		break;
		
		case 'f':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_inHeat.I=value;
		}
		break;
		
		case 'g':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_inHeat.D=value;
		}
		break;
		
		case 'h':
		if ( (value>=0) && (value<=4000) )
		{
			PID_values_inHeat.setValue=value;
		}
		break;
		
		case 'i':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_specHum_in.P=value;
		}
		break;
		
		case 'j':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_specHum_in.I=value;
		}
		break;
		
		case 'k':
		if ( (value>=0) && (value<=2560) )
		{
			PID_values_specHum_in.D=value;
		}
		break;
		
		case 'l':
		if ( (value>=0) && (value<=40000) )
		{
			PID_values_specHum_in.setValue=value;
		}
		break;
		
		case 'm':
		if ( (value>=0) && (value<=255) )
		{
			PID_values_specHum_in.min=value;
		}
		break;
		
		case 'n':
		if ( (value>=0) && (value<=255) )
		{
			sTime.days=value;
		}
		break;
		
		case 'o':
		if ( (value>=0) && (value<=255) )
		{
			treatment=value;
		}
		break;
		
		case 'p':
		if ( (value>=0) && (value<=255) )
		{
			repetition=value;
		}
		break;
		
		
		case 'q': //read values from eprom
		{
			eprom_read();
		}
		break;
		
		
		case 'r':		  //set intervall for Values
		if ( (value>=1) && (value<=3600) )
		{
			eValues->intervall_Buffer=value;
			buffer_update_flag=1;
		}
		break;
		
		case 's':		  //set delay time
		if  (value<=eValues->intervall_Buffer-10)
		{
			eValues->signalRunTimeBuffer=value;
			buffer_update_flag=1;
		}
		break;
		

		case 't':
		saveToEpromEnabled ^= (1<<0);
		break;
		
		
		case 'u':
		{
			for (uint8_t i=2; i<9; i+=2)
			{
				lightValues[0]=i;
				sent_to_panel(lightValues);
			}
		}
		break;
		
		case 'v':
		{
			if ( (value>=0) && (value<=255) )
			{
				lightValues[1]=value;
			}
		}
		break;
		
		case 'w':
		{
			if ( (value>=0) && (value<=255) )
			{
				lightValues[2]=value;
			}
		}
		break;
		
		case 'x':
		{
			if ( (value>=0) && (value<=255) )
			{
				lightValues[3]=value;
			}
		}
		break;
		
		case 'y':
		{
			if ( (value>=0) && (value<=255) )
			{
				lightValues[4]=value;
			}
		}
		break;
		
		case 'z':
		{
			//FREI
		}
		break;
		
		case 'A':
		if ( (value>=0) && (value<=10000) )
		{
			PID_values_co2.setValue = value;
		}
		break;
		
		case 'B':
		if ( (value>=0) && (value<=10000) )
		{
			PID_values_vpd_in.setValue=value;
		}
		break;
		
		case 'C':
		if ( (value>=1) && (value<=2) )
		{
			HUMmode=value;
		}
		break;
		
		case 'D':
		{
			memoryAdress=64;
		}
		break;
		
		case 'E':
		{
			if ( (value>=0) && (value<=100) )
			{
				TIMER3.OCRA=value;
			}
		}
		break;
		
		case 'F':
		{
			if ( (value>=0) && (value<=100) )
			{
				TIMER3.OCRB=value;
			}
		}
		break;
		
		case 'G':
		{
			if ( (value>=0) && (value<=100) )
			{
				TIMER3.OCRC=value;
			}
		}
		break;
		
		case 'H':
		{
			if ( (value>=0) && (value<=100) )
			{
				TIMER3.OCRD=value;
			}
		}
		break;
		
		// I bis J FREI
		
		case 'K':
		{
			if (value==0)
			{
				stop_and_reset_program(&spec_hum_in_program);
			}
			else if ( (value>=10) && (value<=43200) )
			{
				stop_and_reset_program(&vpd_in_program);
				set_program(&spec_hum_in_program,5000,18000,3000,value);
			}
		}
		break;
		
		case 'L':
		{
			if (value==0)
			{
				stop_and_reset_program(&preHeat_program);
			}
			else if ( (value>=10) && (value<=43200) )
			{
				set_program(&preHeat_program,2800,3200,100,value);
			}
		}
		break;
		
		case 'M':
		{
			if (value==0)
			{
				stop_and_reset_program(&inHeat_program);
			}
			else if ( (value>=10) && (value<=43200) )
			{
				set_program(&inHeat_program,2800,3200,50,value);
			}
		}
		break;

		case 'N':
		{
			if (value==0)
			{
				stop_and_reset_program(&vpd_in_program);
			}
			else if ( (value>=10) && (value<=43200) )
			{
				stop_and_reset_program(&spec_hum_in_program);
				set_program(&vpd_in_program,500,4000,100,value);
			}
		}
		break;
				
		case 'X': //External (!) set intervall value of sender 1
		if (value>=0 && value<=86399)
		{
			CANMessage intervallMessage;
			intervallMessage.id = (uint16_t) (1<<4);  //set sender ID
			intervallMessage.rtr = 0;
			intervallMessage.length = 5;
			intervallMessage.data[0]=2;	//set intervall
			intervallMessage.data[1]=(uint8_t)(value>>16);//intervall value...
			intervallMessage.data[2]=(uint8_t)(value>>8);
			intervallMessage.data[3]=(uint8_t)value;
			uint8_t count=0;
			while(!(can_send_message(&intervallMessage)) & (count<10) )
			{
				count++;
			}
		}
		break;
		

		
		
		case 'Z': //set External (!) intervall value of sender 2
		if (value>=0 && value<=86399)
		{
			CANMessage intervallMessage;
			intervallMessage.id = (uint16_t) (2<<4);  //set sender ID
			intervallMessage.rtr = 0;
			intervallMessage.length = 5;
			intervallMessage.data[0]=2;	//set intervall
			intervallMessage.data[1]=(uint8_t)(value>>16);//intervall value...
			intervallMessage.data[2]=(uint8_t)(value>>8);
			intervallMessage.data[3]=(uint8_t)value;
			uint8_t count=0;
			while(!(can_send_message(&intervallMessage)) & (count<10) )
			{
				count++;
			}
		}
		break;
		
		#ifdef Special_Functions
		#endif
		
		default:
		uart_put_s("bullshit string");
	}
	uart_struct.uart_state=no_string;
}



