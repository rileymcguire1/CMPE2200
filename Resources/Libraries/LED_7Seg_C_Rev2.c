#include "derivative.h"
#include "LED_7SEG_C.h"

/*
;***********************************************************
;*      Libary:   LEDS_7SEG_C
;*                               
;*      Contains: LEDS_7Seg_Init
;*                Clear_7Seg
;*                Char_7Seg
;*                Char_7Seg_D
;*                Bot_8Out                            
;*                Bot_16Out
;*                Top_8Out
;*                Top_16Out
;*                Seg_write  
;*                                                         
;*              Author: Riley McGuire                      
;*                                                         
;*              Last Modified: Feb 01, 2018 (created)  
;*                                                         
;***********************************************************


;***********************************************************
;*      Function:       LEDS_7Seg_Init                          
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 01, 2018                               
;*      Description:    This function initializes the port 
;*                      lines accosiated with the LEDS 
;*                                                         
;***********************************************************
*/
void LEDS_7Seg_Init(void)
{
  signed char i = 0;
  unsigned char Digit = 0;
  
  DDRA |= 0x03;
  DDRB = 0xff;
  
  for(i=7;i>=0;i--)
  {
    Clear_7Seg(i);
  }
}

/*
;***********************************************************
;*      Function:       Clear_7Seg                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 01, 2018                                
;*      Description:    Clears all segments of char in pos 
;*                                                         
;***********************************************************
*/
void Clear_7Seg(unsigned char Pos) 
{
  unsigned char temp;
  
  Pos |= 0x70;
  
  PORTB = Pos;
  
  temp = PORTA;
  temp &= 0xFC;
  temp |= 0x02;
  
  PORTA = temp;
  PORTA |= 0x03;
  
  PORTB = 0x80;
  
  PORTA &= 0xFC;
  PORTA |= 0x01;
}

/*
;***********************************************************
;*      Function:       Char_7Seg                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 01, 2018                                
;*      Description:    Sends character to pos                                   
;***********************************************************
*/

void Char_7Seg(unsigned char Pos, unsigned char Character)
{
  unsigned char temp;
  
  Pos |= 0x50;
  
  PORTB = Pos;
  
  temp = PORTA;
  temp &= 0xFC;
  temp |= 0x02;
  
  PORTA = temp;
  PORTA |= 0x03;
  
  PORTB = (Character |= 0x80);
  
  PORTA &= 0xFC;
  PORTA |= 0x01;
}
  

/*
;***********************************************************
;*      Function:       Char_7Seg_D                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 01, 2018                                
;*      Description:    Sends character to pos with decimal                                   
;***********************************************************
*/

void Char_7Seg_D(unsigned char Pos, unsigned char Character)
{
  unsigned char temp;
  
  Pos |= 0x50;
  
  PORTB = Pos;
  
  temp = PORTA;
  temp &= 0xFC;
  temp |= 0x02;
  
  PORTA = temp;
  PORTA |= 0x03;
  
  PORTB = Character;
  
  PORTA &= 0xFC;
  PORTA |= 0x01;
}

/*
;***********************************************************
;*      Function:       Bot_8Out                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 05, 2018                                
;*      Description:    Places input data on the bottom row,
;*                      upper two digits of row are blanked                                   
;***********************************************************
*/

void Bot_8Out(unsigned char cIn)
{
  unsigned char cVal;
  Clear_7Seg(0x04);
  Clear_7Seg(0x05);
  
  cVal = cIn >> 4;
  Char_7Seg(6, cVal);
  cVal = cIn & 0x0f;
  Char_7Seg(7, cVal);
}

/*
;***********************************************************
;*      Function:       Bot_16Out                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 05, 2018                                
;*      Description:    Places input data on the bottom row                                                    
;***********************************************************
*/

void Bot_16Out(unsigned int cIn)
{
  unsigned char iVal;
  iVal = cIn & 0x00ff;
  Bot_8Out(iVal);
  
  iVal = cIn >> 12;
  Char_7Seg(4, iVal);
  iVal = cIn >> 8;
  Char_7Seg(5, iVal);
}


/*
;***********************************************************
;*      Function:       Top_8Out                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 05, 2018                                
;*      Description:    Places input data on the top row,
;*                      upper two digits of row are blanked                                   
;***********************************************************
*/

void Top_8Out(unsigned char cIn)
{
  unsigned char cVal;
  Clear_7Seg(0x04);
  Clear_7Seg(0x05);
  
  cVal = cIn >> 4;
  Char_7Seg(2, cVal);
  cVal = cIn & 0x0f;
  Char_7Seg(3, cVal);
}

/*
;***********************************************************
;*      Function:       Top_16Out                     
;*                                                          
;*      Author:         Riley McGuire                      
;*      Date:           Feb 05, 2018                                
;*      Description:    Places input data on the top row                                                    
;***********************************************************
*/

void Top_16Out(unsigned int cIn)
{
  unsigned char iVal;
  iVal = cIn & 0x00ff;
  Top_8Out(iVal);
  
  iVal = cIn >> 12;
  Char_7Seg(0, iVal);
  iVal = cIn >> 8;
  Char_7Seg(1, iVal);
}