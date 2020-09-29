/*
 * CoffePot_Main.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: kpore
 */


#include <stdio.h>
#include <sys/exception.h>
#include <blackfin.h>
#include "MyCoffeePotFunctions.h"


#define MAX_SECONDS 50
#define MAX_WATER_LEVEL_POTS_ONE_TWO_FOUR 410
#define MAX_TEMPERATURE 90

#define LEDOFF
#define FINAL					//HEAT AND WATER
#define ONLYFINAL				//INITIALIZE HEAT AND WATER ONLY IN FINAL

#pragma interrupt;
void  ISR_TIC();

COFFEEPOT_DEVICE *pMyCoffeePot1;
COFFEEPOT_DEVICE *pMyCoffeePot2;

void Start_Assignment2(void){
#define ONE_SECOND 4000
//Initializing the simulation
	ShowNameProcessorUsed();

	My_Init_LEDandSwitchInterfaceREB();
	My_Init_SwitchInterfaceFRONTPANEL();
	My_Init_LEDInterfaceFRONTPANEL();
	printf("initialized hardware");
	Init_CoffeePotSimulation(COFFEEPOT2, USE_TEXT_AND_GRAPHICS_GUIS);
	pMyCoffeePot1 = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT1, "I hate coffee");
	pMyCoffeePot2 = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT2, "Kacper Porebski");

	Init_CoreTimer(2*ONE_SECOND , 2*ONE_SECOND);
	Init_CoffeePot(pMyCoffeePot1);
	Init_CoffeePot(pMyCoffeePot2);

	register_handler(ik_timer,  ISR_TIC);

	Start_CoreTimer();
	Start_CoreTimer_Interrupt();



		Activate_LED_Control(pMyCoffeePot1);
		Activate_LED_Control(pMyCoffeePot2);
		Activate_Water_Control(pMyCoffeePot1);
		Activate_Water_Control(pMyCoffeePot2);
		Activate_Heater_Control(pMyCoffeePot1);
		Activate_Heater_Control(pMyCoffeePot2);

	unsigned long int secondsCounter = 0;



//	while(secondsCounter < 200){
//
//		if(My_ReadSwitchesFP()== 0x10){
//			printf("Switch 5 fp pressed\n");
//			while((My_ReadSwitchesFP()&0x10) != 0){
//				unsigned short int currentControlRegisterValue = ReadControlRegister_CPP(pMyCoffeePot1);
//				unsigned short int currentControlRegisterValue2 = ReadControlRegister_CPP(pMyCoffeePot2);
//				unsigned short int newControlRegisterValue =
//						( (0xF & My_ReadSwitchesFP()) | ((currentControlRegisterValue & 0x0FF0)) | (My_ReadSwitchesFP() << 12));
//				WriteControlRegister_CPP(pMyCoffeePot1, newControlRegisterValue);
//				My_WriteLEDFP(0xF & My_ReadSwitchesFP());
//
//				unsigned short int newControlRegisterValue2 =
//						( My_ReadSwitchesREB() | ((currentControlRegisterValue2 & 0xFFF0) | (0xF & My_ReadSwitchesREB() << 12)));
//				printf("ReadSwitchesREB: %x \n",My_ReadSwitchesREB() );
//				WriteControlRegister_CPP(pMyCoffeePot2, newControlRegisterValue2);
//				My_WriteREB(0xF & My_ReadSwitchesREB());
//
//				My_TIC_CoffeePot(pMyCoffeePot1);
//
//
//			}
//
//			printf("Switch 5 fp released");
//
//
//		}
//		//printf("counter = %d \n", secondsCounter);
//		secondsCounter++;
//
//	}
//	secondsCounter==0;

//using conditional compiling the below test code segment will flash the LEDs of the different pots using
// a CPP function. The amount of times this test will run can be lengthened or shortened by modifying
//MAX_SECONDS, however this will affect all demonstrations so keep that in mind.
#ifdef LED

		bool continueDemonstrate_LEDControl = true;
	while(continueDemonstrate_LEDControl){
		Demonstrate_LEDControl_CPP(pMyCoffeePot1);
		Demonstrate_LEDControl_CPP(pMyCoffeePot2);
		if(++secondsCounter >= MAX_SECONDS)
			continueDemonstrate_LEDControl = false;
}
#endif


//using conditional compiling the below test code segment will flash the LED corresponding to Pot number using
// the written ASM function. The amount of times this test will run can be lengthened or shortened by modifying
//MAX_SECONDS, however this will affect all demonstrations so keep that in mind. Instead you can add
//an offset into the for loop for quicker way to see the operations.
#ifdef LATER
#ifndef FOURPOTS
	Activate_LED_Control(pMyCoffeePot1);
#endif
#ifdef FOURPOTS
	Activate_LED_Control(pMyCoffeePot1, pMyCoffeePot2, pMyCoffeePot3, pMyCoffeePot4);
#endif
	printf("Demonstrating LED by flashing each LED on different pots:\n");
	bool continueDemonstrate_LEDControl_ASM = true;
	while(continueDemonstrate_LEDControl_ASM){
		Demonstrate_LEDControl_ASM(pMyCoffeePot1, LED1_BIT);
		Demonstrate_LEDControl_ASM(pMyCoffeePot1, LED1_BIT);
#ifdef FOURPOTS
		Demonstrate_LEDControl_ASM(pMyCoffeePot2, LED2_BIT);
		Demonstrate_LEDControl_ASM(pMyCoffeePot2, LED2_BIT);
		Demonstrate_LEDControl_ASM(pMyCoffeePot3, LED3_BIT);
		Demonstrate_LEDControl_ASM(pMyCoffeePot3, LED3_BIT);
		Demonstrate_LEDControl_ASM(pMyCoffeePot4, LED4_BIT);
		Demonstrate_LEDControl_ASM(pMyCoffeePot4, LED4_BIT);
#endif
		if(++secondsCounter >= MAX_SECONDS-14)
			continueDemonstrate_LEDControl_ASM = false;


	}


#endif

#ifdef EVEN_LATER
	Activate_Water_Control(pMyCoffeePot1);
#ifdef FOURPOTS
	Activate_Water_Control(pMyCoffeePot2);
	Activate_Water_Control(pMyCoffeePot3);
	Activate_Water_Control(pMyCoffeePot4);
#endif
	bool continueDemonstrate_WaterControl = true;
	 secondsCounter = 0;

	while(continueDemonstrate_WaterControl ){
		FillCoffeePotToWaterLevel(MAX_WATER_LEVEL, pMyCoffeePot1, NUM_OF_POTS);
#ifdef FOURPOTS
		FillCoffeePotToWaterLevel(MAX_WATER_LEVEL, pMyCoffeePot2, NUM_OF_POTS);
		FillCoffeePotToWaterLevel(MAX_WATER_LEVEL, pMyCoffeePot3, NUM_OF_POTS);
		FillCoffeePotToWaterLevel(MAX_WATER_LEVEL, pMyCoffeePot4, NUM_OF_POTS);
#endif
		if(++secondsCounter >= MAX_SECONDS)
					continueDemonstrate_WaterControl = false;


	}


	Activate_Heater_Control(pMyCoffeePot1);
#ifdef FOURPOTS
	Activate_Heater_Control(pMyCoffeePot2);
	Activate_Heater_Control(pMyCoffeePot3);
	Activate_Heater_Control(pMyCoffeePot4);
#endif
	bool continueDemonstrate_HeaterControl = true;
	secondsCounter = 0;
	while(continueDemonstrate_HeaterControl){
		HeatWaterToTemperature(MAX_TEMPERATURE, pMyCoffeePot1, NUM_OF_POTS);
#ifdef FOURPOTS
		HeatWaterToTemperature(MAX_TEMPERATURE, pMyCoffeePot2, NUM_OF_POTS);
		HeatWaterToTemperature(MAX_TEMPERATURE, pMyCoffeePot3, NUM_OF_POTS);
		HeatWaterToTemperature(MAX_TEMPERATURE, pMyCoffeePot4, NUM_OF_POTS);
#endif
		if(++secondsCounter >= MAX_SECONDS)
					continueDemonstrate_HeaterControl = false;


	}


#endif


	//Main demonstration of the Coffepot assignment
	//Here water and heat are activated, then the temperature and water level
	//of the pots is controlled to stay full and well heated.
	//Currently I have the loop running for a reasonable length of time
	//which is 215 iterations without any problems.


#ifdef ONLYFINAL

	extern bool switch5Pressed;
	extern bool switch5Released;
	bool continueDemonstrate_TempAndWater = true;
	while(continueDemonstrate_TempAndWater){
		switch5PressedAndReleased();
		if(switch5Pressed && switch5Released){
			unsigned short int currentControlRegisterValue = ReadControlRegister_CPP(pMyCoffeePot1);
			unsigned short int currentControlRegisterValue2 = ReadControlRegister_CPP(pMyCoffeePot2);
			unsigned short int newControlRegisterValue =
			( (0xF & My_ReadSwitchesFP()) | ((currentControlRegisterValue & 0x0FF0)) | (My_ReadSwitchesFP() << 12));
			WriteControlRegister_CPP(pMyCoffeePot1, newControlRegisterValue);
			My_WriteLEDFP(0xF & My_ReadSwitchesFP());
			unsigned short int newControlRegisterValue2 =
			( My_ReadSwitchesREB() | (currentControlRegisterValue2 & 0x0FF0) | (My_ReadSwitchesREB() << 12));
			//printf("ReadSwitchesREB: %x \n",My_ReadSwitchesREB() );
			WriteControlRegister_CPP(pMyCoffeePot2, newControlRegisterValue2);
			My_WriteREB(0xF & My_ReadSwitchesREB());
			My_TIC_CoffeePot(pMyCoffeePot1);

		}

		FillCoffeePotToWaterLevel(MAX_WATER_LEVEL_POTS_ONE_TWO_FOUR, pMyCoffeePot1);
		FillCoffeePotToWaterLevel(MAX_WATER_LEVEL_POTS_ONE_TWO_FOUR, pMyCoffeePot2);
		HeatWaterToTemperature(MAX_TEMPERATURE, pMyCoffeePot1);
		HeatWaterToTemperature(MAX_TEMPERATURE, pMyCoffeePot1);
				if(++secondsCounter >= MAX_SECONDS+200)
				continueDemonstrate_TempAndWater = false;


	}
#endif


}
