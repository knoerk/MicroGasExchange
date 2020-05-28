

#include "include/calculate_means.h"


uint8_t calculate_means(volatile sensValues* values)
{
	values->Bppfd+=values->ppfd;
	values->BppfdCounter++;
	values->Mppfd=(values->Bppfd+(values->BppfdCounter/2) ) / values->BppfdCounter;
	
	values->BinH+=OCR1B;
	values->BinHCounter++;
	values->MinH=(values->BinH+(values->BinHCounter/2) ) / values->BinHCounter;
	
	
	if ( (values->co!=-9999) && (values->co != -8888) )
	{
		if (values->co>6500)
		{
			values->co=6500;
		}
		values->Bco+=values->co*10;
		values->BcoCounter++;
		values->Mco=(values->Bco+(values->BcoCounter/2) ) / values->BcoCounter;
		
	}
	else
	{
		
	}
	

	if ((values->hytTemp!=-9999) && (values->hytTemp!= -8888))
	{
		values->BhytTemp+=values->hytTemp;
		values->BhytTempCounter++;
		values->MhytTemp=(values->BhytTemp+(values->BhytTempCounter/2) ) / values->BhytTempCounter;
		
	}
	else
	{

	}
	
	

	if ((values->feuchte!=-9999) && (values->feuchte!= -8888))
	{
		values->Bfeuchte+=values->feuchte;
		values->BfeuchteCounter++;
		values->Mfeuchte=(values->Bfeuchte+(values->BfeuchteCounter/2) ) / values->BfeuchteCounter;
		
	}
	else
	{

	}
	

	if ((values->pressure!=-9999) && (values->pressure!= -8888))
	{
		values->Bpressure+=values->pressure;
		values->BpressureCounter++;
		values->Mpressure=(values->Bpressure+(values->BpressureCounter/2) ) / values->BpressureCounter;
		
	}
	else
	{

	}
	
	if ((values->boschTemp!=-9999) && (values->boschTemp!= -8888))
	{
		values->BboschTemp+=values->boschTemp;
		values->BboschTempCounter++;
		values->MboschTemp=(values->BboschTemp+(values->BboschTempCounter/2) ) / values->BboschTempCounter;
		
	}
	else
	{

	}
	
	if ((values->RHO!=-9999) && (values->RHO!= -8888))
	{
		values->BRHO+=values->RHO;
		values->BRHOCounter++;
		values->MRHO=(values->BRHO+(values->BRHOCounter/2) ) / values->BRHOCounter;
		
	}
	else
	{

	}
	
	if ((values->S!=-9999) && (values->S!= -8888))
	{
		values->BS+=values->S;
		values->BSCounter++;
		values->MS=(values->BS+(values->BSCounter/2) ) / values->BSCounter;
		
	}
	else
	{

	}
	
	if ((values->AF!=-9999) && (values->AF!= -8888))
	{
		values->BAF+=values->AF;
		values->BAFCounter++;
		values->MAF=(values->BAF+(values->BAFCounter/2) ) / values->BAFCounter;
		
	}
	else
	{

	}
	

	if ((values->VPD!=-9999) && (values->VPD!= -8888))
	{
		values->BVPD+=values->VPD;
		values->BVPDCounter++;
		values->MVPD=(values->BVPD+(values->BVPDCounter/2) ) / values->BVPDCounter;
		
	}
	else
	{

	}
	
	
	//values->BufferCounter++;
	
	//if (values->BufferCounter>=values->intervall)
	//{
		//values->Bppfd=0;
		//values->Bco=0;
		//values->BhytTemp=0;
		//values->Bfeuchte=0;
		//values->Bpressure=0;
		//values->BboschTemp=0;
		//values->BRHO=0;
		//values->BS=0;
		//values->BAF=0;
		//values->BVPD=0;
		//
		//values->BppfdCounter=0;
		//values->BcoCounter=0;
		//values->BhytTempCounter=0;
		//values->BfeuchteCounter=0;
		//values->BpressureCounter=0;
		//values->BboschTempCounter=0;
		//values->BRHOCounter=0;
		//values->BSCounter=0;
		//values->BAFCounter=0;
		//values->BVPDCounter=0;
		//
		//values->BufferCounter=0;
	//}
	return 0;
}