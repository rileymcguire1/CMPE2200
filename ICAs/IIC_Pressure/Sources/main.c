/********************************************************************
*HC12 Program:	Pressure Sensor - First crack at barometric sensor
*Processor:		MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Riley McGuire
*Date:		April 10,2018                                       
*Details: Program to display the air pressure from an MPL3115A2 sensor
*         Modified original from Ross T.
********************************************************************/

#include <hidef.h>      	// common defines and macros
//#include <stdio.h>		// ANSI C Standard Input/Output functions
//#include <math.h>			// ANSI C Mathematical functions
#include "derivative.h"    	// derivative-specific definitions

/********************************************************************
*		Library includes
********************************************************************/
#include "IIC0_Lib.h"
#include "LCD_4Line_C.h"
#include "Delay_C.h"
#include "stdio.h"
//#include "math.h"
//#include "Misc_Lib.h"
//#include "SevSeg_Lib.h"


/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

unsigned char cSta;
unsigned long lPress;
int iTemperature;
double dTemperature;
double dKPascals;
char s[20];         //array for outputting string data


//char cPressInfo1[] ="    adjusted to ";
//char cPressInfo2[] ="   sea level (YEG)";

char cBarPress[] = "Barometric Pressure";

/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{
	_DISABLE_COP();

/********************************************************************
*		Initializations
********************************************************************/
 
  
	//SevSeg_Init();
  lcdInit();
	//LCD_CursOff();
	IIC0_Init();    //about 20usec delay in place of 8us
	lcdSDelay();
	//TimInit8us(); //

	IIC0_Write(0xC0,0x26,0b00111000);		//Set for Barometer with 128 oversample
	IIC0_Write(0xC0,0x13,0b00000111);		//Enable Data Flag for temperature and pressure
	IIC0_Write(0xC0,0x26,0b00111001);		//Activate for data generation
	cSta = IIC0_Read(0xC0,0x00);			  //Dummy check of status register
	
	Set_R_C(0,0);
	lcdString(cBarPress);
	/*Set_R_C(2,0);
  lcdString(cPressInfo1);
	Set_R_C(3,0);
	lcdString(cPressInfo2);
	*/
	
	
	for (;;)		//endless program loop
	{
/********************************************************************
*		Main Program Code
********************************************************************/
//The presure calculation:
		while((IIC0_Read(0xC0,0x00)&0b00000100)==0);	//check status of pressure/temperature
		
		lPress=IIC0_Read(0xC0,0x01);		//upper byte
		lPress<<=8;
		lPress+=IIC0_Read(0xC0,0x02);		//centre byte
		lPress<<=8;
		lPress+=IIC0_Read(0xC0,0x03);		//low byte
		if((lPress&0b000000000000000000100000)>0) lPress+=0b000000000000000001000000; //round up
		lPress>>=6;							  //keep upper 18 bits (no fraction)
	                						//Sea-level equivalent correction
	lPress+=8100;// Blk       //This value determined experimentally by comparison to Blatchford Aiport readings
	
	 
//Convert to KPa, and display the results
		
		dKPascals = lPress/1000.0;
		//function from measured to actual pressure
		dKPascals = 0.9869*dKPascals + 1.3519;
		
		Set_R_C(1,5);
		if(sprintf(s,"%7.3f KPa",dKPascals)>=0)
		lcdString(s);
		
		
//The temperature calculation
		iTemperature=IIC0_Read(0xC0,0x04);		//upper byte
		iTemperature<<=8;
		iTemperature+=IIC0_Read(0xC0,0x05);		//lower byte
		dTemperature = iTemperature/256.0;
		
		Set_R_C(2,0);
		if(sprintf(s,"Temperature (C)")>=0)
		lcdString(s);
		
		Set_R_C(3,0);
		if(sprintf(s,"%12.1f",dTemperature)>=0)
		lcdString(s);
		
		Delay_C(250);

	}
}
/********************************************************************
*		Functions
********************************************************************/



/********************************************************************
*		Interrupt Service Routines
********************************************************************/



/*******************************************************************/
