/**************************************************************************
*HC12 Program:	Gas Pump - SCI input and display to LCD
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		April 12, 2018
*Details:   
**************************************************************************/

#include <hidef.h>         	// common defines and macros
#include <stdio.h>		      // ANSI C Standard Input/Output functions
//#include <math.h>			      // ANSI C Mathematical functions
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
#include "Switches_C.h"
//#include "A2D_Lib_C.h"
#include "SCI_Lib_C.h"
//#include "Timer.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

double regular = 0;
double midGrade = 0;
double premium = 0;
double selected = 0;
double liters;
double cost;
char output[20];
char ClearAndHome[] = "\x1B[2J\x1B[H";
char SwitchNotPressed = 1;



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
 lcdInit(); 
 Init19200(); 
 
 Tx_String(ClearAndHome);
 //set prices for gas grades 
 lcdLabels("    THE GAS PUMP","ENTER TODAYS PRICES","","");
 
 //get regular price
    Tx_String("Enter the price for regular: ");
    GetNumber(output);
    regular = atof(output);
    output[0] = 0;
    
 //get MidGrade price
    Tx_String("Enter the price for mid-grade: ");
    GetNumber(output);
    midGrade = atof(output);
    output[0] = 0;
    
  //get premium price
    Tx_String("Enter the price for premium: ");
    GetNumber(output);
    premium = atof(output);
    output[0] = 0;

/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
	  lcdClear();
	  output[0] = 0; 
	  //set labels
    lcdLabels("REGULAR:", "MID-GRADE:","PREMIUM:", "SELECT GRADE:");
    //set regular
    Set_R_C(0,12);
    (void)sprintf(output,"%5.1f",regular);
    lcdString(output); 
    //set mid-grade
    Set_R_C(1,12);
    (void)sprintf(output,"%5.1f",midGrade);
    lcdString(output); 
    //set premium
    Set_R_C(2,12);
    (void)sprintf(output,"%5.1f",premium);
    lcdString(output);               
    
    while(SwitchNotPressed){
      
      //switch input
      switch(Get_Switches()){
        case 0x01:
          selected = midGrade;
          (void)sprintf(output,"MID-GRADE");
          SwitchNotPressed = 0;
          break;
        case 0x04:
          selected = premium;
          (void)sprintf(output,"PREMIUM");
          SwitchNotPressed = 0;
          break;
        case 0x10:
          selected = regular;
          (void)sprintf(output,"REGULAR");
          SwitchNotPressed = 0;
          break;
      }
    }
    SwitchNotPressed = 1;
    
    //display selected grade
    lcdClear();
    lcdLabels("    THE GAS PUMP","","","LITERS?");
    Set_R_C(2,0);
    lcdString(output);
    Set_R_C(2,12);
    (void)sprintf(output,"%5.1f",selected);
    lcdString(output);
    output[0] = 0; 
    
    //get user input for liters
    Tx_String("Enter the amount of liters: ");
    GetNumber(output);
    liters = atof(output);
    output[0] = 0; 
    
    //calculate cost for gas
    cost = liters * selected / 100;
    
    //display cost with price and liters
    lcdClear();
    lcdLabels("    THE GAS PUMP","PRICE:","LITERS:","YOUR COST:");
    
    Set_R_C(1,8);    (void)sprintf(output,"%5.1f",selected);
    lcdString(output);
    
    Set_R_C(2,9);
    (void)sprintf(output,"%6.2f",liters);
    lcdString(output);
    
    Set_R_C(3,12);
    (void)sprintf(output,"%6.2f",cost);
    lcdString(output);
    
    //wait for center switch press
    while(Get_Switches() != 1);
    Wait_For_Switches(0x01);
    
    
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