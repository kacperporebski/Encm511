#define EMBEDDEDUNIT_LITE
#include <EmbeddedUnit2017/EmbeddedUnit2017.h>
#include "../LinksToFiles/CoreTimer_Code.h"
//#include "CoreTimerTests_cpp.h"


TEST_CONTROL(CoreTimerTests_cpp);

#if 1
void UpdateEunitGui(void);
TEST(CoreTimerTests_cpp_GUIUpdate) {
	UpdateEunitGui();  // Conditionally compile this line (use #if 0) to stop an GUI update based on last completed test
}
#endif


unsigned short int TestBitwiseAND(unsigned short int bitPattern, unsigned short int bitMask);
unsigned short int TestBitwiseOR(unsigned short int bitPattern, unsigned short int bitMask);

#if 0

TEST(Check_Main_CoreTimer)
{
	bool result = CoreTimer_My_Main();
	CHECK(result);
}

TEST(Check_Core_Timer_Done)
{
	Init_CoreTimer();

	bool timerDone = Done_CoreTimer();
	CHECK(timerDone == false);

	Start_CoreTimer();
	while (!(Read_CoreTimerRegister(REG_CONTROL) & DONE_BIT))
	{
		//do nothing
	}

	timerDone = Done_CoreTimer();
	CHECK(timerDone == true);

	timerDone = Done_CoreTimer();
	CHECK(timerDone == false);
}

TEST(Start_Stop_Core_Timer)
{
	Init_CoreTimer();

	unsigned long int firstCoreTimerValue = Read_CoreTimerRegister(REG_COUNTER);
	Start_CoreTimer();
	unsigned long int secondCoreTimerValue = Read_CoreTimerRegister(REG_COUNTER);

	CHECK(firstCoreTimerValue > secondCoreTimerValue);

	unsigned long int thirdCoreTimerValue = Read_CoreTimerRegister(REG_COUNTER);
	CHECK(secondCoreTimerValue > thirdCoreTimerValue);

	Stop_CoreTimer();
	unsigned long int fourthCoreTimerValue = Read_CoreTimerRegister(REG_COUNTER);
	unsigned long int fifthCoreTimerValue = Read_CoreTimerRegister(REG_COUNTER);

	CHECK(fourthCoreTimerValue == fifthCoreTimerValue);
	CHECK(fifthCoreTimerValue == fourthCoreTimerValue);
}

TEST(Test_Init_CoreTimer)
{
	Write_CoreTimerRegisterValue(REG_COUNTER, 0);
	unsigned long int regCountValue1 = Read_CoreTimerRegister(REG_COUNTER);
	CHECK(regCountValue1 == 0);

	Write_CoreTimerRegisterValue(REG_PERIOD, 0);
	unsigned long int regPeriodValue1 = Read_CoreTimerRegister(REG_PERIOD);
	CHECK(regPeriodValue1 == 0);

	Write_CoreTimerRegisterValue(REG_TSCALE, 0);
	unsigned long int regTScaleValue1 = Read_CoreTimerRegister(REG_TSCALE);
	CHECK(regTScaleValue1 == 0);

	Write_CoreTimerRegisterValue(REG_CONTROL, 0);
	unsigned long int regControlValue1 = Read_CoreTimerRegister(REG_CONTROL);
	CHECK(regControlValue1 == 0);

	Init_CoreTimer();

	unsigned long int regCountValue2 = Read_CoreTimerRegister(REG_COUNTER);
	CHECK(Planned_CoreTimerRegisterValue(REG_COUNTER) == regCountValue2);
	CHECK_EQUAL(Planned_CoreTimerRegisterValue(REG_COUNTER), regCountValue2);

	unsigned long int regPeriodValue2 = Read_CoreTimerRegister(REG_PERIOD);
	CHECK(Planned_CoreTimerRegisterValue(REG_PERIOD) == regPeriodValue2);

	unsigned long int regTScaleValue2 = Read_CoreTimerRegister(REG_TSCALE);
	CHECK(Planned_CoreTimerRegisterValue(REG_TSCALE) == regTScaleValue2);

	unsigned long int regControlValue2 = Read_CoreTimerRegister(REG_CONTROL);
	CHECK(Planned_CoreTimerRegisterValue(REG_CONTROL) == regControlValue2);
	CHECK_EQUAL(Planned_CoreTimerRegisterValue(REG_CONTROL), regControlValue2);
}
#endif


#if 0
#define ONE_SECOND 480000000

TEST(ASSIGNMENT2REQ3WAIT){

    Init_CoreTimer(2*ONE_SECOND, 2*ONE_SECOND);

	unsigned long int regCountValue = Read_CoreTimerRegister(REG_COUNTER);
	CHECK_EQUAL(2*ONE_SECOND, regCountValue);

	unsigned long int regPeriodValue = Read_CoreTimerRegister(REG_PERIOD);
	CHECK_EQUAL(2*ONE_SECOND, regPeriodValue);

	unsigned long int regTScaleValue = Read_CoreTimerRegister(REG_TSCALE);
	CHECK_EQUAL(0, regTScaleValue);

	unsigned long int regControlValue = Read_CoreTimerRegister(REG_CONTROL);
	CHECK_EQUAL( (AUTORELOAD_BIT | POWER_ON_BIT ), regControlValue);


	unsigned long long int cycles [10];
	for(int i = 0; i< 10; i++){
		if(i==0)
		Start_CoreTimer();
	    cycles[i]= ReadProcessorCyclesASM();
		TimedWaitOnCoreTimer();
	}

	unsigned long long int difference[9];
	for(int i=0; i<sizeof(cycles)/sizeof(unsigned long long int); i++){
		difference[i]=cycles[i+1]-cycles[i];
	}

#define EXPECTED_DIFFERENCE (ONE_SECOND*2)

	for(int i=1; i<sizeof(difference)/sizeof(unsigned long long int); i++){
		CHECK(abs((long long int)(10000 - (difference[i]*10000/EXPECTED_DIFFERENCE))) < 100 );
	}

	Stop_CoreTimer();


}


TEST(ASSIGNMENT2REQ3POLL){

    Init_CoreTimer(2*ONE_SECOND, 2*ONE_SECOND);

	unsigned long int regCountValue = Read_CoreTimerRegister(REG_COUNTER);
	CHECK_EQUAL(2*ONE_SECOND, regCountValue);

	unsigned long int regPeriodValue = Read_CoreTimerRegister(REG_PERIOD);
	CHECK_EQUAL(2*ONE_SECOND, regPeriodValue);

	unsigned long int regTScaleValue = Read_CoreTimerRegister(REG_TSCALE);
	CHECK_EQUAL(0, regTScaleValue);

	unsigned long int regControlValue = Read_CoreTimerRegister(REG_CONTROL);
	CHECK_EQUAL( (AUTORELOAD_BIT | POWER_ON_BIT ), regControlValue);


	unsigned long long int cycles [10];
	bool firstTime = true;
	int continued = 0;
	for(int i = 0; i< 10; i++){
		if(firstTime){
			Start_CoreTimer();
			firstTime = false;
		}
		if(Done_CoreTimer())
			cycles[i]= ReadProcessorCyclesASM();
		else
			i--;
		if(continued >= 500)
			break;
		continued++;
	}

	unsigned long long int difference[9];
	for(int i=0; i<sizeof(cycles)/sizeof(unsigned long long int); i++){
		difference[i]=cycles[i+1]-cycles[i];
	}

#define EXPECTED_DIFFERENCE (ONE_SECOND*2)

	for(int i=1; i<sizeof(difference)/sizeof(unsigned long long int); i++){
		CHECK(abs((long long int)(10000 - (difference[i]*10000/EXPECTED_DIFFERENCE))) < 100 );
	}

	Stop_CoreTimer();

}

TEST(CHECK_BUG){

#define TEST_VALUE1 3905283346
#define TEST_VALUE2 1204950346

	 Init_CoreTimer(2*ONE_SECOND, 2*ONE_SECOND);
	 Write_CoreTimerRegisterValue(REG_PERIOD, TEST_VALUE1);
	 unsigned long int regCountValue = Read_CoreTimerRegister(REG_COUNTER);
	 CHECK(regCountValue!=TEST_VALUE1);

	 Write_CoreTimerRegisterValue(REG_COUNTER, TEST_VALUE2);
	 unsigned long int regPeriodValue = Read_CoreTimerRegister(REG_PERIOD);
	 CHECK(regPeriodValue!=TEST_VALUE2);


}

#endif



TEST_FILE_RUN_NOTIFICATION(CoreTimerTests_cpp);

