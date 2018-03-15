#include "derivative.h"
#include "Delay_C.h"
#include "A2D_Lib_C.h"
/*
;***********************************************************
;*      Libary: adc_lib_C.c                             
;*      Contains:                                           
;*               ATD0_Init()                                     
;*               ATD0_Sample()                                          
;*                                                         
;*              Author: Riley McGuire                      
;*                                                         
;*              Last Modified: March 06, 2018 (created)  
;*                     
;***********************************************************


;***********************************************************
;*      ATD0_Init()                                  
;*                                                          
;*      Requires:       None      
;*      Returns:        None                               
;*      Regs Affected:  None                         
;*                                                         
;*      Description:    Initializes the A/D converter for the 
;*                      9S12 and wait for it to get up to voltage 
;*                                                         
;***********************************************************

*/

	void ATD0_Init(void)
	{
	  //turn on A/D and wait for power up
		ATD0CTL2 = 0xE0;
		Delay_C(1);
		//set up single conversion and wait for pwer up
		ATD0CTL3 = 0x02;
		ATD0CTL4 = 0x26;
		
		Delay_C(100);
	}

/*
 ;***********************************************************
;*      ATD0_Sample7()                                  
;*                                                          
;*      Requires:       a write to ATD0CTL5 starts sample sequence      
;*      Returns:        A2D value is returned in result register 0                               
;*      Regs Affected:  None                         
;*                                                         
;*      Description:    gets sample result from result register 
;*                                                         
;***********************************************************

*/

	unsigned int ATD0_Sample7(void)
	{
	  //convert to right justify
		ATD0CTL5 = 0xB0;
		//wait for conversion to complete and return result
		while(ATD0STAT0&0x80 != 0x80){
		}
		return (ATD0DR7);
	}

