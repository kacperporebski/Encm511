/*
 * CoreTimer_Code.h
 *
 *  Created on: Nov 18, 2019
 *      Author: kpore
 */

#ifndef CORETIMER_CODE_H_
#define CORETIMER_CODE_H_

#include <stdio.h>
extern "C" unsigned long long int ReadProcessorCyclesASM(void);
void Init_CoreTimer(unsigned long int period, unsigned long int count);
void Start_CoreTimer(void);
void Stop_CoreTimer(void);
bool Done_CoreTimer(void);
void TimedWaitOnCoreTimer();
bool CoreTimer_My_Main(void);

enum CORETIMER_REG {DONT_KNOW , REG_COUNTER, REG_PERIOD, REG_TSCALE, REG_CONTROL };

unsigned long int Planned_CoreTimerRegisterValue(CORETIMER_REG regName);
unsigned long int Read_CoreTimerRegister(CORETIMER_REG regName);

void Write_CoreTimerRegisterValue(CORETIMER_REG regName , unsigned long int newValue);

#define DONE_BIT 0x8
#define AUTORELOAD_BIT 0x4
#define ENABLE_BIT 0x2
#define POWER_ON_BIT 0x1




#endif /* CORETIMER_CODE_H_ */
