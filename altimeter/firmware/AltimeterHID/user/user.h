/*********************************************************************
 *
 *                Microchip USB C18 Firmware
 *
 *********************************************************************
 * FileName:        user.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 ********************************************************************/

#ifndef USER_H
#define USER_H

/** D E F I N I T I O N S ****************************************************/
#define MAJORVERSION    1
#define MINORVERSION    0
#define DOTVERSION      0

#define BUF_SIZE        64			// USB buffers

#define EE_ADDRESS			0xA6	// address of EEPROM on I2C bus


/** C O M M A N D S **********************************************************/
#define	NO_OPERATION			0x5A		// does nothing	 
#define GET_FIRMWARE_VERSION    0x76 	    // Get firmware version number

#define DISABLE_BUZZER			0xAA
#define ENABLE_BUZZER			0xAB

#define RESET               	0xAC
#define END_OF_BUFFER       	0xAD

#define READ_EEPROM				0xAE
#define WRITE_EEPROM			0xAF

#define READ_INT_EE				0xB0
#define WRITE_INT_EE			0xB1



/** P U B L I C  P R O T O T Y P E S *****************************************/
void UserInit(void);
void ProcessIO(void);

#endif //USER_H
