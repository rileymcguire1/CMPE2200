/**************************************************************************
*HC12 Program:	Lab exam 1
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		Feb 13, 2018
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
#include "LED_7Seg_C.h"
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
 unsigned char top = 0;
 unsigned char bottom = 0;

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
  LEDS_7_Init();
  Sw_Init();
 


/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
	  top = 0;
    
    if((Get_Switches() & 0x10)==0x10){
      top++;
    }
    if((Get_Switches() & 0x01)==0x01){
      top++;
    }
    if((Get_Switches() & 0x02)==0x02){
      top++;
    }
    if((Get_Switches() & 0x04)==0x04){
      top++;
    }
    if((Get_Switches()& 0x08)==0x08){
      top++;
    }
    
    bottom = 5-top;
    Top_8Out(top);                                      
    Bot_8Out(bottom);
    

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
