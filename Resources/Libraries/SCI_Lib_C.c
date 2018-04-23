#include "derivative.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Delay_C.h"
#include "SCI_Lib_C.h"
/*
;***********************************************************
;*      Libary: SCI_Lib.c                             
;*      Contains:
;*               Init19200()                                           
;*               Key_hit()                                     
;*               Rx_Byte()
;*               Tx_Byte()
;*               Tx_String()
;*               TxSCI_String_B()                                                           
;*                                                         
;*              Author: Riley McGuire                      
;*                                                         
;*              Last Modified: March 15, 2018 (created)  
;*                     
;***********************************************************



 ;***********************************************************
;*      SCI_19200()                                                                                                    
;*                                                         
;*      Description:  19200 Baud, 8N1
;*                                                         
;***********************************************************

*/

	void Init19200(void){
	 SCI0BDH = 0;
	 SCI0BDL = 26;
	 SCI0CR1 = 0x00;
	 SCI0CR2 = 0x0C;
	}

/*
;***********************************************************
;*      Key_hit()                                  
;*                                                               
;*      Returns:        SCI0SR1 & 20                                      
;*                                                         
;*      Description:    This is chekcing RDRF
;*                      Calling program needs to look at the return value
;*                      and run Rx_Byte if return value is non-zero 
;*                                                         
;***********************************************************

*/

	unsigned char Key_hit(void)
	{
	  return SCI0SR1 & 0x20;
	}

/*
 ;***********************************************************
;*      Rx_Byte()                                  
;*                                                          
;*      Requires:       none    
;*      Returns:        ASCII code for a keyboard press                               
;*      Regs Affected:  None                         
;*                                                         
;*      Description:    pools the RDRF of SCI0SR1 until char is recvd
;*                                                         
;***********************************************************

*/

	unsigned char Rx_Byte(void)
	{
	  while((SCI0SR1 & 0x20)==0);
	  return SCI0DRL;  
	    
	}

/*
 ;***********************************************************
;*      Tx_Byte()                                  
;*                                    
;*      Description: character to be sent is passed into the function
;*                   as an unsigned char. The transmit register is checked
;*                   until it is empty prior to writing the char to it 
;*                                                         
;***********************************************************

*/

	void Tx_Byte(unsigned char cVal)
	{
	  while((SCI0SR1 & 0x80)==0);
	  SCI0DRL = cVal; 
	    
	}


/*
 ;***********************************************************
;*      Tx_String()                                  
;*                                    
;*      Description: calls Tx_Byte to trasmit each element of string 
;*                                                         
;***********************************************************

*/

	void Tx_String(char * cString)
	{
	  while(*cString !=0){
	    Tx_Byte(*cString++);
	  }
	    
	}
	
/*
;***********************************************************
;*      GetNumber()                                  
;*                                    
;*      Description: Get user input from keyboard on terraterm
;*                   takes output variable
;*                                                         
;***********************************************************

*/

void GetNumber(char* output){
    char input[2] = "";
    char RxData;
    do{
      RxData = Rx_Byte();
      Tx_Byte(RxData);
      input[0] = RxData;
      (void)strcat(output,input);
    }while(RxData != 0x0d);
    output[strlen(output)-1] = 0;
    Tx_String("\x1B[2J\x1B[H");
}


