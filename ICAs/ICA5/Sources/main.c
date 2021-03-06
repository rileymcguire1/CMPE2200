/**************************************************************************
*HC12 Program:	ICA - 5
*Processor:		MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		  Jan 25, 2018                                       
*Details:   Skeleton File with some additional libraries turning on the 
*           LEDs with some delays in C
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
   
   Yellow_On();
   Delay_C (35);
   
   Yellow_Off();
   Delay_C(500);
   
   Green_On();
   Delay_C(55);
   
   Green_Off();
   Delay_C(500);
    

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
