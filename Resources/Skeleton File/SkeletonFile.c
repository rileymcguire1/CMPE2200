/**************************************************************************
*HC12 Program:	YourProg - MiniExplanation
*Processor:		MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		Jan 00, 2018
*Details:   
**************************************************************************/

#include <hidef.h>         	// common defines and macros
//#include <stdio.h>		    // ANSI C Standard Input/Output functions
//#include <math.h>			      // ANSI C Mathematical functions

#include "derivative.h"    	// derivative-specific definitions

/********************************************************************
*		Library includes - your libraries' header files
********************************************************************/
//#include "IIC0_Lib.h"
//#include "LCD_4Line_C.h" 
//#include "Misc_Lib.h"
//#include "LEDS_7Seg_C.h"
//#include "LEDS_7Seg_C.h"

#include "Delay_C.h"
#include "RYG_LEDs.h"



/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

 //unsigned char Pos;

/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{
	_DISABLE_COP();

/********************************************************************
*		Initializations
********************************************************************/
 
  led_sw_init();
  
 


/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
                                             
   Red_On();
   Delay_C (25);
   
   Red_Off();
   Delay_C (500); 
    

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
