
#include "include/sensorBoard.h"

int main(void)
{
	volatile sensValues actualValues;
	
	init(&actualValues);

	simple_delay(10<<senderID);

	uint8_t i=0;
	do
	{
		i++;
		bmp_get_cal();
		simple_delay(10);
	} while ( (AC1==0) && (i<50) );
	
	//hyt_change_adress(84,80);


	while(1)
	{
		
		if(can_new_interrupt)
		{
			handleCanMessage(&actualValues);
		}
		
		if (message_request)
		{
			
			getValues(&actualValues);			
			sendValuesViaCan(actualValues);
			sendValuesViaUart(actualValues);
			message_request=0;
			PORTD ^=  (1<<PD7);
		}


		
		
		if (tick)
		{
			if (uart_struct.uart_state == string_complete)
			{
				receive_command();
			}
			
			if (send_always)
			{
				message_request=1;
			}
			tick=0;
		}
	}
}


