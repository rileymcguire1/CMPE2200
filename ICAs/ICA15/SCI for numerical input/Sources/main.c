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

void GetNumber(void);

/********************************************************************
*		Variables
********************************************************************/

 unsigned char Key_In = 0;
 char output[20] = "";
 char input[2] = "";
 char RxData;
 char ClearAndHome[] = "\x1B[2J\x1B[H";
 float n1;
 float n2;
 float result;
 

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
	
	for (;;)		//endless program loop
	{
    //set up LCD display
    Tx_String(ClearAndHome); 
    lcdClear();
    n1 = 0;
    n2 = 0;
    output[0] = 0;
    lcdLabels("THE MULTIPLIER","N1:", "N2:","N1 X N2=");
    
    //get first decimal and output to lcd
    Tx_String("Enter the first decimal number: ");
    GetNumber();
    n1 = atof(output);
    Set_R_C(1,5);
    lcdString(output);
    output[0] = 0;
    //get second decimal and output to lcd
    Tx_String("Enter the second decimal number: ");
    GetNumber();
    n2 = atof(output);
    Set_R_C(2,5);
    lcdString(output);
    output[0] = 0;
    
    //calculate result
    result = n1*n2;
    Set_R_C(3,9);
    (void)sprintf(output,"%.03f",result);
    lcdString(output);
    
    //hold till enter is pressed
    Tx_String("Press Enter to Reset");
    while(Rx_Byte() !=0x0d);
	}
}
/**************************************************************************
*		Function:  Note that functions reside outside of Main - so if you call
*              these from within Main, you must include its prototype     
*              above
***************************************************************************/

void GetNumber(void){
    do{
      RxData = Rx_Byte();
      Tx_Byte(RxData);
      input[0] = RxData;
      (void)strcat(output,input);
    }while(RxData != 0x0d);
    output[strlen(output)-1] = 0;
    Tx_String(ClearAndHome);
}
  


/********************************************************************
*		Interrupt Service Routines
********************************************************************/



/*******************************************************************/
