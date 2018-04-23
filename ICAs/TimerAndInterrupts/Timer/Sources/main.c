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
//#include <math.h>			      // ANSI C Mathematical functions
#include <string.h>
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
//#include "A2D_Lib_C.h"
//#include "SCI_Lib_C.h"
#include "Timer.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

 unsigned int iTicks = 0;
 unsigned int iSeconds = 50;
 unsigned int iMinutes = 59;
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
 
  lcdInit();
  Timer_Init();
  TC0 = TCNT + 62500; //first interval set for 10ms
	EnableInterrupts;

/********************************************************************
*		Main Program Code
********************************************************************/
	
	
	for (;;)		//endless program loop
	{
     iSeconds++;
     if(iSeconds > 59){
      iMinutes++;
      iSeconds = 0;
      iTicks = 0;
     }
     if(iMinutes>59){
      iMinutes = 0;
     }

     //show time on LCD display
     Set_R_C(0,0);
     sprintf(s, "%02d",iMinutes);
     lcdString(s);
     lcdData(':');
     sprintf(s, "%02d", iSeconds);
     lcdString(s);
     
     asm WAI;
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
 interrupt VectorNumber_Vtimch0 void TimerInterval(void){
  TFLG1 = 0b00000001;
  TC0 += 62500;
 }


/*******************************************************************/
