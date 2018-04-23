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
//#include "SCI_Lib_C.h"
#include "Timer.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

char output[20];
unsigned int input;
double voltage;
double dutyCycle;
unsigned int counter;
float stepSize = 0.005;


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
Timer_Init(3);  
lcdInit();  
EnableInterrupts; 

//read A2D initial time to set first interrupt
input = ATD0_Sample7();
voltage = input * stepSize;
dutyCycle = voltage / 5.115;
TC0 = TCNT + 10000 * dutyCycle;

/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
	  //read A2D to get voltage
	  input = ATD0_Sample7();
    voltage = input * stepSize;
    
	  //determine duty cycle from voltage   
	  if(voltage >= 4.5) {
	    dutyCycle = 0.9;
	  } else if(voltage <= 0.5){
	    dutyCycle = 0.1;
	  }
	  else{
	    dutyCycle = voltage / 5.115;
	  }

    //wait for toggle
    asm WAI;
    
    //display relevant data
    lcdLabels("A2D Output:","Voltage:","Duty Cycle:","");
    Set_R_C(0,13);
    (void)sprintf(output,"%X",input);
    lcdString(output);
    Set_R_C(1,10);
    (void)sprintf(output,"%5.3f",input*stepSize);
    lcdString(output);
    Set_R_C(2,13);
    (void)sprintf(output,"%3.1f%%",dutyCycle*100);
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
 interrupt VectorNumber_Vtimch0 void TimerInternal (void){
    TFLG1 = 0x01;
    counter++;
    //set new interrupt 
    if(counter%2){
     TC0 += dutyCycle*10000;
    } 
    else{
      TC0 += (1-dutyCycle)*10000;
    }
  }


/**************************************************************/