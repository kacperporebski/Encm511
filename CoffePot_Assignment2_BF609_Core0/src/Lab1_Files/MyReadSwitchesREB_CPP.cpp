/*
 * Read_FIO_FLAG_CPP.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: kpore
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "BF609_Lab1_Core0.h"
#include <blackfin.h>

extern "C" unsigned short int MyReadSwitchesREB_ASM(void);

unsigned short int MyReadSwitchesREB_CPP(void){
	//printf("In ReadProcessorCyclesCPP\n");

	unsigned short int readREBData = MyReadSwitchesREB_ASM();
	return readREBData;
}







