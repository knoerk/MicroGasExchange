#include "include/debug.h"


void debug(volatile sensValues* values_1,volatile sensValues* values_2,volatile sensValues* values_3, volatile eepromValues* eValues)
{
	char cDebugValue[8];
	uint8_t i=0;
	int32_t debugArray[38];
	
	debugArray[i++]=sTime.days;
	debugArray[i++]=sTime.daySecs;
	debugArray[i++]=treatment;
	debugArray[i++]=repetition;
	debugArray[i++]=values_1->hytTemp;
	debugArray[i++]=values_2->hytTemp;
	debugArray[i++]=values_1->feuchte;
	debugArray[i++]=values_2->feuchte;
	debugArray[i++]=values_1->pressure;
	debugArray[i++]=values_2->pressure;
	debugArray[i++]=values_1->co;
	debugArray[i++]=values_2->co;
	debugArray[i++]=values_1->k30Status;
	debugArray[i++]=values_2->k30Status;
	debugArray[i++]=values_1->ppfd;
	debugArray[i++]=values_2->ppfd;
	debugArray[i++]=values_1->RHO;
	debugArray[i++]=values_2->RHO;
	debugArray[i++]=values_1->S;
	debugArray[i++]=values_2->S;
	debugArray[i++]=values_1->VPD;
	debugArray[i++]=values_2->VPD;
	debugArray[i++]=values_1->AF;
	debugArray[i++]=values_2->AF;
	debugArray[i++]=saveToEpromEnabled;
	debugArray[i++]=OCR1A;
	debugArray[i++]=OCR1B;
	debugArray[i++]=OCR2;
	debugArray[i++]=7;
	debugArray[i++]=eValues->delayTimer;
	debugArray[i++]=eValues->intervall;
	debugArray[i++]=values_1->BppfdCounter;
	debugArray[i++]=values_2->BppfdCounter;
	debugArray[i++]=values_3->BppfdCounter;
	debugArray[i++]=eValues->full;
	//debugArray[i++]=mcp2515_read_register(CANINTF);
	//debugArray[i++]=mcp2515_read_register(REC);
	//debugArray[i++]=mcp2515_read_register(TEC);
	//debugArray[i++]=saveToEpromEnabled;

	for	 (uint8_t j = 0 ; j<i; j++)
	{
		ltoa ( debugArray[j],cDebugValue,10);
		uart_put_s(cDebugValue);
		uart_put_c(';');
	}
	uart_put_c('\n');
}