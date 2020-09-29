 /*
 * CoreTimer_Code.cpp
 *
 *  Created on: Nov 18, 2019
 *      Author: kpore
 */
#include "CoreTimer_Code.h"

#define TEST_SET_COUNTER 40000 //acts as first delay
#define TEST_SET_PERIOD 20000
#define TEST_SET_CONTROL (POWER_ON_BIT | AUTORELOAD_BIT)
#define TEST_SET_TSCALE 0

void ShowStubMessage(char *message, bool showMessage){
if(showMessage) printf("%s\n" , message);

}

#include <blackfin.h>

unsigned long int Planned_CoreTimerRegisterValue(CORETIMER_REG regName){
	ShowStubMessage("Planned_CoreTimerRegisterValue()", false);

	unsigned long int returnValue = (unsigned long int) 0xFFFFFFFF;

	switch(regName){
	case REG_CONTROL: returnValue = TEST_SET_CONTROL; break;
	case REG_COUNTER: returnValue = TEST_SET_COUNTER; break;
	case REG_PERIOD: returnValue = TEST_SET_PERIOD; break;
	case REG_TSCALE: returnValue = TEST_SET_TSCALE; break;
	default: printf("Unknown request \n");
	}

	return returnValue;



}


unsigned long int Read_CoreTimerRegister(CORETIMER_REG regName){
	ShowStubMessage("Read_CoreTimerRegister()" , false);
	unsigned long int returnValue = (unsigned long int) 0xFFFFFFFF;

		switch(regName){
		case REG_CONTROL: returnValue = *pTCNTL; break;
		case REG_COUNTER: returnValue = *pTCOUNT; break;
		case REG_PERIOD: returnValue = *pTPERIOD; break;
		case REG_TSCALE: returnValue = *pTSCALE; break;
		default: printf("Unknown request \n");
		}

		return returnValue;


}


void Write_CoreTimerRegisterValue(CORETIMER_REG regName, unsigned long int newValue){
	ShowStubMessage("Write_CoreTimerRegisterValue", false);

	switch(regName){
			case REG_CONTROL: *pTCNTL=newValue; break;
			case REG_COUNTER: *pTCOUNT=newValue; break;
			case REG_PERIOD: *pTPERIOD=newValue; break;
			case REG_TSCALE: *pTSCALE=newValue; break;
			default: printf("Unknown request \n");
			}



}


void Init_CoreTimer(unsigned long int period, unsigned long int count){
	ShowStubMessage("Init_CoreTimer()", true);

	Write_CoreTimerRegisterValue(REG_PERIOD, period);
	Write_CoreTimerRegisterValue(REG_COUNTER, count);
	Write_CoreTimerRegisterValue(REG_TSCALE,0);
	Write_CoreTimerRegisterValue(REG_CONTROL, AUTORELOAD_BIT | POWER_ON_BIT);


}

void Start_CoreTimer(void){
	ShowStubMessage("Start_CoreTimer()", true);
	*pTCNTL = *pTCNTL | (POWER_ON_BIT| ENABLE_BIT) ;

}

void Stop_CoreTimer(void){
	ShowStubMessage("Stop_CoreTimer()", false);
	*pTCNTL = *pTCNTL & (~ENABLE_BIT) ;

}




void TimedWaitOnCoreTimer(void){
 ShowStubMessage("Timed wait()", true);

	while(1){
		if(Done_CoreTimer())
			break;
	}


}



#define TCNTRLBITS_3_1_0 (ENABLE_BIT | POWER_ON_BIT | DONE_BIT)

bool Done_CoreTimer(void){
	ShowStubMessage("Done_CoreTimer", false);
	bool returnValue = false;

	if( (*pTCNTL & TCNTRLBITS_3_1_0) == TCNTRLBITS_3_1_0){
		*pTCNTL = *pTCNTL & (~DONE_BIT);
		returnValue = true;
	}

	return returnValue;
	}



