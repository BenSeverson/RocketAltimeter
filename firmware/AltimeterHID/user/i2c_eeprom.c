#include "user\i2c_eeprom.h"
#include <i2c.h>
#include <p18cxxx.h>

unsigned int EERandomReadBig( unsigned char control, unsigned int address, unsigned char block )
{
  block &= 1;
  // start bit ////////////////////////////////////////////////////////////////
  IdleI2C();                      // ensure module is idle
  StartI2C();                     // initiate START condition
  while ( SSPCON2bits.SEN );      // wait until start condition is over 
  if ( PIR2bits.BCLIF )           // test for bus collision
  {
    return ( -1 );                // return with Bus Collision error 
  }

  // control byte ////////////////////////////////////////////////////////////
  if ( WriteI2C( control | (block << 3) ) )    // write 1 byte
  {
    return ( -3 );              // return with write collision error
  }
  //IdleI2C();                    // ensure module is idle
  if ( SSPCON2bits.ACKSTAT )   // test for ACK condition, if received
  {
    return ( -2 );              // return with Not Ack error
  }
  
  // first address byte ///////////////////////////////////////////////////////
  if ( WriteI2C( address >> 8) )  // WRITE word address for EEPROM
  {
    return ( -3 );            // return with write collision error
  }
  //IdleI2C();                  // ensure module is idle
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition, if received
  {
    return ( -2 );            // return with Not Ack error
  }
  
  // second address byte //////////////////////////////////////////////////////
  if ( WriteI2C( address ) )  // WRITE word address for EEPROM
  {
    return ( -3 );            // return with write collision error
  }
  //IdleI2C();                  // ensure module is idle
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition, if received
  {
    return ( -2 );            // return with Not Ack error
  } 

  // restart bit //////////////////////////////////////////////////////////////
  RestartI2C();             // generate I2C bus restart condition
  while ( SSPCON2bits.RSEN );// wait until re-start condition is over 
  if ( PIR2bits.BCLIF )     // test for bus collision
  {
    return ( -1 );          // return with Bus Collision error 
  }
  
  // control byte /////////////////////////////////////////////////////////////                      
  if ( WriteI2C( ( control | (block << 3) ) | 1 ) )// write 1 byte - R/W bit should be 1
  {
    return ( -3 );          // return with write collision error
  }
  //IdleI2C();                // ensure module is idle
  if ( SSPCON2bits.ACKSTAT )// test for ACK condition, if received
  {
    return ( -2 );          // return with Not Ack error
  } 
  
  // read byte ////////////////////////////////////////////////////////////////  
  SSPCON2bits.RCEN = 1;       // enable master for 1 byte reception
  while ( SSPCON2bits.RCEN ); // check that receive sequence is over
  NotAckI2C();              // send ACK condition
  while ( SSPCON2bits.ACKEN ); // wait until ACK sequence is over 
  
  // stop bit /////////////////////////////////////////////////////////////////
  StopI2C();              // send STOP condition
  while ( SSPCON2bits.PEN ); // wait until stop condition is over 
  if ( PIR2bits.BCLIF )   // test for bus collision
  {
    return ( -1 );         // return with Bus Collision error 
  }
    
  return ( (unsigned int) SSPBUF );     // return with data
}


unsigned char EEPageWriteBig( unsigned char control, unsigned int address, unsigned char *wrptr, unsigned char length, unsigned char block )
{
  block &= 1;
  // write start bit //////////////////////////////////////////////////////////
  IdleI2C();                      // ensure module is idle
  StartI2C();                     // initiate START condition
  while ( SSPCON2bits.SEN );      // wait until start condition is over 
  if ( PIR2bits.BCLIF )           // test for bus collision
  {
    return ( -1 );                // return with Bus Collision error 
  }

  // write control byte ///////////////////////////////////////////////////////
  if ( WriteI2C( control | (block << 3) ) )    // write 1 byte - R/W bit should be 0
  {
    return ( -3 );              // return with write collision error
  }
  //IdleI2C();                    // ensure module is idle
  if ( SSPCON2bits.ACKSTAT )   // test for ACK condition, if received 
  { 
	return ( -2 );              // return with Not Ack error
  }

  // write address ////////////////////////////////////////////////////////////
  if ( WriteI2C( address >> 8 ) )  // write address byte to EEPROM
  {
    return ( -3 );            // return with write collision error
  }
  //IdleI2C();                  // ensure module is idle
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition, if received
  {
    return ( -2 );            // return with Not Ack error
  }  
  if ( WriteI2C( address ) )  // write address byte to EEPROM
  {
    return ( -3 );            // return with write collision error
  }
  //IdleI2C();                  // ensure module is idle
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition, if received
  {
    return ( -2 );            // return with Not Ack error
  }

  // write bytes ////////////////////////////////////////////////////////////// 
  if ( putsI2C_count(wrptr, length) )
  {
    return( -4 );           // bus device responded possible error
  }

  // stop bit /////////////////////////////////////////////////////////////////
  //IdleI2C();                      // ensure module is idle
  StopI2C();                      // send STOP condition
  while ( SSPCON2bits.PEN );      // wait until stop condition is over 
  if ( PIR2bits.BCLIF )           // test for Bus collision
  {
    return ( -1 );                // return with Bus Collision error 
  }
  return ( 0 );                   // return with no error
}

unsigned char EESequentialReadBig( unsigned char control, unsigned int address, unsigned char *rdptr, unsigned char length, unsigned char block )
{
  block &= 1;
  // start bit ////////////////////////////////////////////////////////////////  
  IdleI2C();                      // ensure module is idle
  StartI2C();                     // initiate START condition
  while ( SSPCON2bits.SEN );      // wait until start condition is over 
  if ( PIR2bits.BCLIF )           // test for bus collision
  {
    return ( -1 );                // return with Bus Collision error 
  }
  
  // control byte /////////////////////////////////////////////////////////////
  if ( WriteI2C( control | (block << 3) ) )    // write 1 byte 
  {
    return ( -3 );              // set error for write collision
  }
  //IdleI2C();                    // ensure module is idle
  if ( SSPCON2bits.ACKSTAT )   // test for ACK condition, if received
  {
    return ( -2 );              // return with Not Ack error
  }  
  
  // address bytes ////////////////////////////////////////////////////////////
  if ( WriteI2C( address >> 8 ) ) // WRITE word address to EEPROM
  {
    return ( -3 );            // return with write collision error
  }
  //IdleI2C();                  // ensure module is idle
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition received
  {
    return ( -2 );            // return with Not Ack error
  }
  if ( WriteI2C( address ) )  // WRITE word address to EEPROM
  {
    return ( -3 );            // return with write collision error
  }
  //IdleI2C();                  // ensure module is idle
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition received
  {
    return ( -2 );            // return with Not Ack error
  }
  
  // restart bit //////////////////////////////////////////////////////////////
  RestartI2C();             // generate I2C bus restart condition
  while ( SSPCON2bits.RSEN );  // wait until re-start condition is over 
  
  // control byte /////////////////////////////////////////////////////////////
  if ( WriteI2C( ( control | (block << 3) ) | 1 ) )// WRITE 1 byte - R/W bit should be 1 for read
  {
    return ( -3 );          // set error for write collision
  }    
  //IdleI2C();                // ensure module is idle
  if ( SSPCON2bits.ACKSTAT )// test for ACK condition received
  {
      return ( -2 );          // return with Not Ack error
  }
  
  // get bytes ////////////////////////////////////////////////////////////////      
  if ( getsI2C( rdptr, length ) )// read in multiple bytes
  {
    return ( -1 );        // return with Bus Collision error
  }

  // send not ACK /////////////////////////////////////////////////////////////
  NotAckI2C();            // send not ACK condition
  while ( SSPCON2bits.ACKEN );// wait until ACK sequence is over 
  
  // stop bit /////////////////////////////////////////////////////////////////
  StopI2C();              // send STOP condition
  while ( SSPCON2bits.PEN );// wait until stop condition is over 
  if ( PIR2bits.BCLIF )   // test for bus collision
  {
    return ( -1 );        // return with Bus Collision error 
  }
  
  return ( 0 );                   // return with no error
}


unsigned char EEByteWriteBig( unsigned char control, unsigned int address, unsigned char data, unsigned char block )
{
  block &= 1;
  IdleI2C();                      // ensure module is idle
  StartI2C();                     // initiate START condition
  while ( SSPCON2bits.SEN );      // wait until start condition is over 
  if ( PIR2bits.BCLIF )           // test for bus collision
  {
    return ( -1 );                // return with Bus Collision error 
  }
  
  if ( WriteI2C( control | (block << 3) ) )    // write byte - R/W bit should be 0
  {
    return ( -3 );              // set error for write collision
  }
  //IdleI2C();                    // ensure module is idle
  if ( SSPCON2bits.ACKSTAT )   // test for ACK condition received
  {
    return ( -2 );              // return with Not Ack error condition
  }
  
  if ( WriteI2C( address ) )  // write word address for EEPROM
  {
    return ( -3 );            // set error for write collision
  }
  //IdleI2C();                  // ensure module is idle
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition received
  {
    return ( -2 );            // return with Not Ack error condition   
  }
  
  // ben - added ack test
  if ( WriteI2C( data ) )   // data byte for EEPROM
  {
    return ( -3 );          // set error for write collision
  }
  if ( SSPCON2bits.ACKSTAT ) // test for ACK condition received
  {
    return ( -2 );            // return with Not Ack error condition   
  }

  //IdleI2C();                      // ensure module is idle  
  StopI2C();                      // send STOP condition
  while ( SSPCON2bits.PEN );      // wait until stop condition is over 
  if ( PIR2bits.BCLIF )           // test for bus collision
  {
    return ( -1 );                // return with Bus Collision error 
  }
  return ( 0 );                   // return with no error
}

signed char putsI2C_count( unsigned char *wrptr, unsigned char numbytes )
{
  unsigned char temp;
  unsigned char i;
  for(i=0;i<numbytes;i++)                // transmit data until null character 
  {
	  temp = putcI2C(*wrptr);
	  if (temp ) return ( temp );            // return with write collision error
  	  wrptr ++;                       // increment pointer
  }

  return ( 0 );
}