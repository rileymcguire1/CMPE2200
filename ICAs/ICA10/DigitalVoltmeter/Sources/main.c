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
  #include "Delay_C.h"
  //#include "RYG_LEDs.h"
  #include "Switches_C.h"
  #include "A2D_Lib_C.h"


  /********************************************************************
  *		Prototypes
  ********************************************************************/



  /********************************************************************
  *		Variables
  ********************************************************************/

   unsigned int result;
   unsigned int max = 0;
   unsigned int min = 0x3FF;
   char s[20];
   float stepSize = 0.005;
   unsigned int counter = 0;

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
    ATD0_Init();
   


  /********************************************************************
  *		Main Program Code
  ********************************************************************/
  	
  	for (;;)		//endless program loop
  	{
  	
  	if(counter == 0){
  	  
  	  //get A/D result from register
      result = ATD0_Sample7();  
      
      //determine max
      if(result>max) {
        max = result;
      }
      
      //determine min
      if(result<min){
        min = result;
      }
      //reset counter
      counter = 800;
  	
      
      //set labels
      lcdLabels("SAMPLED A/D:", "VOLTAGE:", "MAX VOLTAGE:","MIN VOLTAGE");
      
      //display hex result
      Set_R_C(0,13);
      sprintf(s, "%03X", result);  
      lcdString(s);
      
      //display decimal result
      Set_R_C(1,9);
      sprintf(s,"%5.3f V", result*stepSize);
      lcdString(s);
      
      //display min
      Set_R_C(3,13);
      sprintf(s,"%5.3f V", min*stepSize);
      lcdString(s);
      
      //display max
      Set_R_C(2,13);
      sprintf(s,"%5.3f V", max*stepSize);
      lcdString(s);
  	}
      
      //check for button presses
      if(Get_Switches() == 0x10){
        max = result;
        Set_R_C(2,13);
        sprintf(s,"%5.3f V", 0);
        lcdString(s);
      }
      if(Get_Switches() == 0x04){
        min = result;
        Set_R_C(3,13);
        sprintf(s,"%5.3f V", 0);
        lcdString(s);
      }
      if(Get_Switches() == 0x01){
        min = result;
        max = result;
        Set_R_C(2,13);
        sprintf(s,"%5.3f V", 0);
        lcdString(s);
        Set_R_C(3,13);
        sprintf(s,"%5.3f V", 0);
        lcdString(s);
        
      }
      
      
      
      //delay 1 ms and increment counter
      Delay_C(10);
      counter -=10;

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
