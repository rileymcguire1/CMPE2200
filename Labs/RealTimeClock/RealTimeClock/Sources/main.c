/**************************************************************************
*HC12 Program:	Real Time Clock - using the Real Time clock
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		April 17, 2018
*Details: Reading the RTC and printing to the LCD display  
**************************************************************************/

#include <hidef.h>         	// common defines and macros
#include <stdio.h>		    // ANSI C Standard Input/Output functions
//#include <math.h>			      // ANSI C Mathematical functions

#include "derivative.h"    	// derivative-specific definitions

/********************************************************************
*		Library includes - your libraries' header files
********************************************************************/
#include "IIC0_Lib.h"
#include "LCD_4Line_C.h" 
//#include "Misc_Lib.h"
//#include "LED_7Seg_C.h"
//#include "Delay_C.h"
//#include "RYG_LEDs.h"
//#include "Switches_C.h"
//#include "A2D_Lib_C.h"
//#include "SCI_Lib_C.h"
//#include "Timer.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/
 unsigned char Sec;
 unsigned char Min;
 unsigned char Hr;
 unsigned char Date;
 unsigned char Mth;
 unsigned char Year;
 
 unsigned char HasHT;
 char output[20];


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
 IIC0_Init();
 
 HasHT = IIC0_Read(0xD0,0x0C);
 IIC0_Write(0xD0, 0x0C, (HasHT&0b10111111));
Sec=IIC0_Read(0xD0,0x01);
if((Sec&0x80)!=0) IIC0_Write(0xD0,0x01, (Sec&0x7F));

//set time
/*
IIC0_Write(0xD0,1,0x00);  //secs
IIC0_Write(0xD0,2,0x47);  //mins
IIC0_Write(0xD0,3,0x11);  //hours
IIC0_Write(0xD0,4,0x02);  //day of week
IIC0_Write(0xD0,5,0x17);  //day of month
IIC0_Write(0xD0,6,0x04);  //month
IIC0_Write(0xD0,7,0x18);  //year
*/


 lcdLabels("Time:   :  :","Date:   /  /","","");
/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
    Sec = IIC0_Read(0xD0, 0x01)&0x7F;
    Min = IIC0_Read(0xD0, 0x02)&0x7F;
    Hr = IIC0_Read(0xD0, 0x03)&0x3F;
    Date = IIC0_Read(0xD0, 0x05)&0x3F;
    Mth = IIC0_Read(0xD0, 0x06)&0x1F;                                         
    Year = IIC0_Read(0xD0, 0x07);
    
    //display to LCD
    //seconds
    Set_R_C(0,12);
    (void)sprintf(output, "%02X", Sec);
    lcdString(output);
    
    //minutes
    Set_R_C(0,9);
    (void)sprintf(output, "%02X", Min);
    lcdString(output);
    
    //hours
    Set_R_C(0,6);
    (void)sprintf(output, "%02X", Hr);
    lcdString(output);
    
    //day
    Set_R_C(1,6);
    (void)sprintf(output, "%02X", Date);
    lcdString(output);
    
    //month
    Set_R_C(1,9);
    (void)sprintf(output, "%02X", Mth);
    lcdString(output);
    
    //year
    Set_R_C(1,12);
    (void)sprintf(output, "%02X", Year);
    lcdString(output);             
    
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



/**************************************************************/