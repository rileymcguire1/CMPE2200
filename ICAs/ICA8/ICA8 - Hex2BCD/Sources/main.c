/**************************************************************************
*HC12 Program:	ICA8 - Hex to BCD conversion
*Processor:	MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		Feb 26, 2018
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
#include "LED_7Seg_C.h"
#include "Delay_C.h"
//#include "RYG_LEDs.h"
#include "Switches_C.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

 unsigned int Top;
 unsigned int Bot;
 unsigned int temp;
 unsigned char Pos;
 unsigned int change;
 unsigned char indicator;
 int i;
 unsigned char error;


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
  LEDS_7_Init();
  lcdInit();
 


/********************************************************************
*		Main Program Code
********************************************************************/
	
	for (;;)		//endless program loop
	{
    //check for side buttons to move cursor
    if(Get_Switches()==0x02){
      if(Pos == 3){
        Pos = 0;
      } else{ 
      Pos++;  
      }
      indicator = 1;
      Wait_For_Switches(0x02);
    }
    if(Get_Switches()==0x08){
      if(Pos == 0){
        Pos = 3;
      } else{ 
      Pos--;  
      }
      indicator = 1;
      Wait_For_Switches(0x08);
    }
    //determine position of cursor                                        
    switch(Pos) {
      case 3:
        change = 0x0001;
        break;
      case 2:
        change = 0x0010;       
        break;
	    case 1:
	      change = 0x0100;        
        break;
	    case 0:
	      change = 0x1000;        
        break;    
    }
    //change value on top on top/bottom press
    if(Get_Switches()==0x10)     //up press increments top
        {
          Top+=change;
          Top_16Out(Top);
          Wait_For_Switches(0x10);
          indicator = 1;
        }
     if(Get_Switches()==0x04)    //down press decrements bottom
        {
          Top-=change;
          Top_16Out(Top);
          Wait_For_Switches(0x04);
          indicator = 1;
        }
      //turn indicator off on center button press
      if(Get_Switches()==0x01){
        indicator =0;
        Wait_For_Switches(0x01);
      }
     
     if(indicator){
      //make cursor on bottom to indicate position
      for(i=7;i>=4;i--)
      {
        Clear_7Seg(i);
      }
      Char_7Seg(Pos+4, 1);
     } 
     else{
     //number too high, display error message
        if(Top>9999){
           error = 1;
        } 
        else{
          error = 0;
        //convert hex on top to decimal on bottom
        Bot = Top/1000;
        Bot = Bot <<4;
        temp = Top%1000;
        Bot += temp/100;
        Bot = Bot << 4;
        temp = temp %100;
        Bot += temp/10;
        Bot = Bot << 4;
        Bot += temp % 10;
        
        Bot_16Out(Bot);
        }
     }
     if(error){
        Set_R_C(1, 5);        lcdString("Input number");
        Set_R_C(2,6);
        lcdString("too high!");
        for(i=3;i>=0;i--)
        {
          Clear_7Seg(i);
        }
        Delay_C(50);
        Top_16Out(Top);
        Delay_C(50);
        
     }else{
       lcdClear();
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
