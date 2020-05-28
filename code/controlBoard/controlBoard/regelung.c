

#include "include/regelung.h"


uint8_t calculate_pid(PID_values* values, int16_t temp)
{
	if (values->invert)
	{
		temp=temp*-1;
		values->setValue=values->setValue*-1;
	}
	
	if ( (values->setValue - temp ) >values->deadband)
	{
		values->pidoutput=65534;
	}
	else if ( (values->setValue - temp) < 0 - values->deadband)
	{
		values->pidoutput=0;
	}

	else
	{
		values->err[2] = values->err[1];
		values->err[1] = values->err[0];
		values->err[0] = values->setValue - temp;
		
		if ( ( (values->err[0]>0) && (values->err[1]<0) ) || ( (values->err[0]<0) && (values->err[1]>0) ) || ( (values->err[0]==0) ) )
		{
			values->esum=0;
		}
		else if ( (values->esum < 1000) && (values->esum > -1000) )
		{
			values->esum+=values->err[0];
		}

		
		int32_t P_value = ( values->P *  ( values->err[0]) ) /values->scale;
		if (P_value>512)
		{
			P_value=512;
		}
		else if (P_value< (-512) )
		{
			P_value=-512;
		}
		
		int32_t I_value = (values->I * ( values->esum ) ) /values->scale;
		if (I_value > 256 )
		{
			I_value=256;
		}
		else if (I_value< -256 )
		{
			I_value=-256;
		}
		
		int32_t D_value = (values->D * ( values->err[0] - values->err[values->tau] ) );
		if (D_value>1024)
		{
			D_value=1024;
		}
		else if (D_value<-1024)
		{
			D_value=-1024;
		}
		

		// calculate new output
		int32_t pidouttemp =  ( values->pidoutput + ( (P_value + I_value + D_value)) );

		
		if (pidouttemp>65534)
		{
			values->pidoutput=65534;
		}
		else if (pidouttemp < 0)
		{
			values->pidoutput=0;
		}
		else
		{
			values->pidoutput=pidouttemp;
		}
		
		//char Cdebug[10];
		//uart_put_s(ltoa(values->pidoutput,Cdebug,10) );
		//uart_put_c(';');
		//uart_put_s(ltoa(P_value + I_value + D_value,Cdebug,10) );
		//uart_put_c(';');
		//uart_put_s(ltoa(P_value,Cdebug,10) );
		//uart_put_c(';');
		//uart_put_s(ltoa(I_value,Cdebug,10) );
		//uart_put_c(';');
		//uart_put_s(ltoa(D_value,Cdebug,10) );
		//uart_put_c('\n');

	}

	if (values->invert)
	{
		values->setValue=values->setValue*-1;
	}
	
	if  ( ( (values->pidoutput+128)/256 )  < values->min )
	{
		return 0;
	}
	else
	{
		return (values->pidoutput/256);
	}

}


void init_PID_values(PID_values* values,uint16_t p, uint8_t i, uint16_t d,uint16_t stellValue, uint16_t min,uint16_t Deadband,uint8_t Tau, uint16_t Scale,uint8_t Invert)
{
	values->err[0]=0;
	values->err[1]=0;
	values->err[2]=0;
	
	values->pidoutput=0;
	values->tau=Tau;
	values->setValue=stellValue;
	values->P=p;
	values->I=i;
	values->D=d;
	values->esum=0;
	values->min=min;
	values->deadband=Deadband;
	values->scale=Scale;
	values->invert=Invert;
}