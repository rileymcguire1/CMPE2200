/**************************************************************************
*HC12 Program:	A/D coupled with transfer function
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		March 12, 2018
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
#include "A2D_Lib_C.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

 unsigned int result;
 float temp;
 float stepSize = 0.005;
 unsigned int countTime = 0;
 unsigned int countSample = 0;
 char s[20];

/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{
	_DISABLE_COP();

/********************************************************************
*		Initializations
********************************************************************/
 
  ATD0_Init();
  lcdInit();
  


/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
	  
	    
	  countSample++;
	  //get converted result from register
    result = ATD0_Sample7();
    //inverse transfer function for temperature
    temp = result*stepSize * 1.564027 + 22;                                         
    
    //set up display 
    lcdLabels("A2D RESULT:","VOLTAGE:","TEMPERATURE:","SAMPLES:");
    
    //display hex results 
    Set_R_C(0,12);
    sprintf(s,"%03X",result);
    lcdString(s); 
    
    //display voltage
    Set_R_C(1,9);
    sprintf(s,"%5.3f V",result*stepSize);
    lcdString(s);
    
    //display temp
    Set_R_C(2,13);
    sprintf(s,"%5.2f C",temp);
    lcdString(s);
    Set_R_C(2,17);
    lcdData(0xDF);
    
    //display sample count
    Set_R_C(3,9);
    sprintf(s, "%d",countSample);
    lcdString(s);
	  
    //delay for one second
    Delay_C(1000);
    

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
