/*
 * sensValues.c
 *
 * Created: 20.04.2014 10:45:57
 *  Author: knoerk
 */ 
#include "include/sensValues.h"

void init_sensValues(volatile sensValues* values)
{
	values->boschTemp=-9999;
	values->co=-9999;
	values->feuchte=-9999;
	values->hytTemp=-9999;
	values->k30Status=0;
	values->ppfd=0;
	values->pressure=-9999;
	values->RHO=-9999;
	values->S=-9999;
	values->AF=-9999;
	values->VPD=-9999;
	values->inH=-9999;
	
	values->Mppfd=-9999;
	values->Mco=-9999;
	values->MhytTemp=-9999;
	values->Mfeuchte=-9999;
	values->Mpressure=-9999;
	values->MboschTemp=-9999;
	values->MRHO=-9999;
	values->MS=-9999;
	values->MAF=-9999;
	values->MVPD=-9999;
	values->MinH=-9999;
	
	values->Bppfd=0;
	values->Bco=0;
	values->BhytTemp=0;
	values->Bfeuchte=0;
	values->Bpressure=0;
	values->BboschTemp=0;
	values->BRHO=0;
	values->BS=0;
	values->BAF=0;
	values->BVPD=0;
	values->BinH=0;
	
	values->BppfdCounter=0;
	values->BcoCounter=0;
	values->BhytTempCounter=0;
	values->BfeuchteCounter=0;
	values->BpressureCounter=0;
	values->BboschTempCounter=0;
	values->BRHOCounter=0;
	values->BSCounter=0;
	values->BAFCounter=0;
	values->BVPDCounter=0;
	values->BinHCounter=0;
	
}

void zero_sensValues(volatile sensValues* values)
{
	values->boschTemp=-8888;
	values->co=-8888;
	values->feuchte=-8888;
	values->hytTemp=-8888;
	values->k30Status=0;
	values->ppfd=-8888;
	values->pressure=-8888;
	values->RHO=-8888;
	values->S=-8888;
	values->AF=-8888;
	values->VPD=-8888;
	values->inH=-8888;
}

void zeroMeansInsensValues(volatile sensValues* values)
{
	{
		values->Bppfd=0;
		values->Bco=0;
		values->BhytTemp=0;
		values->Bfeuchte=0;
		values->Bpressure=0;
		values->BboschTemp=0;
		values->BRHO=0;
		values->BS=0;
		values->BAF=0;
		values->BVPD=0;
		values->BinH=0;
		
		values->BppfdCounter=0;
		values->BcoCounter=0;
		values->BhytTempCounter=0;
		values->BfeuchteCounter=0;
		values->BpressureCounter=0;
		values->BboschTempCounter=0;
		values->BRHOCounter=0;
		values->BSCounter=0;
		values->BAFCounter=0;
		values->BVPDCounter=0;
		values->BinHCounter=0;
	}
}