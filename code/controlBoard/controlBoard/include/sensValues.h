/*
 * sensValues.h
 *
 * Created: 20.04.2014 08:45:28
 *  Author: knoerk
 */ 


#ifndef SENSVALUES_H_
#define SENSVALUES_H_

#include <avr/io.h>


typedef struct
{
	int16_t ppfd;
	uint16_t co;
	int16_t hytTemp;
	int16_t feuchte;
	int32_t pressure;
	int16_t boschTemp;
	uint8_t k30Status;
	int16_t RHO;
	int16_t S;
	int16_t AF;
	int16_t VPD;
	int16_t inH;
	
	int16_t Mppfd;
	int16_t Mco;
	int16_t MhytTemp;
	int16_t Mfeuchte;
	int32_t Mpressure;
	int16_t MboschTemp;
	int16_t MRHO;
	int16_t MS;
	int16_t MAF;
	int16_t MVPD;
	int16_t MinH;
	
	int32_t Bppfd;
	int32_t Bco;
	int32_t BhytTemp;
	int32_t Bfeuchte;
	int32_t Bpressure;
	int32_t BboschTemp;
	int32_t BRHO;
	int32_t BS;
	int32_t BAF;
	int32_t BVPD;
	int32_t BinH;
	
	int16_t BppfdCounter;
	int16_t BcoCounter;
	int16_t BhytTempCounter;
	int16_t BfeuchteCounter;
	int16_t BpressureCounter;
	int16_t BboschTempCounter;
	int16_t BRHOCounter;
	int16_t BSCounter;
	int16_t BAFCounter;
	int16_t BVPDCounter;
	int16_t BinHCounter;
} sensValues;

void init_sensValues(volatile sensValues* values);
void zero_sensValues(volatile sensValues* values);
void zeroMeansInsensValues(volatile sensValues* values);

#endif /* SENSVALUES_H_ */