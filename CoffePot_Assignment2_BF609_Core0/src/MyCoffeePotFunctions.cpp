/*
 * MyCoffeePotFunctions.cpp
 *
 *  Created on: Oct 28, 2019
 *      Author: kpore
 */

#include "MyCoffeePotFunctions.h"
#include <stdio.h>

#define SHOW_FUNCTION_STUB 1

void ShowNameProcessorUsed(){

#if defined(__ADSPBF533__)
	char processor[] = "__ADSPBF533__";
#else
	char processor[] = "__ADSPBF609__";
#endif
	printf("Coffee pot running on %s system \n", processor);

}

//Shows the stub of functions used, can be turned on or off.
inline void Show_Function_Stub(char* functionStub){
	if(SHOW_FUNCTION_STUB){
		printf("%s \n", functionStub);
	}

}

extern volatile bool subFlag;
#define CORETIMER_INTERRUPTS_ACTIVATED 1
void My_TIC_CoffeePot(COFFEEPOT_DEVICE* p){
#if CORETIMER_INTERRUPTS_ACTIVATED
	if(subFlag){
		FastForward_OneSimulationTIC(p);
	}
	//DO NOTHING RELY ON CORE-TIMER INTERRUPT
#else
	FastForward_OneSimulationTIC(p);
#endif
}


//Initializes and polls one coffeepot to enable to intended use.
void Init_CoffeePot(COFFEEPOT_DEVICE* pCoffeePot){
	Show_Function_Stub("Init_CoffeePot");
#if 1

	unsigned short int newControlRegisterValue = INITandSTAYPOWEREDON_BIT;
	WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue); //Write to control register

#else
	//Use C++ to access the coffeepot register
		unsigned short int currenetControlRegisterValue = pCoffeePot->controlRegister;
		unsigned short int newControlRegisterValue = INIT_STAY_POWERED_ON;
		pCoffeePot->controlReigster = newControlRegisterValue;
#endif
	//above is setting the POWER_ON and INIT bit in Coffee Pot control reg
	// Then in a loop -- read control reg, use bitwise AND to see if device ready
	// When ready -> exit
		My_TIC_CoffeePot(pCoffeePot);
	unsigned short int currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
	while((currentControlRegisterValue & 0x0011 ) != 0x0011){

		FastForward_OneSimulationTIC(pCoffeePot);
		currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);

	}

		ToggleLED_CPP(LED1_BIT, pCoffeePot);
		//TURN ON LED 1 TO INDICATE IT IS INTIALIZED CORRECTLY

}


//Activates the LEDs on ONE coffeepot
void Activate_LED_Control(COFFEEPOT_DEVICE* pCoffeePot){
	Show_Function_Stub("Activate_LED_Control");
	unsigned short int currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
	unsigned short int newControlRegisterValue = LED_DISPLAY_ENABLE_BIT | currentControlRegisterValue;
		WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue);
		//Turn on LED_POWER bit in control register, without turning off other bits

		while((currentControlRegisterValue & 0x0013 ) != 0x0013){

				currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
				My_TIC_CoffeePot(pCoffeePot);
			}

		//Wait till LED responds and is ready
		ToggleLED_CPP(LED4_BIT, pCoffeePot);
		//Turn LED4 on to represent this.

}


extern COFFEEPOT_DEVICE *pMyCoffeePot1;
extern COFFEEPOT_DEVICE *pMyCoffeePot2;
//Toggles the LED value you pass into the function on the desired coffeepot
void ToggleLED_CPP(unsigned short int LED_BIT_VALUE, COFFEEPOT_DEVICE* pCoffeePot){
	unsigned short int LEDchar = LED_BIT_VALUE>>12;
	unsigned short int currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
	unsigned short int newControlRegisterValue;


	if(pCoffeePot == pMyCoffeePot1)
	{

	if((currentControlRegisterValue & LED_BIT_VALUE) == LED_BIT_VALUE)
		{
		printf("TURN LED OFF");
			unsigned short int newControlRegisterValue = ((~LED_BIT_VALUE) & currentControlRegisterValue);
			printf("HELP: 0x%x\n",((~LED_BIT_VALUE) & currentControlRegisterValue) );
			WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue);
			printf("HELO: 0x%x\n", My_ReadLEDFP()&(~LEDchar));
			My_WriteLEDFP(My_ReadLEDFP()&(~LEDchar));
			My_TIC_CoffeePot(pCoffeePot);
			//if LED is ON then turn OFF
		}
	else{
		printf("TURN LED ON");
		newControlRegisterValue = (LED_BIT_VALUE | currentControlRegisterValue);
		//else TURN ON since its off
		WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue);
		My_WriteLEDFP(My_ReadLEDFP()|LEDchar);
		My_TIC_CoffeePot(pCoffeePot);
		//Write to control and update.
		}

	}
	else if( pCoffeePot == pMyCoffeePot2)
	{

		if((currentControlRegisterValue & LED_BIT_VALUE) == LED_BIT_VALUE)
			{
				unsigned short int newControlRegisterValue = (~LED_BIT_VALUE) & currentControlRegisterValue;
				WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue);
				My_WriteREB(My_ReadLEDREB()&(~LEDchar));
				My_TIC_CoffeePot(pCoffeePot);
				//if LED is ON then turn OFF
			}
			else
			{
				newControlRegisterValue = LED_BIT_VALUE | currentControlRegisterValue;
				//else TURN ON since its off
				WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue);
				My_WriteREB(My_ReadLEDREB()|LEDchar);
				My_TIC_CoffeePot(pCoffeePot);
			}
	}
}

void Demonstrate_LEDControl_CPP(COFFEEPOT_DEVICE* pCoffeePot){
	Show_Function_Stub("Demonstrate_LEDControl_CPP");

	ToggleLED_CPP(LED1_BIT, pCoffeePot);
	ToggleLED_CPP(LED1_BIT, pCoffeePot);
	ToggleLED_CPP(LED2_BIT, pCoffeePot);
	ToggleLED_CPP(LED2_BIT, pCoffeePot);
	ToggleLED_CPP(LED3_BIT, pCoffeePot);
	ToggleLED_CPP(LED3_BIT, pCoffeePot);
	ToggleLED_CPP(LED4_BIT, pCoffeePot);
	ToggleLED_CPP(LED4_BIT, pCoffeePot);
//Flash LED 1 through 3 on the desired CoffeePot.

}



//Activates water control for the desired pot.
void Activate_Water_Control(COFFEEPOT_DEVICE* pCoffeePot){
	Show_Function_Stub("Activate Water");


	unsigned short int currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
		unsigned short int newControlRegisterValue = WATER_ENABLE_BIT | currentControlRegisterValue;
			WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue);
			//Turn on WATER_ENABLE_BIT bit in control register, without turning off other bits

			while((currentControlRegisterValue & WATER_ENABLE_BIT) != WATER_ENABLE_BIT){

					currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
					My_TIC_CoffeePot(pCoffeePot);
				}
			ToggleLED_CPP(LED3_BIT, pCoffeePot);//Turn LED3 on to represent this.
			//Wait till coffeepot responds and is ready

}


//Fills the desired coffeepot with water.
#define WATER_ADJUSTMENT_VALUE 50
#define WATER_FLOW_VALUE 30
void FillCoffeePotToWaterLevel(int waterLevel, COFFEEPOT_DEVICE* pCoffeePot){
	Show_Function_Stub("FillCoffeePotToWaterLevel");
	if((ReadControlRegister_CPP(pCoffeePot) & WATER_ENABLE_BIT) != WATER_ENABLE_BIT){
		printf("Water flow not enabled");
		return;
	}
	//Check if water control is enabled.



	int waterFlow = WATER_FLOW_VALUE;
	if((CurrentWaterLevel_CPP(pCoffeePot) + (WATER_ADJUSTMENT_VALUE)) >= waterLevel ){
			My_TIC_CoffeePot(pCoffeePot);
				return;
	}
	//Check if water level is within a safe range.

	pCoffeePot->waterInFlowRegister = waterFlow;

		My_TIC_CoffeePot(pCoffeePot);

	//Update register to pour more water.



}

//Activates the heater control for the desired coffeepot.
void Activate_Heater_Control(COFFEEPOT_DEVICE* pCoffeePot){
	Show_Function_Stub("Activate Heater Control");
	unsigned short int currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
		unsigned short int newControlRegisterValue = HEATER_ENABLE_BIT| currentControlRegisterValue;
			WriteControlRegister_CPP(pCoffeePot, newControlRegisterValue);
			//Turn on LED_POWER bit in control register, without turning off other bits

			while((currentControlRegisterValue & HEATER_ENABLE_BIT ) != HEATER_ENABLE_BIT){

					currentControlRegisterValue = ReadControlRegister_CPP(pCoffeePot);
					My_TIC_CoffeePot(pCoffeePot);
				}
			ToggleLED_CPP(LED2_BIT, pCoffeePot);//Turn LED2 on to represent this.
	}



//Heats water to the desired temperature.
#define SAFETY_TEMP 15
#define MAX_HEAT_REG 200
#define MAX_BOOST_REG 15
#define MAX_WATER_LEVEL 500
void HeatWaterToTemperature(int temperature, COFFEEPOT_DEVICE* pCoffeePot){
	Show_Function_Stub("HeatWaterToTemperature");
	if((ReadControlRegister_CPP(pCoffeePot) & HEATER_ENABLE_BIT) != HEATER_ENABLE_BIT){
			printf("heat bit not enabled");
			return;
		}

	//Check if heater is activated
	if(CurrentTemperature_CPP(pCoffeePot) + SAFETY_TEMP > temperature)
		return;

	//Check if temperature value is in a safe range



	pCoffeePot->heaterRegister = MAX_HEAT_REG;
	pCoffeePot->heaterBoostRegister = MAX_BOOST_REG;
	//Turn on heater to increase temperature

	if((CurrentTemperature_CPP(pCoffeePot) > 80 ) && (CurrentWaterLevel_CPP(pCoffeePot) < 450))
		FillCoffeePotToWaterLevel(MAX_WATER_LEVEL, pCoffeePot);
	//If water is evaporating and bellow a certain level -> add more water

		My_TIC_CoffeePot(pCoffeePot);




	}

//Fills the Pot with water and then heats it using above functions
void Control_Both_Temp_And_Water(int water_level, int temperature ,  COFFEEPOT_DEVICE* pCoffeePot){
		FillCoffeePotToWaterLevel(water_level, pCoffeePot);
	if(CurrentWaterLevel_CPP(pCoffeePot) > 400 && CurrentTemperature_CPP(pCoffeePot) < 90)
		HeatWaterToTemperature(temperature, pCoffeePot);


}


bool switch5Pressed = false;
bool switch5Released = false;
#define SWITCH5 0x10
void switch5PressedAndReleased(){
	if((My_ReadSwitchesFP() & SWITCH5) == SWITCH5) {//pressed
		switch5Pressed = true;
		printf("fp 5 pressed");
		}

	if(switch5Pressed) {//pressed
			if((My_ReadSwitchesFP() & SWITCH5) == 0){	//released
				switch5Released= true;
			printf("fp 5 released");
			}
		}


}

