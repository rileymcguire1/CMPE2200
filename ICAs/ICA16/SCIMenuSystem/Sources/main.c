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
#include <stdlib.h>
#include <string.h>
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
//#include "A2D_Lib_C.h"
#include "SCI_Lib_C.h"


/********************************************************************
*		Prototypes
********************************************************************/


/********************************************************************
*		Variables
********************************************************************/

 unsigned int Timer = 0;
 unsigned char Output = 0;
 char ClearAndHome[] = "\x1B[2J\x1B[H";
 char RecvdString[2] = "";
 char enable = 0;
 char string[20];

 

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
  lcdInit();  
 


/********************************************************************
*		Main Program Code
********************************************************************/
	
	//set up menu
	Tx_String(ClearAndHome);
	Tx_String("\x1B[?25l");
	Tx_String("\x1B[1;22HCounter Menu Choices");
	Tx_String("\x1B[4;22H1  -  Start the Count");
	Tx_String("\x1B[6;22H2  -  Stop the Count");
	Tx_String("\x1B[8;22H3  -  Clear the Count");
	Tx_String("\x1B[10;22H4  -  Exit Program");
	Tx_String("\x1B[43;50HCurrent Count: ");
	
	
	for (;;)		//endless program loop
	{
	  Delay_C(1);
    
    Timer++;  
    
	  
    
    //get user input
    if(Key_hit()) {
    
    switch(Rx_Byte()){
      case '1':
        enable = 1;
        break;
      case '2':
        enable = 0;
        break;
      case '3':
        Output = 0;
        enable = 0;
        break;
      case '4':
        Tx_String(ClearAndHome);
        while(1);
        break;
    }
    }
    //increment counter on 2Hz
    if(Timer == 500){
      Timer = 0;
         
      //display counter
      Tx_String("\x1B[43;66H");
      sprintf(string,"%02X",Output);
      Tx_String(string);
      if(enable){
      Output++;
      }
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
