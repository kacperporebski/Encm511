/*
 * ReadProcessorCyclesCPP.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: kpore
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "BF609_Lab1_Core0.h"
#include <blackfin.h>

extern "C" unsigned long long int ReadProcessorCyclesASM(void);

unsigned long long int ReadProcessorCyclesCPP(void){
	//printf("In ReadProcessorCyclesCPP\n");

#if 0
	unsigned long long int cyclesValue = *pCYCLES;
	return cyclesValue;   //DOES NOT WORK SINCE CANT ACCESS *pCYCLES DIRECTLY CAUSE HARDWARE REGISTER
#else
	unsigned long long int cyclesValue = ReadProcessorCyclesASM();
			return cyclesValue;
#endif
}

