/**************************************************************************
*HC12 Program:	Lab 4 part A - counter on 7Seg LEDs
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		Feb 06, 2018
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
//#include "RYG_LEDs.h"
#include "Switches_C.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

 //unsigned char Pos;
  unsigned int increment = 0;
	unsigned int decrement = 0;
	unsigned char toggle = 1;

/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{
	_DISABLE_COP();

/********************************************************************
*		Initializations
********************************************************************/
 
  Sw_Init();
  LEDS_7_Init();

/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
	  
	  if(toggle)
	  {
	    Top_8Out(increment);
	    Bot_8Out(decrement);  
	  }
	  else
	  {
	    Top_8Out(decrement);
	    Bot_8Out(increment);  
      
	  }
    if(Get_Switches()==0x10)     //up press increments top
      {
        increment++;
        Wait_For_Switches(0x10);
      }
    
      if(Get_Switches()==0x04)    //down press decrements bottom
      {
        decrement--;
        Wait_For_Switches(0x04);
      }
    
      if(Get_Switches()==0x01)
      {
        increment = 0;
        decrement = 0;
      }
      if(Get_Switches()==0x02)    //right press toggles counter positions
      {
        if(toggle){
          
        toggle = 0;
        
        } else{
          toggle = 1;
        }
        Wait_For_Switches(0x02);
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
