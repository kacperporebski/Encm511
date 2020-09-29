
 //ASM STUB
 
 #include <blackfin.h>
 .section L1_data;  //tells LINKER where to put the code. 
 //put PRIVATE data variables used by this ASM function here
 .section program; //tells LINKER where to put ASM
 .global _MyWriteLEDREB_ASM;
 
 #define charToWrite R0
 #define portPointer_P0 P0
 #define MASKBITS12TO9 0x0FFF
 #define temp_R1 R1	
 #define temp_R2 R2
 
 _MyWriteLEDREB_ASM:		//unsigned long int ReadProcessorCyclesASM(void)
 
 	LINK 20;	
 			
  P0.H= hi(REG_PORTF_DATA);	  P0.L = lo(REG_PORTF_DATA);		//Set pointer to FIO_FLAG memory location
 
 temp_R1 = W[portPointer_P0] (Z);			//Read 16 bit value from 16bit port, exten with zeros to become 32bits
 temp_R2 = MASKBITS12TO9;
 temp_R1 = temp_R1 & temp_R2;
 temp_R1 = temp_R1 | charToWrite;
 
 [P0] = temp_R1;
 ssync;
										    //bitwise must be done register to register
 											// return just value in bits 8-11

 	UNLINK;
 	
 _MyWriteLEDREB_ASM.END:
 	RTS;
 	
 
 