;****************************************************************************
;* HC12 Program:  ICA3 - Binary Counter for LEDs                            *
;* Processor:     mc9s12xdp512                                              *
;* Xtal Speed:    16 MHz                                                    *
;* Author:        Riley McGuire                                             *
;* Date:          Jan 18, 2018      	                                      *
;*                                                                          *
;* Details: A more detailed explanation of the program is entered here      *
;*                                                                          * 
;*                                                                          *
;*                                                                          *
;*                                                                          *
;****************************************************************************

; export symbols
            XDEF Entry            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point

; include derivative specific macros
            INCLUDE 'mc9s12xdp512.inc'
            
            
;**************************************************************
;*                  Equates Declared Here                     *
;**************************************************************
ROMStart    EQU  $4000  ; absolute address to place my code/constant data


            

;**************************************************************
;*                 Variables Declared Here                    *
;**************************************************************
            ORG RAMStart 			;Address $0400            
;Insert your variables here 




;**************************************************************
;*                 Constants Declared Here                    *
;**************************************************************
            
Constants	EQU $C000	
	ORG Constants 			;Address $C000

            
;Insert your constants here 




;**************************************************************
;*                 Code Section Here                          *
;**************************************************************
            ORG   ROMStart		  ;Address	$4000
Entry:
            LDS   #RAMEnd+1       ; initialize the stack pointer
                                  ; enable interrupts
                                  
                                  

;Place your code here starting at the Main label                                
                              
Main:
  JSR RYG_LED_Init
Loop:  
  LDX #1000
  JSR Delay
          
  LDD PT1AD1
  ADDA #%00100000
  STD PT1AD1
  BRA Loop
  
  
  
;**************************************************************
;*                 SCI VT100 Strings Defined Here             *
;**************************************************************  
  
     
     
;**************************************************************
;*                 Look-Up Table Includes                     *
;**************************************************************

          ;INCLUDE "YourLookUp.inc" 

 
         
         
;**************************************************************
;*           Absolute XDP512 Library Includes                 *
;************************************************************** 
         ; XDP512 Libs
         ;INCLUDE "IIC-24AA512_EEPROM.inc"
         ;INCLUDE "LCD_XDP512.inc"
         ;INCLUDE "LEDS_7Seg.inc"
         INCLUDE "LEDS_RYG_XDP512.inc"         
         INCLUDE "My Delays.inc"
         ;INCLUDE "Switches_XDP512.inc"
         
       
         

;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry           ; Reset Vector
