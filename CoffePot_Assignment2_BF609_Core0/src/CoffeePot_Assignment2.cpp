/*****************************************************************************
 * CoffeePot_Assignment2.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include "adi_initialize.h"
#include "CoffeePot_Assignment2.h"


/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

int main(int argc, char *argv[])
{
	adi_initComponents();
	
	Start_Assignment2();

	return 0;
}

