#include "derivative.h"
/*
;***********************************************************
;*      Libary: LEDS_RYG_XDP512.inc                        *
;*      Contains:                                          * 
;*              Red_On                                     *
;*              Red_Off                                    *
;*              Red_Toggle                                 *
;*                                                         *
;*              Yellow_On                                  *
;*              Yellow_Off                                 *
;*              Yellow_Toggle                              *
;*                                                         *
;*              Green_On                                   *
;*              Green_Off                                  *
;*              Green_Toggle                               *
;*                                                         *
;*              RYG_LED_Init                               *
;*                                                         *
;*                                                         *
;*              Author: Riley McGuire                      *
;*                                                         *
;*              Last Modified: January 15, 2018 (created)  *
;*                                                         *
;***********************************************************


;***********************************************************
;*      RYG_LED_Init  Subroutine                           *
;*                                                         * 
;*      Requires:       None                               *
;*      Returns:        None                               *
;*      Regs Affected:  None                               *
;*                                                         *
;*      Description:    This routine initializes the upper *
;*                      half of portad for the RYG LEDs    *
;*                                                         *
;***********************************************************

RYG_LED_Init: BCLR PT1AD1, #$E0      ;make all leds low
              BSET DDR1AD1, #$E0     ;make PAD13-15 outputs, rest inputs
              BSET ATD1DIEN1, #$1F   ;enable digital outputs to switches
              RTS
*/
void led_sw_init(void)
{
	PT1AD1 &= 0x1F;
	DDR1AD1 |= 0xE0;
}


/*              
;***********************************************************
;*      Red On-Off-Toggle  Subroutine                      *
;*                                                         * 
;*      Requires:       None                               *
;*      Returns:        None                               *
;*      Regs Affected:  None                               *
;*                                                         *
;***********************************************************              


Red_On:     PSHD
            LDD PT1AD1
            ORAA #%10000000
            STD PT1AD1
            PULD
            RTS
          
Red_Off:    PSHD
            LDD PT1AD1
            ANDA #%01111111
            STD PT1AD1
            PULD
            RTS
          
Red_Toggle: PSHD
            LDD PT1AD1
            EORA #%10000000
            STD PT1AD1
            PULD
            RTS          
*/     

void Red_On(void)
{
	PT1AD1 |= 0x80;
}

void Red_Off(void)
{
	PT1AD1 &= 0x7F;
}

void Red_Toggle(void)
{
	PT1AD1 ^= 0x80;
}

/*
            
;***********************************************************
;*      Yellow On-Off-Toggle  Subroutine                   *
;*                                                         * 
;*      Requires:       None                               *
;*      Returns:        None                               *
;*      Regs Affected:  None                               *
;*                                                         *
;***********************************************************              


Yellow_On:      PSHD
                LDD PT1AD1
                ORAA #%01000000
                STD PT1AD1
                PULD
                RTS
          
Yellow_Off:     PSHD
                LDD PT1AD1
                ANDA #%10111111
                STD PT1AD1
                PULD
                RTS
          
Yellow_Toggle:  PSHD
                LDD PT1AD1
                EORA #%01000000
                STD PT1AD1
                PULD
                RTS          
           
*/

void Yellow_On(void)
{
	PT1AD1 |= 0x40;
}

void Yellow_Off(void)
{
	PT1AD1 &= 0xBF;
}

void Yellow_Toggle(void)
{
	PT1AD1 ^= 0x40;
}

/*
            
;***********************************************************
;*      Green On-Off-Toggle  Subroutine                    *
;*                                                         * 
;*      Requires:       None                               *
;*      Returns:        None                               *
;*      Regs Affected:  None                               *
;*                                                         *
;***********************************************************              


Green_On:     PSHD
              LDD PT1AD1
              ORAA #%00100000
              STD PT1AD1
              PULD
              RTS
          
Green_Off:    PSHD
              LDD PT1AD1
              ANDA #%11011111
              STD PT1AD1
              PULD
              RTS
          
Green_Toggle: PSHD
              LDD PT1AD1
              EORA #%00100000
              STD PT1AD1
              PULD
              RTS  
			  
*/

void Green_On(void)
{
	PT1AD1 |= 0x20;
}

void Green_Off(void)
{
	PT1AD1 &= 0xDF;
}

void Green_Toggle(void)
{
	PT1AD1 ^= 0x20;
}