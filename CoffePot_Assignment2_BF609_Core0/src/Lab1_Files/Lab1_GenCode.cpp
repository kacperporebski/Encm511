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


	char initials [] = { 0xFF , 0x18 , 0x24 , 0x42,0x0, 0xc0, 0x0 , 0xFF , 0x9 , 0x9, 0x6, 0x0, 0xc0 };
	int counter = 0;
	unsigned char patternToDisplay;
	unsigned long long int TimeToWait = 48000000;
	unsigned long long int TimeNow;
	unsigned long long int TimeAtLoopStart;
	TimeAtLoopStart = ReadProcessorCyclesCPP();
while(1){

	patternToDisplay = initials[counter];
	My_WriteLEDFP(patternToDisplay);
	counter++;
	if((My_ReadSwitchesFP()&0x01) == 0x01)		//switch 1 pressed speed up
		TimeToWait = TimeToWait/1.5;
	if((My_ReadSwitchesFP()&0x02) == 0x02)		//switch 2 pressed slow down
		TimeToWait = TimeToWait*1.5;
	TimeNow = ReadProcessorCyclesCPP();
	while(TimeNow < ( TimeAtLoopStart + TimeToWait) ){
	TimeNow = ReadProcessorCyclesCPP();			//WAIT
	}
	TimeAtLoopStart = ReadProcessorCyclesCPP();
	if(counter==sizeof(initials))
		counter=0;
	if((My_ReadSwitchesFP()&0x10) == 0x10)
		return;

	}



#if 0
	//LED Test
	unsigned char useLEDValue = 0x42;
	unsigned char checkLEDValue = My_ReadLED();
	if(checkLEDValue!=useLEDValue)
		printf("LED READ/WRITE test FAILED \n");
#endif



}

void Start(){
	printf("Starting program \n");
	//initialize hardware
	My_Init_LEDandSwitchInterfaceREB();
	My_Init_SwitchInterfaceFRONTPANEL();
	My_Init_LEDInterfaceFRONTPANEL();
	printf("Press all REB switches to start lab 1\n");
	printf("Disable all REB switches to start lab 0 \n");
while(1)
{


	if(My_ReadSwitchesREB() == 15)
	{
		printf("starting lab 0\n");
		Start_Lab0();
	}
	else if(My_ReadSwitchesREB() == 0)
	{
		printf("starting lab 1\n");
		Start_Lab1();
	}


}

}

void Start_Lab1(){
	//Code Stub
	printf("Code stub for Start_Lab1\n");

		//hardware fill array
	char hardware[100];
	static int counter = 0;

	while(1)
	{

		if(Switch4and5pressed() == false) {
		hardware[counter] = My_ReadSwitchesREB();
		printf("added %x to array\n" , hardware[counter]);
		counter++;
		}
		else
			break;
		if(counter >= sizeof(hardware)){
			counter = 0;
		}




	}

	WaitTillSwitch5PressedAndReleased();
	printf("Hardware array filled , displaying now \n");
	unsigned char patternToDisplay;
	unsigned long long int TimeToWait = 48000000;
	unsigned long long int TimeNow;
	unsigned long long int TimeAtLoopStart;
	int index = 0;
	TimeAtLoopStart = ReadProcessorCyclesCPP();
while(1){

	patternToDisplay = hardware[index];
	//printf("displaying %x from array" , patternToDisplay);
	My_WriteREB(patternToDisplay);
	index++;
		if((My_ReadSwitchesREB()&0x01) == 0x01)		//switch 1 pressed speed up
			TimeToWait = TimeToWait/1.5;
		if((My_ReadSwitchesREB()&0x02) == 0x02)		//switch 2 pressed slow down
			TimeToWait = TimeToWait*1.5;

	TimeNow = ReadProcessorCyclesCPP();

		while(TimeNow < ( TimeAtLoopStart + TimeToWait) ){
			TimeNow = ReadProcessorCyclesCPP();			//WAIT
		}

	if(index==counter)
		index=0;

	if((My_ReadSwitchesFP()&0x01) == 0x01)
			return;

	TimeAtLoopStart = ReadProcessorCyclesCPP();

		}




	//printf("Leaving Start_Lab1 function\n");


}



#define SHIFT_8BITS 8
#define SHIFT_12BITS 12
#define GARBAGE_VALUE static_cast<unsigned char>(-1)
static unsigned char lastLEDValFP = 0;
static unsigned char lastLEDValREB = 0;
static bool My_Init_LEDInterfaceFP_Done = false;
static bool My_Init_SwitchInterfaceFP_Done = false;
static bool My_Init_LEDandSwitchInterfaceREB_Done = false;

unsigned char My_ReadSwitchesREB(){
	//printf("Code stub for readSwitchesREB\n");
	if(My_Init_SwitchInterfaceFP_Done == false){
		printf("Switch Hardware not ready.\n");
		return GARBAGE_VALUE;
	}
	if( My_Init_LEDandSwitchInterfaceREB_Done == false){
			printf("REB Hardware not ready.\n");
			return GARBAGE_VALUE;
		}
#ifdef __ADSPBF609__
   // REB_BITS16 activeHighValues = Read_GPIO_REB_Input();
    REB_BITS16 activeHighValues = MyReadSwitchesREB_CPP();
    activeHighValues = activeHighValues >> SHIFT_8BITS;
#define MASK_KEEP_LOWER_FOUR_BITS 0x0F
	REB_BITS16 wantedSwitchValueActiveHigh = activeHighValues & MASK_KEEP_LOWER_FOUR_BITS;
	return wantedSwitchValueActiveHigh;
#else
	return 0x55;
#endif
}

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

void My_Init_LEDandSwitchInterfaceREB(){
	printf("Code stub for  My_Init_LEDandSwitchInterface\n");
	My_Init_LEDandSwitchInterfaceREB_Done = true;
#ifdef __ADSPBF609__
	 MyInitREB_CPP();
#endif

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

void My_WriteREB (unsigned char x){
	//printf("Code stub for writeLED\n");
	if(My_Init_LEDandSwitchInterfaceREB_Done == false){
			printf("REB Hardware not ready.\n");
			return;
		}

#ifdef __ADSPBF609__
	lastLEDValREB=x;
	MyWriteLEDREB_CPP(x << SHIFT_12BITS);
#else
	lastLEDValREB = x;
	PrintBinaryValue(x);
#endif
}

void My_WriteLEDFP (unsigned char x){
	//printf("Code stub for writeLED\n");
	if(My_Init_LEDInterfaceFP_Done == false){
			printf("LED Hardware not ready.\n");
			return;
		}
	lastLEDValFP = x;

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
