/**************************************************************************
*HC12 Program:	YourProg - MiniExplanation
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		Jan 00, 2018
*Details:   
**************************************************************************/

#include <hidef.h>         	// common defines and macros
#include <stdio.h>		    // ANSI C Standard Input/Output functions
#include <math.h>			      // ANSI C Mathematical functions
#include <string.h>
#include <stdlib.h>
#include "derivative.h"    	// derivative-specific definitions

/********************************************************************
*		Library includes - your libraries' header files
********************************************************************/
//#include "IIC0_Lib.h"
#include "LCD_4Line_C.h" 
//#include "Misc_Lib.h"
//#include "LED_7Seg_C.h"
//#include "Delay_C.h"
//#include "RYG_LEDs.h"
//#include "Switches_C.h"
#include "A2D_Lib_C.h"
#include "SCI_Lib_C.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/
  unsigned char Key_In = 0;
  char output[20] = "";
  char input[2] = "";
  char RxData;
  unsigned int result; 
  float stepSize = 0.005;
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
 
  Init19200();
  ATD0_Init();
  lcdInit();
/********************************************************************
*		Main Program Code
********************************************************************/
	
	//set up lcd display
	output[0] = 0;
  
	for (;;)		//endless program loop
	{ 
	  //set up headers
	  Tx_String("\x1B[2J\x1B[H");
	  Tx_String("\x1B[?25l");
	  Tx_String("\x1B[1;1HA/D Sample (HEX)  Sampled Voltage");
	  countSample = 2;                                
    while(countSample<24){
      //get A/D sample
      result = ATD0_Sample7();
      //display sample to screen
      output[0] = 0;
      strcat(output, "\x1B[");
      sprintf(s,"%i",countSample);  
      strcat(output, s);
      strcat(output, ";3H");
      sprintf(s,"%03X",result);
      strcat(output, s);
      Tx_String(output);
      //display voltage to screen
      output[0] = 0;
      strcat(output, "\x1B[");
      sprintf(s,"%i",countSample);  
      strcat(output, s);
      strcat(output, ";21H");
      sprintf(s,"%5.3f",result*stepSize);
      strcat(output, s);
      Tx_String(output);
      
      //increment sample line count
	    countSample++;
      Delay_C(1000);
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
