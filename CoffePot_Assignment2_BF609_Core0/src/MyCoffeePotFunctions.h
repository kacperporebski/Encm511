/*
 * MyCoffeePotFunctions.h
 *
 *  Created on: Oct 28, 2019
 *      Author: kpore
 */

#ifndef MYCOFFEEPOTFUNCTIONS_H_
#define MYCOFFEEPOTFUNCTIONS_H_


#include "../../ENCM511_SpecificFiles/ENCM511_include/CoffeePot_SimulatorFunctions2017.h"
void ShowNameProcessorUsed();
void Init_CoffeePot(COFFEEPOT_DEVICE* pCoffeePot);
void Init_CoffeePot(COFFEEPOT_DEVICE* pCoffeePot1, COFFEEPOT_DEVICE* pCoffeePot2, COFFEEPOT_DEVICE* pCoffeePot3 , COFFEEPOT_DEVICE* pCoffeePot4 );
void Activate_LED_Control(COFFEEPOT_DEVICE* pCoffeePot);
void Activate_LED_Control(COFFEEPOT_DEVICE* pCoffeePot1, COFFEEPOT_DEVICE* pCoffeePot2, COFFEEPOT_DEVICE* pCoffeePot3 , COFFEEPOT_DEVICE* pCoffeePot4);
void Activate_Heater_Control(COFFEEPOT_DEVICE* pCoffeePot);
void Demonstrate_LEDControl_CPP(COFFEEPOT_DEVICE* pCoffeePot);
void FillCoffeePotToWaterLevel(int waterLevel , COFFEEPOT_DEVICE* pCoffeePot);
void Activate_Water_Control(COFFEEPOT_DEVICE* pCoffeePot);
void HeatWaterToTemperature(int temperature, COFFEEPOT_DEVICE* pCoffeePot);
void ToggleLED_CPP(unsigned short int LED_BIT_VALUE , COFFEEPOT_DEVICE* pCoffeePot);
void Control_Both_Temp_And_Water(int water_level, int temperature ,  COFFEEPOT_DEVICE* pCoffeePot);
extern "C" void Demonstrate_LEDControl_ASM(COFFEEPOT_DEVICE* pCoffeePot, unsigned short int LED_BIT_PATTERN);
void My_TIC_CoffeePot(COFFEEPOT_DEVICE* p);
#include "Lab1_Files/BF609_LAB1_Core0.h"
#include "CORETIMER LIBRARY/CoreTimer_Code.h"
#include "CORETIMER LIBRARY/CoreTimer_InterruptCode.h"

#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Input_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Output_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/FrontPanel_LED_Switches.h"

void switch5PressedAndReleased();

#endif /* MYCOFFEEPOTFUNCTIONS_H_ */
