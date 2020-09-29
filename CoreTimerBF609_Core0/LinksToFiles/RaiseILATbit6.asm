/*
 * RaiseILATbit6.asm
 *
 *  Created on: Nov 23, 2019
 *      Author: kpore
 */

 #define ILAT_BIT6 6
 
 .section program;
 .global _Raise_ILAT_BIT6_ASM;
 _Raise_ILAT_BIT6_ASM:
 nop;
 nop;
 nop;
 raise ILAT_BIT6;
 _Raise_ILAT_BIT6_ASM.END:
 RTS;