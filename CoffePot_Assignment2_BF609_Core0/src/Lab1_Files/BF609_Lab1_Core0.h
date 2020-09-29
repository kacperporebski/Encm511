/*****************************************************************************
 * BF609_Lab1_Core0.h
 *****************************************************************************/

#ifndef __BF609_LAB1_CORE0_H__
#define __BF609_LAB1_CORE0_H__

/* Add your custom header content here */

#include<stdio.h>
#include<iostream>
void Start_Lab1();
void Star_Lab0();
void Start();
void My_Init_LEDandSwitchInterfaceREB();
void My_Init_SwitchInterfaceFRONTPANEL();
void My_Init_LEDInterfaceFRONTPANEL();
unsigned char My_ReadSwitchesFP();
unsigned char My_ReadSwitchesREB();
unsigned char My_ReadLEDFP();
unsigned char My_ReadLEDREB();
void My_WriteREB (unsigned char x);
void My_WriteLEDFP (unsigned char x);
void PrintBinaryValue(unsigned char x);
void WaitTillSwitch1PressedAndReleased();
void WaitTillSwitch2PressedAndReleased();
void WaitTillSwitch3PressedAndReleased();
void WaitTillSwitch5PressedAndReleased();
unsigned long long int ReadProcessorCyclesCPP(void);
unsigned short int MyReadSwitchesREB_CPP(void);
void MyWriteLEDREB_CPP(unsigned short int x);
void MyInitREB_CPP(void);
bool Switch4and5pressed();


#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Input_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_GPIO_Output_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/FrontPanel_LED_Switches.h"

#endif /* __BF609_LAB1_CORE0_H__ */
