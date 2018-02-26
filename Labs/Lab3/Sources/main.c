/**************************************************************************
*HC12 Program:	LAB3 - Counting using Switch Presses
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		Jan 00, 2018
*Details:  Count to the RYG LEDs using switch presses as inputs 
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
#include "Switches_C.h"


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
  Sw_Init();
  
 


/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
	
    if(Get_Switches()==0x18)
    {
      Wait_For_Switches(0x10);
      PT1AD1 += 0x20;
    }
    if(Get_Switches()==0x0C)
    {
      Wait_For_Switches(0x04);
      PT1AD1 -= 0x20;
    }
    if(Get_Switches()==0x01)
    {
      Wait_For_Switches(0x01);
      PT1AD1 = 0x00;
    }

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
