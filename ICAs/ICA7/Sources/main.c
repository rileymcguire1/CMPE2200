/**************************************************************************
*HC12 Program:	YourProg - MiniExplanation
*Processor:	MC9S12XDP512
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
#include "LCD_4Line_C.h" 
//#include "Misc_Lib.h"
//#include "LED_7Seg_C.h"
#include "Delay_C.h"
//#include "RYG_LEDs.h"
//#include "Switches_C.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

 char str[22] = "My Cats";
 char name[10] = "Riley";
 char letter = 'A';

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
 


/********************************************************************
*		Main Program Code
********************************************************************/
	
	 /*//Populate the LCD labels
	  lcdLabels("Label 0:","Label 1:","Label 2:","Label 3:"); 
	                                         
    // Set_R_C(row,col)
    Set_R_C(3,10);             
	  lcdString(str);
	  
	  Set_R_C(0,10);
    lcdString(name); */
    
    Set_R_C(2,9);    lcdData(0xF7);
    
    
	for (;;)		//endless program loop
	{
	 /* Set_R_C(1,15);
    lcdData(letter);
    Delay_C(1000);    letter += 0x20;
    Set_R_C(1,15);
    lcdData(letter);
    Delay_C(2000);
    letter -=0x20;
    letter += 0x01;
    if(letter > 'Z') {
      letter = 'A'; }  */
       

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
