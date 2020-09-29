/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: kpore 
* Date: Thu 2019/11/28 at 04:49:36 PM 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include "Lab4_UTTcos_Core0_uTTCOSg2017_main.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_SPI_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/GP_Timer_Library.h"
#include "adi_initialize.h"


// TODO -- Update this code to use CORETIMER interrupts to allow slow uTTCOS in BF533 simulator
// TODO Just these values so that 100 TICS tacks about 1 second
#if defined(__ADSPBF609__)
#define  TIC_CONTROL_VALUE ((unsigned long int) 4800000)		// BF609 EMULATOR
#define TICS_PER_SECOND 	100
#define ONE_SECOND 			TICS_PER_SECOND		// If TICS_CONTROL_VALUE Adjusted correctly
#define RUN_ONCE			0
#define NO_DELAY			0
#else
#error "Unknown ADSP or ARM processor"
#endif

void main(void)
{
	// Make maxNumberThreads at least 5 larger than the 
	//            number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 4;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  
	adi_initComponents();
	Task_Init_LCD_Screen();
	My_Init_LEDInterfaceFRONTPANEL();
	Init_GP_Timer(3);
	Start_GP_Timer(3);

	Custom_uTTCOS_OS_Init(TIC_CONTROL_VALUE);  // Need to update to handle coretimer interrupts

	// TODO -- Remove this TODO statement and next line when demo is finished and you start your Lab 2
	Set_Up_NOT_START_RemoveMeSoonTasks( );

#warning "You will need to activate the next line to start the uTTCOS Clock scheduler
	uTTCOSg_Start_CoreTimer_Scheduler(maxNumberThreads);   //  Start the scheduler timer

	// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks
	while (1) {

		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		// uTTCOSg_GoToSleep( );                // Need to update to handle coretimer interrupts
		Idle_WaitForInterrupts_ASM( );

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOSg_DispatchThreads( );
	}
}

#define E_BIT_HIGH 0x100
#define E_BIT_LO	0
void Task_Init_LCD_Screen()
{

	REB_Write_SPI(0);

	unsigned long int array_MessageInitLCD []= {
					E_BIT_HIGH | 0x30,
					E_BIT_LO | 0x30,
					E_BIT_HIGH | 0x30,
					E_BIT_LO | 0x30,
					E_BIT_HIGH | 0x3c,
					E_BIT_LO | 0x3c,
					E_BIT_HIGH | 0x0f,
					E_BIT_LO | 0x0f,
					E_BIT_HIGH | 0x01,
					E_BIT_LO | 0x01

	};


	Init_REB_SPI();
	SetBoardLED_SPI_ConfigSoftSwitches();
	Start_REB_SPI();


	for(int i = 0 ; i < 9 ; i++)
	{
			REB_Write_SPI(array_MessageInitLCD[i]);
		printf("0x%x\n", array_MessageInitLCD[i]);
	}


}






// Set up uTTCOS path to function that this task needs to interact with
volatile char ID_Task_WriteLCDMessage;
volatile char ID_Task_Temp;
void Set_Up_NOT_START_RemoveMeSoonTasks(void) {
	//ID_Task_RemoveMeSoon_Print1 = uTTCOSg_AddThread(Task_RemoveMeSoon_Print1, NO_DELAY, 0.75 * ONE_SECOND);
	ID_Task_WriteLCDMessage = uTTCOSg_AddThread(Task_WriteLCDMessage, NO_DELAY , 7*ONE_SECOND) ;
	ID_Task_Temp = uTTCOSg_AddThread(Task_Temp, 6.5*ONE_SECOND, 6.5*ONE_SECOND);
}



#define RS_HI 0x400
#define RS_LO 0
extern volatile char ID_WriteLCDMessage;    // Set up uTTCOS path to function that this task needs to interact with
void Task_WriteLCDMessage(void)
{
			ClearScreen();


	unsigned long int messageArray[] =
	{
			RS_HI |	E_BIT_HIGH | 0x35,
			RS_HI |	E_BIT_LO | 0x35,
			RS_HI |	E_BIT_HIGH | 0x35,

			RS_HI |E_BIT_HIGH | 0x31,
			RS_HI |	E_BIT_LO | 0x31 ,
			RS_HI |E_BIT_HIGH | 0x31,

			RS_HI |E_BIT_HIGH | 0x31,
			RS_HI |	E_BIT_LO | 0x31 ,
			RS_HI |E_BIT_HIGH | 0x31,

			RS_HI |	E_BIT_HIGH | 0x20,
			RS_HI |	E_BIT_LO | 0x20 ,
			RS_HI |	E_BIT_HIGH | 0x20,

			RS_HI |	E_BIT_HIGH | 0x52 ,
			RS_HI | E_BIT_LO | 0x52,
			RS_HI |	E_BIT_HIGH | 0x52 ,

			RS_HI |	E_BIT_HIGH | 0x55 ,
			RS_HI |	E_BIT_LO | 0x55,
			RS_HI |	E_BIT_HIGH | 0x55 ,

			RS_HI |	E_BIT_HIGH | 0x4C ,
			RS_HI |	E_BIT_LO | 0x4C,
			RS_HI |	E_BIT_HIGH | 0x4C ,

			RS_HI |	E_BIT_HIGH | 0x53 ,
			RS_HI |	E_BIT_LO | 0x53,
			RS_HI |	E_BIT_HIGH | 0x53 ,

			RS_HI |	E_BIT_HIGH | 0x20,
			RS_HI |	E_BIT_LO | 0x20,
			RS_HI |	E_BIT_HIGH | 0x20
	};


	for(int i = 0; i< 26; i++){
		REB_Write_SPI(messageArray[i]);
		printf("0x%x\n", messageArray[i]);
	}

}

//void Task_Write_

#define CLEAR 0x01

void ClearScreen(){

	unsigned long int Clear[] = {
			E_BIT_HIGH | CLEAR ,
			E_BIT_LO | CLEAR ,
			E_BIT_HIGH | CLEAR
	};

	for(int i = 0 ; i < 2 ; i++){
	while(! REB_SPI_Ready())
			{
					//donoting
			}
			REB_Write_SPI(Clear[i]);

	}

}



extern volatile char ID_Task_Temp;
void Task_Temp()
{

	ClearScreen();
	unsigned long int temp;
	unsigned long int T1;
	unsigned long int T2;
		T2 = ReadWidth_GP_Timer(3);
		T1 = ReadPeriod_GP_Timer(3) - T2;
		temp = 235 - (400*T1) / T2;
		My_WriteLEDFP(temp);
	 char temperature [50];
		unsigned long int control [] ={
				RS_HI |	E_BIT_HIGH,
				RS_HI |	E_BIT_LO,
				RS_HI |	E_BIT_HIGH
		};

		snprintf(temperature, 3, "%lu", temp);

		for(int k = 0, j=0; k<2; j++){
		REB_Write_SPI(temperature[k] | control[j]);
		printf("0x%x\n", temperature[k] | control[j]);
		if(j==2){
			j=0;
			k++;
		}
		}

}

