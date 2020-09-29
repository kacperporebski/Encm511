/*
 * InterruptService.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: kpore
 */

#include "../LinksToFiles/CoreTimer_Code.h"
#include <blackfin.h>


volatile int messageCount = 0;
#pragma interrupt;
void My_ISR(void){
	*pTCNTL = *pTCNTL & (~DONE_BIT);
	messageCount++;
}
