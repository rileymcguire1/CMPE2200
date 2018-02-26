#include "derivative.h"
#include "Delay_C.h"
#include "Switches_C.h"

/*
;***********************************************************
;*      Libary: Switches_C.c                               
;*      Contains:Sw_Init()                                  
;*               Get_Switches()                            
;*               Wait_for_Switches_Up()                    
;*                                                         
;*              Author: Riley McGuire                      
;*                                                         
;*              Last Modified: January 29, 2018 (created)  
;*                                                         
;***********************************************************


;***********************************************************
;*      Function:       Sw_Init()                          
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           January 29, 2019                               
;*      Description:    This function initializes the port 
;*                      lines accosiated with the switches 
;*                                                         
;***********************************************************
*/
void Sw_Init() 
{
  ATD1DIEN1 |= 0x1F;  //Enable inputs for the switches
}

/*
;***********************************************************
;*      Function:       Get_Switches()                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           January 29, 2019                                
;*      Description:    Returns an unsigned char that contains ones in the bit 
;*                      positions of the switches that are down after debouncing 
;*                                                         
;***********************************************************
*/
unsigned char Get_Switches() 
{
  unsigned char Switches = 0;
  Switches = PT1AD1 & 0x1F;
  Delay_C(10);
  
  if((PT1AD1 &0x1F) != Switches)
    Switches = 0;
  
  return Switches;
}

/*
;***********************************************************
;*      Function:       Wait_For_Switches()                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           January 29, 2019                                
;*      Description:    This function hangs in a loop waiting for the switches
;*                      represented by the mask passed in to be in the up state
;*                                                         
;***********************************************************
*/
void Wait_For_Switches(unsigned char mask){
    unsigned char Switches = 0;
    Switches = PT1AD1 & mask;
    while(Switches){
      Switches = PT1AD1 & mask;
    }
    
    return;
}