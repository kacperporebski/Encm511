/*
 * SPI_Test.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: kpore
 */

#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_SPI_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/GP_Timer_Library.h"

void SPI_Test()
{
	Init_REB_SPI();
	SetBoardLED_SPI_ConfigSoftSwitches();
	Start_REB_SPI();
	unsigned short int count = 0;
	while (1) {
		while(!REB_SPI_Ready())
		{
			//do nothing
		}
		REB_Write_SPI(count ++);
	}
}

void SPI_Temp_Test()
{
	Init_REB_SPI();
	SetBoardLED_SPI_ConfigSoftSwitches();
	Start_REB_SPI();
	Init_GP_Timer(3);
	Start_GP_Timer(3);
	unsigned long int temp;
	unsigned long int T1;
	unsigned long int T2;
	while(1){
		while(!REB_SPI_Ready())
				{
					//do nothing
				}
		T2 = ReadWidth_GP_Timer(3);
		T1 = ReadPeriod_GP_Timer(3) - T2;
		temp = 235 - (400*T1) / T2;
		REB_Write_SPI(temp);
	}


}
