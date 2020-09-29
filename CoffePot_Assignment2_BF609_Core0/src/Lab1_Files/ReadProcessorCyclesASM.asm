/*
 * ReadProcessorCyclesASM.asm
 *
 *  Created on: Sep 26, 2019
 *      Author: kpore
 */

 //ASM STUB
 
 .section L1_data;  //tells LINKER where to put the code. 
 //put PRIVATE data variables used by this ASM function here
 
 .var _examplePrivateASMArray[2] = { 0, 1};
 
 .section program; //tells LINKER where to put ASM
 .global _ReadProcessorCyclesASM;
 
 #define returnValue_R0 R0		//self documented name for register
 #define returnValue_R1 R1
 #define GARBAGE_VALUE 0x0042
 
 _ReadProcessorCyclesASM:		//unsigned long int ReadProcessorCyclesASM(void)
 
 	LINK 20;				//SAFETY CODE
 #if 0	
 	returnValue_R0 = GARBAGE_VALUE;		//return garbage
 #endif 
 
 	returnValue_R0 = CYCLES;		//32bit ot 32 bit register to register
 	returnValue_R1 = CYCLES2;
 	UNLINK;
 	
 _ReadProcessorCyclesASM.END:
 	RTS;
 	
 