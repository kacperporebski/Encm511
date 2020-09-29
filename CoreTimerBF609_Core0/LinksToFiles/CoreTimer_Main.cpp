/*
 * CoreTimer_Main.cpp
 *
 *  Created on: Nov 18, 2019
 *      Author: kpore
 */
#include "CoreTimer_Code.h"


bool CoreTimer_My_Main(){

	//Init_CoreTimer();
	//Init_REB_Output?

	unsigned short int loopCount = 0;
	unsigned short int countClockTics = 0;

	Start_CoreTimer();

	while((loopCount < 10000)&& (countClockTics < 8 )){
		loopCount++;
		if(Done_CoreTimer())
			countClockTics++;
	}

	Stop_CoreTimer();

	printf("Timer code exited safely -- loopCount %d , clockTics %d \n ", loopCount , countClockTics);


	bool returnValue = false;
	if((loopCount < 10000) && (countClockTics == 8 )){
		returnValue = true;
	}
	return returnValue;

}
