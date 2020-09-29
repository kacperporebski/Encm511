/*
 * DemonstateLED_ASM.asm
 *
 *  Created on: Oct 30, 2019
 *      Author: kpore
 */
#include <blackfin.h>

 .section L1_data;
 .section program;
 
 .global _Demonstrate_LEDControl_ASM;		//extern "C" void Demonstrate_LEDControl_ASM
 
 _Demonstrate_LEDControl_ASM:
 
 #define baseAddress_R0 R0
 #define returnValue_R0 R0

 
 LINK 20;
 
 #define LED_BIT_R1 R1
 #define currentControlRegister_R2 R2
 #define temp_R3 R3
 #define pCoffeePot_P0 P0
 
 pCoffeePot_P0 = baseAddress_R0;				//make pointer point to the coffeepot
 currentControlRegister_R2 = W[pCoffeePot_P0] (Z);	
 
 //now R2 is the bits in my control register
 temp_R3 = currentControlRegister_R2 & LED_BIT_R1;
 CC = temp_R3 == LED_BIT_R1;
 
 if CC JUMP TURN_OFF;
 
 TURN_ON:
 //turn on
 temp_R3 = currentControlRegister_R2 | LED_BIT_R1;
 [pCoffeePot_P0] = temp_R3;
 JUMP END;
 
 TURN_OFF:
 	//turn off
 	 LED_BIT_R1 = ~LED_BIT_R1;
 	 temp_R3 = currentControlRegister_R2 & LED_BIT_R1;
 	 [pCoffeePot_P0] = temp_R3;
 	
 END:

 	.extern __Z28FastForward_OneSimulationTICP16COFFEEPOT_DEVICE CALL __Z28FastForward_OneSimulationTICP16COFFEEPOT_DEVICE;

 
 
 UNLINK;
  _Demonstrate_LEDControl_ASM.END:
  RTS;
 
 