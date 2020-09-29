/*
 * InterruptService.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: kpore
 */

#include "CORETIMER LIBRARY/CoreTimer_Code.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/CoffeePot_SimulatorFunctions2017.h"
#include <blackfin.h>



volatile int message = 0;
volatile bool subFlag = false;
extern COFFEEPOT_DEVICE *pMyCoffeePot1;
extern COFFEEPOT_DEVICE *pMyCoffeePot2;


#pragma interrupt
void ISR_TIC(){
	*pTCNTL = *pTCNTL & (~DONE_BIT);	//SETTING TINT TO ZERO -> CLEAR CT INTERRUPT

	ssync();		//write right now


	if(message == 3){

		subFlag = true;		//turn on subroutine flag since u dont call subroutines in ISR
		message = 0;		//if you want it to be fast
	}
	message++;


}



