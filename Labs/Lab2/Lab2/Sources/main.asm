;****************************************************************************
;* HC12 Program:  Lab2 - Counting using switch presses                      *
;* Processor:     mc9s12xdp512                                              *
;* Xtal Speed:    16 MHz                                                    *
;* Author:        Riley McGuire                                             *
;* Date:          16:00 May 19, 2010	                                      *
;*                                                                          *
;* Details: Count to the RYG LEDs using switch presses as input. Left switch*
;*          is enable, up increments, down decrements and center resets     * 
;*          count                                                           *
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
  BRSET PT1AD1, #%00001000, Enable  ;check to see if enable is pressed
  BRSET PT1AD1, #%00000001, Reset   ;begin clear process 
  
Enable:  
  BRSET PT1AD1, #%00011000, DebounceUp    ;begin increment process
  BRSET PT1AD1, #%00001100, DebounceDown  ;begin increment process
  BRA Loop
  
Reset:              ;checks to make sure no other button is pressed
  BRCLR PT1AD1, #%00011110, Clear
  BRA Loop
  
Clear:             ;resets LED counter
  JSR Red_Off
  JSR Yellow_Off
  JSR Green_Off
  BRA Loop  
    
DebounceUp:      ;Debounce the up button press
  LDX #10
  JSR Delay
  BRSET PT1AD1, #%00011000, Increment
  BRA Loop
  
DebounceDown:     ;Debounce the down button press
  LDX #10
  JSR Delay
  BRSET PT1AD1, #%00001100, Decrement
  BRA Loop  
    
Increment:        ;increment the LED counter
  LDD PT1AD1
  ADDA #%00100000
  STD PT1AD1
  BRA ReleaseUp
  
Decrement:        ;Decrement the LED counter
  LDD PT1AD1
  SUBA #%00100000
  STD PT1AD1
  BRA ReleaseDown
  
ReleaseUp:
  BRSET PT1AD1, #%00011000, ReleaseUp
  BRA Loop    

ReleaseDown:
  BRSET PT1AD1, #%00001100, ReleaseDown
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
