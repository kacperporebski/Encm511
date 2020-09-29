
 //ASM STUB
 
#include <blackfin.h>
 
 .section L1_data;  //tells LINKER where to put the code. 
 //put PRIVATE data variables used by this ASM function here
 .section program; //tells LINKER where to put ASM
 .global _MyInitREB_ASM;
 
 #define portPointer_P0 P0
 #define temp_R1 R1	
 #define temp_R2 R2
 #define MASK_TO_INPUT_ENABLE_BITS_11_TO_8 0x0F00
 #define MASK_TO_MAKE_15TO12_OUTPUT 0xF000
 #define MASK_TO_MAKE_ACTIVE_HIGH 0xF0FF
 #define MASK_TO_CLEAR_DATA 0x0FFF
_MyInitREB_ASM:		
 	LINK 20;	
 			
P0.H= hi(REG_PORTF_INEN);	  P0.L = lo(REG_PORTF_INEN);		
	temp_R1 = W[portPointer_P0] (Z);			    //Read 16 bit value from 16bit port, exten with zeros to become 32bits
	temp_R2 = MASK_TO_INPUT_ENABLE_BITS_11_TO_8(Z);		// 0000_1111_0000_0000
	temp_R1 = temp_R1 | temp_R2;					// Makes bits 15 to 8 = 1 , everything else unchanged
[P0] = temp_R1;
 
  
P0.H= hi(REG_PORTF_DIR);	  P0.L = lo(REG_PORTF_DIR);
	temp_R1 = W[portPointer_P0] (Z);		 
	temp_R2 = MASK_TO_MAKE_15TO12_OUTPUT(Z);
	temp_R1 = temp_R1 | temp_R2;	
[P0] = temp_R1;
   
 
P0.H= hi(REG_PORTF_POL);	  P0.L = lo(REG_PORTF_POL);
 	temp_R1 = W[portPointer_P0] (Z);				
	temp_R2 = MASK_TO_MAKE_ACTIVE_HIGH(Z);			// 0x0011
	temp_R1 = temp_R1 & temp_R2;					// makes the pins we are using active high, rest unchanged
[P0] = temp_R1;


P0.H= hi(REG_PORTF_DATA);	  P0.L = lo(REG_PORTF_DATA);		//Set pointer to FIO_FLAG memory location
 	temp_R1 = W[portPointer_P0] (Z);			
 	temp_R2 = MASK_TO_CLEAR_DATA;					// 0xFFFF0FFF
	temp_R1 = temp_R1 & temp_R2;				// makes bits 12 to 15 = 0 , everything else unchanged
[P0] = temp_R1;	

 		ssync;					   
 							   				 
UNLINK;
_MyInitREB_ASM.END:
 	RTS;
 	
 
 