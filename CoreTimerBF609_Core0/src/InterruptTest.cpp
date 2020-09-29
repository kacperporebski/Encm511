/*
 * InterruptTest.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: kpore
 */


#define EMBEDDEDUNIT_LITE
#include <EmbeddedUnit2017/EmbeddedUnit2017.h>
#include "../LinksToFiles/CoreTimer_Code.h"
#include "../LinksToFiles/CoreTimer_InterruptCode.h"
#include <sys/exception.h>
#include <blackfin.h>

TEST_CONTROL(InterruptTest_cpp)


#pragma interrupt;
void My_ISR();

extern volatile int messageCount;
TEST(interrupt_test){

	register_handler(ik_timer, My_ISR);

	Start_CoreTimer_Interrupt();
	messageCount = 0;
	while(messageCount < 8){
		CoreTimer_SWI();
	printf("Count %d \n", messageCount);
	}
	Stop_CoreTimer_Interrupt();




}



extern volatile int messageCount;
TEST(real_interrupt_teast){
#define PERIOD 4500

	Init_CoreTimer(PERIOD, PERIOD);

	register_handler(ik_timer, My_ISR);
	messageCount=0;
	Start_CoreTimer();
	Start_CoreTimer_Interrupt();
	while(messageCount<8)
		printf("Count %d \n", messageCount);
	Stop_CoreTimer_Interrupt();
	Stop_CoreTimer();


}


TEST_FILE_RUN_NOTIFICATION(Interrupt_cpp);
