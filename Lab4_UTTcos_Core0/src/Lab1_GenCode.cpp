/*
 * Lab1_GenCode.cpp
 *
 *  Created on: Oct 2, 2019
 *      Author: kpore
 */
#include "BF609_Lab1_Core0.h"

using namespace std;

void Start_Lab0(){
	printf("Code stub for Start_Lab0\n");
#if 0
	//initializing hardware test
		unsigned char badLED = My_ReadLED();
	    unsigned char badSwitch = My_ReadSwitches();
#endif

#if 0 //Switch Test
	My_Init_LEDInterface();
	unsigned char switchValue;
	printf("Press Switch 1\n");
	do{
	 switchValue = My_ReadSwitches();
	printf("%d = switch value \n", switchValue);
	if(switchValue!= 1)
	printf("Switch READ test FAILED, try again \n");
	}while(switchValue != 1);
	//Loop causes you to wait until switch 3 is read correctly

	printf("Release Switch 1\n");
	do{
	 switchValue = My_ReadSwitches();
	printf("%d = switch value \n", switchValue);
	if(switchValue&0x01 == 1)
    printf("Switch READ test FAILED, try again \n");
	}while(switchValue&0x01 == 1 );

#endif

#if 0
	char initials [] = { 0xFF , 0x18 , 0x24 , 0x42,0x0, 0xc0, 0x0 , 0xFF , 0x9 , 0x9, 0x6, 0x0, 0xc0 };
	WaitTillSwitch1PressedAndReleased();
	int counter = 0;
	unsigned char patternToDisplay;

while(1){

	while(My_ReadSwitches()!= 4){
		WaitTillSwitch2PressedAndReleased();
		patternToDisplay = initials[counter];
		My_WriteLED(patternToDisplay);
		counter++;
		if(counter>= sizeof(initials))break;
	}
	if(counter>= sizeof(initials))break;
	patternToDisplay = initials[counter];
	My_WriteLED(patternToDisplay);
	counter++;

	}
#endif




#if 0
	//LED Test
	unsigned char useLEDValue = 0x42;
	unsigned char checkLEDValue = My_ReadLED();
	if(checkLEDValue!=useLEDValue)
		printf("LED READ/WRITE test FAILED \n");
#endif



}








#define SHIFT_8BITS 8
#define SHIFT_12BITS 12
#define GARBAGE_VALUE static_cast<unsigned char>(-1)
static unsigned char lastLEDValFP = GARBAGE_VALUE;
static unsigned char lastLEDValREB = GARBAGE_VALUE;
static bool My_Init_LEDInterfaceFP_Done = false;
static bool My_Init_SwitchInterfaceFP_Done = false;
static bool My_Init_LEDandSwitchInterfaceREB_Done = false;



unsigned char My_ReadSwitchesFP(){
	//printf("Code stub for readSwitches\n");
	if(My_Init_SwitchInterfaceFP_Done == false){
		printf("Switch Hardware not ready.\n");
		return GARBAGE_VALUE;
	}
#ifdef __ADSPBF609__
    FRONTPANEL_SWITCH_5BIT_VALUE activeLowValues = Read_GPIO_FrontPanelSwitches();
	FRONTPANEL_SWITCH_5BIT_VALUE activeHighValues = ~activeLowValues;

#define MASK_KEEP_LOWER_FIVE_BITS 0x1F
	FRONTPANEL_SWITCH_5BIT_VALUE wantedSwitchValueActiveHigh = activeHighValues & MASK_KEEP_LOWER_FIVE_BITS;
	return wantedSwitchValueActiveHigh;
#else
	return 0x55;
#endif
}

unsigned char My_ReadLEDREB(){
	//printf("Code stub for readLEDREB\n");

	if( My_Init_LEDandSwitchInterfaceREB_Done == false){
		printf("REB Hardware not ready.\n");
		return GARBAGE_VALUE;
	}
	return lastLEDValREB;
}

unsigned char My_ReadLEDFP(){
	//printf("Code stub for readLEDFP\n");
	if(My_Init_LEDInterfaceFP_Done == false){
		printf("Front Panel LED Hardware not ready.\n");
		return GARBAGE_VALUE;
	}
	return lastLEDValFP;
}



void My_Init_LEDInterfaceFRONTPANEL(){
	printf("Code stub for  My_Init_LEDInterfaceFRONTPANEL\n");
		 My_Init_LEDInterfaceFP_Done = true;
	#ifdef __ADSPBF609__
		 Init_GPIO_FrontPanelLEDS();
	#endif

}

void My_Init_SwitchInterfaceFRONTPANEL(){
		printf("Code stub for InitializeSwitchInterfaceFRONTPANEL\n");
		My_Init_SwitchInterfaceFP_Done = true;

#ifdef __ADSPBF609__
		Init_GPIO_FrontPanelSwitches();
#endif


	}



void My_WriteLEDFP (unsigned char x){
	//printf("Code stub for writeLED\n");
	if(My_Init_LEDInterfaceFP_Done == false){
			printf("LED Hardware not ready.\n");
			return;
		}

#ifdef __ADSPBF609__
	Write_GPIO_FrontPanelLEDS(x);
#else
	lastLEDValFP = x;
	PrintBinaryValue(x);
#endif
}

void PrintBinaryValue(unsigned char bitpattern){
	int maxbits = 0x80;
		while(maxbits>0){
			char bit;
			if((bitpattern & maxbits) > 0 )
				bit = '1';
			else
				bit = ' ';
			printf("%c", bit );
			maxbits>>=1;
		}
		printf("\n");
}

void WaitTillSwitch1PressedAndReleased(){
	unsigned char switchValue = My_ReadSwitchesFP();
	printf("Press switch 1\n");
	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue !=1);
	printf("Release switch 1\n");
	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue & 0x01 == 1 );
	printf("switch 1 pressed and released\n");
}

void WaitTillSwitch2PressedAndReleased(){
	unsigned char switchValue = My_ReadSwitchesFP();
	printf("Press switch 2\n");
	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue & 0x02 != 0x02);

	printf("Release switch 2\n");
	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue&0x02 == 2 );
	printf("switch 2 pressed and released\n");
}

void WaitTillSwitch3PressedAndReleased(){
	unsigned char switchValue = My_ReadSwitchesFP();
	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue !=4);

	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue&0x04 == 4 );
}

void WaitTillSwitch5PressedAndReleased(){
	unsigned char switchValue = My_ReadSwitchesFP();
	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue !=16);

	do{
	 switchValue = My_ReadSwitchesFP();
	}while(switchValue&0x10 == 16 );
}

bool Switch4and5pressed(){
	bool Switch4and5pressed = false;
	unsigned char switchValue = My_ReadSwitchesFP();
	//printf("Waiting for press switch 5?\n");
		do{
		 switchValue = My_ReadSwitchesFP();
		 if(switchValue == 24){
			 //printf("Switch 4 and 5 pressed together?\n");
			Switch4and5pressed = true;
			break;
		 }
		}while(switchValue != 16);

		//printf("Waiting for 5 release?\n");
		do{
		 switchValue = My_ReadSwitchesFP();
		}while(switchValue&0x10 == 16 );

		return Switch4and5pressed;
}
