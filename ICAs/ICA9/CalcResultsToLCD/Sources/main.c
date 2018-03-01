/**************************************************************************
*HC12 Program:ICA9 - Sent Calculated Results to LCD
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:	  Mar 01, 2018
*Details:   
**************************************************************************/

#include <hidef.h>         	// common defines and macros
#include <stdio.h>		    // ANSI C Standard Input/Output functions
#include <math.h>			      // ANSI C Mathematical functions

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


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

 int diameter = 17;
 double CirArea;
 double SphArea;
 double volume;
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
  
 


/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
    CirArea = pow((diameter / 2.0),2.0) * _M_PI;
    SphArea = 4*CirArea;
    volume = (4.0/3.0)*_M_PI*pow((diameter / 2.0),3);                                         
    
    lcdLabels("INPUT DIAMETER:","CIRCLE AREA:","SPHERE AREA:","SPHERE VOL:");
    
    Set_R_C(0,16);
    sprintf(s,"%d",diameter);
    lcdString(s);
    
    Set_R_C(1,13);
    sprintf(s,"%6.2f",CirArea);
    lcdString(s);
    
    Set_R_C(2,13);
    sprintf(s,"%6.1f",SphArea);
    lcdString(s);
    
    Set_R_C(3,13);
    sprintf(s,"%6.1f",volume);
    lcdString(s);

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
