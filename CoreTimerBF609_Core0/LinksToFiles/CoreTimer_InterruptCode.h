/*
 * CoreTimer_InterruptCode.h
 *
 *  Created on: Nov 23, 2019
 *      Author: kpore
 */

#ifndef CORETIMER_LIBRARY_CORETIMER_INTERRUPTCODE_H_
#define CORETIMER_LIBRARY_CORETIMER_INTERRUPTCODE_H_

void Start_CoreTimer_Interrupt();
void Stop_CoreTimer_Interrupt();

extern "C" void Raise_ILAT_BIT6_ASM(void);

void CoreTimer_SWI(void);



#endif /* CORETIMER_LIBRARY_CORETIMER_INTERRUPTCODE_H_ */
