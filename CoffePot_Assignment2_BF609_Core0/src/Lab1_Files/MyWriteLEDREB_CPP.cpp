


/*
 * WriteGPIODataCPP.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: kpore
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "BF609_Lab1_Core0.h"
#include <stdio.h>
#include <blackfin.h>

extern "C" void MyWriteLEDREB_ASM(unsigned short int x);

void MyWriteLEDREB_CPP(unsigned short int x){
	MyWriteLEDREB_ASM(x);
	return;
}







