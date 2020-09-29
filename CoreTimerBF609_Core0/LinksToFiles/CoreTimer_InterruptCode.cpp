/*
 * CoreTimer_InterruptCode.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: kpore
 */

#include "blackfin.h"
#include "CoreTimer_InterruptCode.h"

void Start_CoreTimer_Interrupt(){

#define IVTMR 0x40

	*pIMASK = *pIMASK | IVTMR;

	return;
}

void Stop_CoreTimer_Interrupt(){

	*pIMASK = *pIMASK & (~IVTMR);
	return;
}


void CoreTimer_SWI(void){
	Raise_ILAT_BIT6_ASM();
}
