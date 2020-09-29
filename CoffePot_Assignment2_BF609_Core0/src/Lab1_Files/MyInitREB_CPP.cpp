


/*
 * MyInitREB_CPP.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: kpore
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "BF609_Lab1_Core0.h"
#include <blackfin.h>

extern "C" void MyInitREB_ASM(void);

void MyInitREB_CPP(){
	MyInitREB_ASM();
	return;
}







