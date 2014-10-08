/*********************************************************************
 *
 *                Microchip USB C18 Firmware
 *
 *********************************************************************
 * FileName:        user.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 3.11+
 * Company:         
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <i2c.h>
#include <timers.h>
#include <pwm.h>
#include "system\typedefs.h"

#include "system\usb\usb.h"

#include "io_cfg.h"             // I/O pin mapping
#include "user\user.h"
#include "user\i2c_eeprom.h"

/** V A R I A B L E S ********************************************************/
#pragma udata	USB_Buffers
char inbuffer[BUF_SIZE];            				// input to USB device buffer
char outbuffer[BUF_SIZE];            				// output to USB device buffer

#pragma udata
byte old_sw1,old_sw2;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void BlinkUSBStatus(void);
BOOL Switch1IsPressed(void);
BOOL Switch2IsPressed(void);
void ControlBuzzer(BOOL on);
void USBHIDTxBlocking(void);
void WriteInternalEEPROM(unsigned char *usbindex);
void ReadInternalEEPROM(unsigned char *usbindex);
void SendFWVersionUSB(void);
//void ReadEE(unsigned char *usbindex);
void ReadEE(unsigned char *usbindex);
void WriteEE(unsigned char *usbindex);
void WriteInternalEEPROM(unsigned char *usbindex);
void ReadInternalEEPROM(unsigned char *usbindex);
unsigned char Int_EE_ReadByte(unsigned char byte_address);
void Int_EE_WriteByte(unsigned char byte_address, unsigned char write_byte);
                       

//void Emulate_Mouse(void);

/** D E C L A R A T I O N S **************************************************/
#pragma code
void UserInit(void)
{
    mInitAllLEDs();
    mInitAllSwitches();
    old_sw1 = sw1;
    old_sw2 = sw2;
    
    // PWM stuff for buzzer
    OpenTimer2(TIMER_INT_OFF & T2_PS_1_16);
	SetDCPWM1(0);
	OpenPWM1(255);
	
	// I2C stuff for EEPROM, SSPADD=119,slew_off for 100kHz operation
    SSPADD = 119;
    OpenI2C(MASTER, SLEW_OFF);
}//end UserInit

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
	unsigned char usb_idx = 0;		// index of USB buffer
    unsigned char usb_data = 0;
    unsigned char asm_temp1;
    
    BlinkUSBStatus();
    
    // User Application USB tasks
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    
    if (HIDRxReport(inbuffer, 64) > 0)
    {
        usb_data = 1;
    }
    
    if (usb_data)  // USB receive buffer has data
	{
		do 
		{
			asm_temp1 = inbuffer[usb_idx];
			switch(asm_temp1)        // parse buffer for commands			
			{
				case NO_OPERATION:          // Do nothing
                    // format:      0x5A
                    usb_idx++;
                    break;
                case GET_FIRMWARE_VERSION:			// Get firmware version
					// format: 		0x76
					// response:	<major><minor><dot>
					SendFWVersionUSB();
                    usb_idx++;
                    break;
                case END_OF_BUFFER: //0xAD
                    usb_idx = 64;
                    break;
                case DISABLE_BUZZER:
                	usb_idx++;
                	ControlBuzzer(FALSE);
                	break;
                case ENABLE_BUZZER:
                	usb_idx++;
                	ControlBuzzer(TRUE);
                	break;
                case RESET:
                    // format:      0xAE
					// response:	-
                    Reset();
                    usb_idx++;
                    break;
                case READ_EEPROM:
                	usb_idx++;
                	ReadEE(&usb_idx);
                	break;
                case WRITE_EEPROM:
                	usb_idx++;
                	WriteEE(&usb_idx);
                	break;
                case READ_INT_EE:
                	usb_idx++;
                	ReadInternalEEPROM(&usb_idx);
                	break;
                case WRITE_INT_EE:
                	usb_idx++;
                	WriteInternalEEPROM(&usb_idx);
                	break;
                
                	
                
                default:
                    /*if (asm_temp1 < 0xA0)  // min command
                    {
                        usb_idx = 64;
                        break;
                    }
                    if (asm_temp1 > 0xB9)  // max command
                    {
                        usb_idx = 64;
                        break;
                    }*/
                    usb_idx = 64;          // unknown command so exit loop
                    break;
                    
			}
			
		}while (usb_idx < 64);
	}

}//end ProcessIO





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
    static word led_count=0;

    if(led_count == 0)led_count = 10000U;
    led_count--;

    #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
    #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
    #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
    #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}

    if(UCONbits.SUSPND == 1)
    {
        if(led_count==0)
        {
            mLED_1_Toggle();
            mLED_2 = mLED_1;        // Both blink at the same time
        }//end if
    }
    else
    {
        if(usb_device_state == DETACHED_STATE)
        {
            mLED_Both_Off();
        }
        else if(usb_device_state == ATTACHED_STATE)
        {
            mLED_Both_On();
        }
        else if(usb_device_state == POWERED_STATE)
        {
            mLED_Only_1_On();
        }
        else if(usb_device_state == DEFAULT_STATE)
        {
            mLED_Only_2_On();
        }
        else if(usb_device_state == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                mLED_1_Toggle();
                mLED_2_Off();
            }//end if
        }
        else if(usb_device_state == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                mLED_1_Toggle();
                mLED_2 = !mLED_1;       // Alternate blink
            }//end if
        }//end if(...)
    }//end if(UCONbits.SUSPND...)

}//end BlinkUSBStatus

BOOL Switch1IsPressed(void)
{
    if(sw1 != old_sw1)
    {
        old_sw1 = sw1;                  // Save new value
        if(sw1 == 0)                    // If pressed
            return TRUE;                // Was pressed
    }//end if
    return FALSE;                       // Was not pressed
}//end Switch1IsPressed

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


void ControlBuzzer(BOOL on)
{
	/*
	OpenTimer2(TIMER_INT_OFF & T2_PS_1_16);
	SetDCPWM1(0);
	OpenPWM1(255);*/
	if(on)
		SetDCPWM1(800);
	else
		SetDCPWM1(0);
}	

/******************************************************************************
 * Function:        void USBHIDTxBlocking(void)
 *
 * Overview:        blocking USB transmission
 *
 * PreCondition:    None
 *
 * Input:           outbuffer
 *
 * Output:          Transmits HID Tx report with data.
 * 
 * Side Effects:    None
 *
 * Note:            
 *****************************************************************************/
void USBHIDTxBlocking(void)
{
    while(mHIDTxIsBusy()){}         // blocking
    HIDTxReport(outbuffer, 64);
    USBDriverService();
}

void ReadInternalEEPROM(unsigned char *usbindex)
{
    unsigned int i, numbytes;
    unsigned char ee_address;

    ee_address = inbuffer[(*usbindex)++];   // starting address.
    numbytes = inbuffer[(*usbindex)++] & 0xFF;   // i= # bytes data (length)

    if (numbytes  > 32)     // more than allowed # bytes
    {
        numbytes = 32;
    }
    if (numbytes == 0)
    {
        return;
    }

    for (i = 0; i < numbytes; i++)
    {
	    outbuffer[i] = Int_EE_ReadByte(ee_address++);
    }

    // transmit data
    USBHIDTxBlocking();
} 

/******************************************************************************
 * Function:        void WriteInternalEEPROM(unsigned char *usbindex)
 *
 * Overview:        Writes a given # of bytes into the internal MCU EEPROM.
 *
 * PreCondition:    None
 *
 * Input:           *usbindex - index to start address of data in USB buffer
 *
 * Output:          Internal EEPROM - updated with new data
 *
 * Side Effects:    None
 *
 * Note:            If the length byte is > 32, only the first 32 bytes are 
 *                  written.
 *****************************************************************************/
void WriteInternalEEPROM(unsigned char *usbindex)
{
    unsigned int i, numbytes;
    unsigned char ee_address;

    ee_address = inbuffer[(*usbindex)++];   // starting address.
    numbytes = inbuffer[(*usbindex)++] & 0xFF;   // i= # bytes data (length)

    if (numbytes  > 32)     // more than allowed # bytes
    {
        numbytes = 32;
    }
    if (numbytes == 0)
    {
        return;
    }

    for (i = 0; i < numbytes; i++)
    {
        Int_EE_WriteByte(ee_address++, inbuffer[(*usbindex)++]);
    }
}

/******************************************************************************
 * Function:        void SendFWVersionUSB(void)
 *
 * Overview:        Sends firmware version over USB.
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Transmits HID Tx report with 3-byte version #.
 *
 * Side Effects:    None
 *
 * Note:            None
 *****************************************************************************/
void SendFWVersionUSB(void)
{
	outbuffer[0] = MAJORVERSION;
	outbuffer[1] = MINORVERSION;
	outbuffer[2] = DOTVERSION;

    // transmit version number    
    USBHIDTxBlocking();

} // end void SendFWVersionUSB(void)

/*void ReadEE(unsigned char *usbindex)
{
    unsigned int ee_address = 0;
    unsigned char block;

    ee_address = inbuffer[(*usbindex)++] << 8;  // address high byte.
    ee_address &= inbuffer[(*usbindex)++];		// address low byte
    block = inbuffer[(*usbindex)++] & 1;		// block byte
	outbuffer[0] = EERandomReadBig(EE_ADDRESS, ee_address, block);
 
    USBHIDTxBlocking();

}*/

void ReadEE(unsigned char *usbindex)
{
	unsigned char i, numbytes;
    unsigned int ee_address = 0;
    unsigned char block;

    ee_address = inbuffer[(*usbindex)++] << 8;  // address high byte.
    ee_address &= inbuffer[(*usbindex)++];		// address low byte
    block = inbuffer[(*usbindex)++];
    numbytes = inbuffer[(*usbindex)++];

	if (numbytes  > 32)     // more than allowed # bytes
    {
        numbytes = 32;
    }
    if (numbytes == 0)
    {
        return;
    }
	EESequentialReadBig(EE_ADDRESS, ee_address, &outbuffer, numbytes, block);			//warning--suspicious pointer conversion???
    /*for (i = 0; i < numbytes; i++)
    {
	    outbuffer[i] = EE_ReadByte(ee_address++);
    }*/

    // transmit data
    USBHIDTxBlocking();
}

void WriteEE(unsigned char *usbindex)
{
	unsigned char i, numbytes;
    unsigned int ee_address = 0;
    unsigned char block;

    ee_address = inbuffer[(*usbindex)++] << 8;  // address high byte.
    ee_address &= inbuffer[(*usbindex)++];		// address low byte
    block = inbuffer[(*usbindex)++];
    numbytes = inbuffer[(*usbindex)++];

	if (numbytes  > 32)     // more than allowed # bytes
    {
        numbytes = 32;
    }
    if (numbytes == 0)
    {
        return;
    }
	EEPageWriteBig(EE_ADDRESS, ee_address, &inbuffer, numbytes, block);
}  

/******************************************************************************
 * Function:        void Int_EE_WriteByte(unsigned char byte_address, unsigned char write_byte)
 *
 * Overview:        Writes value write_byte to the internal EEPROM address byte_address. 
 *
 * PreCondition:    none
 *
 * Input:           byte_address - EEPROM address to be written to
 *                  write_byte - byte value to write to EEPROM
 *
 * Output:          Specified EE byte address is written with given value.
 *
 * Side Effects:    Interrupts are disabled during EE write sequence.
 *
 * Note:            
 *****************************************************************************/
void Int_EE_WriteByte(unsigned char byte_address, unsigned char write_byte)
{
    //BOOL interrupts_on = 0;

    EEADR = byte_address;
    EEDATA = write_byte;
    EECON1 = 0;
    EECON1bits.WREN = 1;

	//if (INTCONbits.GIE == 1)
	//	interrupts_on = 1;
	//INTCONbits.GIE = 0;			// uninterruptable routine

    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;

    //if (interrupts_on == 1)		// turn interrupts back on if enabled.	
	//	INTCONbits.GIE = 1;

    while (EECON1bits.WR == 1); // wait for write to complete
    EECON1 = 0;
}

/******************************************************************************
 * Function:        unsigned char Int_EE_ReadByte(unsigned char byte_address)
 *
 * Overview:        Reads a byte from EEPROM at the given address. 
 *
 * PreCondition:    none
 *
 * Input:           byte_address - EEPROM address to be read from
 *
 * Output:          Returns value of EE byte at byte_address
 *
 * Side Effects:    None.
 *
 * Note:            
 *****************************************************************************/
unsigned char Int_EE_ReadByte(unsigned char byte_address)
{
    EEADR = byte_address;
    EECON1 = 0;
    EECON1bits.RD = 1;
    return EEDATA;

}

/** EOF user.c ***************************************************************/
