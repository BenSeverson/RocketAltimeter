/*********************************************************************
*
*                Microchip USB C18 Firmware Version 1.2
*
*********************************************************************
* FileName:        user.c
* Dependencies:    See INCLUDES section below
* Processor:       PIC18
* Compiler:        C18 3.11+
* Company:         Microchip Technology, Inc.
*
* Software License Agreement
*
* The software supplied herewith by Microchip Technology Incorporated
* (the “Company”) for its PICmicro® Microcontroller is intended and
* supplied to you, the Company’s customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Rawin Rojvanit       11/19/04    Original.
* Rawin Rojvanit       05/14/07    A few updates.
********************************************************************/

/******************************************************************************
* CDC RS-232 Emulation Tutorial Instructions:
******************************************************************************
* Refer to Application Note AN956 for explanation of the CDC class.
*
* First take a look at Exercise_Example() and study how functions are called.
*
* There are five exercises, each one has a solution in the CDC\user\solutions.
* Scroll down and look for Exercise_01,_02,_03,_04, and _05.
* Instructions on what to do is inside each function.  The exercises make use
* of LEDs, general purpose pushbuttons, and the temperature sensor found on
* the PICDEM FS USB Demo Board.  Excercises 1 and 4 can be used directly
* on the PIC18F87J50 FS USB Plug-In Module board, but the other exercises use
* hardware items not phsyically present (such as temperature sensor) on the
* board.
*
*****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <i2c.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "io_cfg.h"             // I/O pin mapping
#include "user\user.h"
#include "user\temperature.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
byte old_sw2,old_sw3;

char input_buffer[64];
char output_buffer[64];

rom char welcome[]={"Full-Speed USB - CDC RS-232 Emulation Demo\r\n\r\n"};
rom char ansi_clrscr[]={"\x1b[2J"};         // ANSI Clear Screen Command

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void InitializeUSART(void);
void BlinkUSBStatus(void);
BOOL Switch2IsPressed(void);
BOOL Switch3IsPressed(void);

void Exercise_Example(void);

void Exercise_01(void);
void Exercise_02(void);
void Exercise_03(void);
void Exercise_04(void);
void Exercise_05(void);

/** D E C L A R A T I O N S **************************************************/
#pragma code
void UserInit(void)
{
	mInitAllSwitches();
	//INTCON2bits.RBPU = 0;
	old_sw2 = sw2;

	InitializeUSART();

}//end UserInit

void InitializeUSART(void)
{
	TRISCbits.TRISC7=1; // RX
	TRISCbits.TRISC6=0; // TX
	SPBRG = 0x71;
#if defined(__18F87J50)||defined(__18F86J55)|| \
	defined(__18F86J50)||defined(__18F85J50)|| \
	defined(__18F67J50)||defined(__18F66J55)|| \
	defined(__18F66J50)||defined(__18F65J50)
	SPBRGH1 = 0x02;      // 0x0271 for 48MHz -> 19200 baud
#else
	SPBRGH = 0x02;      // 0x0271 for 48MHz -> 19200 baud
#endif
	TXSTA = 0x24;       // TX enable BRGH=1
	RCSTA = 0x90;       // continuous RX
	BAUDCON = 0x08;     // BRG16 = 1
}//end InitializeUSART

void putsUSART(char *data)
{
	do
	{  // Transmit a byte
		while(!TXSTAbits.TRMT);
		TXREG = *data;      // Write the data byte to the USART, 8-bit mode only
	} while( *data++ );
}

/******************************************************************************
* Function:        void ProcessIO(void)
*
* PreCondition:    None
*
* Input:           None
*
* Output:          None
*
* Side Effects:    None
*
* Overview:        This function is a place holder for other user routines.
*                  It is a mixture of both USB and non-USB tasks.
*
* Note:            None
*****************************************************************************/
void ProcessIO(void)
{

	// User Application USB tasks
	if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
//while(sw2 == 1){}
//if(mUSBUSARTIsTxTrfReady())
 //putrsUSBUSART("\rstarting program\r\n");
	Exercise_Example();

	/* Exercise_01();
	Exercise_02();
	Exercise_03();
	Exercise_04();
	Exercise_05();*/

}//end ProcessIO

void Exercise_Example(void)
{

}//end Exercise_Example

void Exercise_01(void)
{
	/*
	* Write code in this function that sends a literal null-terminated
	* string of text ("Hello World!\r\n") to the PC when switch 2 is
	* pressed.
	*
	* Useful functions:
	*  Switch2IsPressed() returns '1' when switch 2 is pressed.
	*  putrsUSBUSART(...);
	*
	* See examples in Exercise_Example();
	*
	* Remember, you must check if cdc_trf_state is ready for another
	* transfer or not. When it is ready, the value will equal CDC_TX_READY,
	* or use macro: mUSBUSARTIsTxTrfReady()
	*/

	/* Insert code here - 3 lines */

	/* End */

}//end Exercise_01

rom char ex02_string[]={"Type in a string here.\r\n"};
void Exercise_02(void)
{
	/*
	* Write code in this function that sends a null-terminated string
	* of text stored in program memory pointed to by "ex02_string" to
	* the PC when switch 3 is pressed.
	*
	* ex02_string is declared right above this function.
	*
	* Useful functions:
	*  Switch3IsPressed() returns '1' when switch 3 is pressed.
	*  putrsUSBUSART(...);
	*
	* See examples in Exercise_Example();
	*
	* Remember, you must check if cdc_trf_state is ready for another
	* transfer or not. When it is ready, the value will equal CDC_TX_READY,
	* or use macro: mUSBUSARTIsTxTrfReady()
	*/

	/* Insert code here - 3 lines*/

	/* End */

}//end Exercise_02

void Exercise_03(void)
{
	/*
	* Write code in this function that reads data from USB and
	* toggles LED D4 when the data read equals ASCII character '1' (0x31)
	*
	* Useful functions:
	*  byte getsUSBUSART(char *buffer, byte len)   See cdc.c for details
	*  mLED_4_Toggle();
	*
	* Use input_buffer[] to store data read from USB.
	*/

	/* Insert code here - 3 lines */

	/* End */

}//end Exercise_03

void Exercise_04(void)
{
	/*
	* Before starting Exercise_04(), comment out the call to Exercise_01()
	* in ProcessIO(); This function will need to check Switch2IsPressed().
	*
	* Write code in this function that sends the following 4 bytes of
	* data: 0x30,0x31,0x32,0x33 when switch 2 is pressed.
	* Note that these data is not null-terminated and is located in
	* the data memory.
	*
	* Useful functions:
	*  Switch2IsPressed() returns '1' when switch 2 is pressed.
	*  mUSBUSARTTxRam(byte *pData, byte len) See cdc.h for details.
	*
	* Use output_buffer[] to store the four bytes data.
	*
	* Remember, you must check if cdc_trf_state is ready for another
	* transfer or not. When it is ready, the value will equal CDC_TX_READY,
	* or use macro: mUSBUSARTIsTxTrfReady()
	*/

	/* Insert code here - 7 lines */

	/* End */

}//end Exercise_04

void Exercise_05(void)
{
	/*
	* The PICDEM Full-Speed USB Demo Board is equipped with a
	* temperature sensor. See temperature.c & .h for details.
	*
	* All necessary functions to collect temperature data have
	* been called. This function updates the data a few times
	* every second. The program currently sends out the
	* temperature data to the PC via UART.
	*
	* You can check this by hooking up a serial cable and
	* set your serial port to 19200 baud, 8 bit data, 1 Stop,
	* no parity.
	*
	* The program assumes CPU Frequency = 48 MHz to generate
	* the correct SPBRG value for 19200 baud transmission.
	*
	* Modify the code to send the ASCII string stored in
	* tempString to the PC via USB instead of UART.
	*
	* The temperature data is stored in tempString array in
	* ASCII format and is null-terminated.
	*
	* Useful function:
	*  putsUSBUSART(...);
	*
	*  Note: It is 'puts' and not 'putrs' to be used here.
	*
	* Remember, you must check if cdc_trf_state is ready for another
	* transfer or not. When it is ready, the value will equal CDC_TX_READY,
	* or use macro: mUSBUSARTIsTxTrfReady()
	*/

}//end Exercise_05

/******************************************************************************
* Function:        void BlinkUSBStatus(void)
*
* PreCondition:    None
*
* Input:           None
*
* Output:          None
*
* Side Effects:    None
*
* Overview:        BlinkUSBStatus turns on and off LEDs corresponding to
*                  the USB device state.
*
* Note:            mLED macros can be found in io_cfg.h
*                  usb_device_state is declared in usbmmap.c and is modified
*                  in usbdrv.c, usbctrltrf.c, and usb9.c
*****************************************************************************/
void BlinkUSBStatus(void)
{

}//end BlinkUSBStatus

BOOL Switch2IsPressed(void)
{
	if(sw2 != old_sw2)
	{
		old_sw2 = sw2;                  // Save new value
		if(sw2 == 0)                    // If pressed
			return TRUE;                // Was pressed
	}//end if
	return FALSE;                       // Was not pressed
}//end Switch2IsPressed



/** EOF user.c ***************************************************************/
