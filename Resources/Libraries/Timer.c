#include "Timer.h"
#include "derivative.h"
/*
;***********************************************************
;*      Libary: Timer                              
;*      Contains:                                           
;*               Timer_Init                                     
;*                                                         
;*                                                         
;*              Author: Riley McGuire                      
;*                                                         
;*              Last Modified: January 15, 2018 (created)  
;*              Converted to C:  January 25, 2018          
;***********************************************************


;***********************************************************
;*      Init  Subroutine                                  
;*                                                                                                                                   
;*      Description:    Initializes the timer system  
;*                      output is pin 9 on board   
;*
;*      Prescaler: 0 - 128 (8MHz / prescalar)
;*                                        
;***********************************************************

*/

	void Timer_Init (unsigned char prescaler)
	{
	  TSCR1 = 0b10000000;
	  TSCR2 &= 0b1111000;
	  TSCR2 |=prescaler;  //prescaler
	  TIOS |=0b00000001;
	  TCTL2 &= 0b11111100;
	  TCTL2 |= 0b00000001;
	  TIE |= 0b00000001;
	  TFLG1 = 0b00000001;
	}



