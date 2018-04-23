/**************************************************************************
*HC12 Program:	Pulse Accumulator - testing the hardware
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		April 5, 2018
*Details:   
**************************************************************************/

#include <hidef.h>         	// common defines and macros
#include <stdio.h>		    // ANSI C Standard Input/Output functions
//#include <math.h>			      // ANSI C Mathematical functions

#include "derivative.h"    	// derivative-specific definitions

/********************************************************************
*		Library includes - your libraries' header files
********************************************************************/
//#include "IIC0_Lib.h"
#include "LCD_4Line_C.h" 
//#include "Misc_Lib.h"
//#include "LED_7Seg_C.h"
#include "Delay_C.h"
//#include "RYG_LEDs.h"
//#include "Switches_C.h"
//#include "A2D_Lib_C.h"
//#include "SCI_Lib_C.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

unsigned int iCount;
double speed;
char output[20];

/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{
	_DISABLE_COP();

/********************************************************************
*		Initializations
********************************************************************/
 
 lcdInit(); 
 PACTL = 0x40; 
 
 lcdLabels("  WIND SPEED SENSOR","SENSOR FREQ:","WIND SPEED:","");

/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
	  //wait for one second
	  Delay_C(1000);                                             
    
    //get count from accumulator register    
    iCount = PACN32;
    
    //calculate freq and speed
    speed = iCount * 0.1949 + 1.0415;
    //display count and speed to LCD
    Set_R_C(1,14);
    (void)sprintf(output, "%3.0d HZ", iCount);
    lcdString(output);
    
    Set_R_C(2, 14);
    (void)sprintf(output, "%2.0f KPH", speed);
    lcdString(output);
    
    //reset acumulator
    PACN32 = 0;

	}
}
/**************************************************************************
*		Function:  Note that functions reside outside of Main - so if you call
*              these from within Main, you must include its prototype     
*              above
***************************************************************************/



/********************************************************************
*		Interrupt Service Routines
********************************************************************/



/*******************************************************************/
