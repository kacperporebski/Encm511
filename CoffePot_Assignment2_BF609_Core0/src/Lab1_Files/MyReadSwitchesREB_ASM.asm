/*
 * Read_FIO_FLAG_ASM.asm
 *
 *  Created on: Oct 9, 2019
 *      Author: kpore
 */

 //ASM STUB
 
 #include <blackfin.h>
 .section L1_data;  //tells LINKER where to put the code. 
 //put PRIVATE data variables used by this ASM function here
 .section program; //tells LINKER where to put ASM
 .global _MyReadSwitchesREB_ASM;
 
 #define portPattern_R0 R0
 #define portPointer_P0 P0
 #define BIT8TO11_PATTERN 0xF00
 #define temp_R1 R1	
 
 _MyReadSwitchesREB_ASM:		//unsigned long int ReadProcessorCyclesASM(void)
 
 	LINK 20;			
  P0.H= hi(REG_PORTF_DATA);	  P0.L = lo(REG_PORTF_DATA);		//Set pointer
 
 portPattern_R0 = W[portPointer_P0] (Z);			//Read 16 bit value from 16bit port, exten with zeros to become 32bits	
 temp_R1 = BIT8TO11_PATTERN;							//bitwise must be done register to register
 portPattern_R0 = portPattern_R0 & temp_R1;			// return just value in bits 8-11

 	UNLINK;
 	
 _MyReadSwitchesREB_ASM.END:
 	RTS;
 	
 
 