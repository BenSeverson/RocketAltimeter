    InitializeSystem();
    //while(sw2 == 1){}
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 = 0;
	PORTCbits.RC0 = 0;
	PORTCbits.RC1 = 0;	
	/*while(1)
    {
        USBTasks();         // USB Tasks
        ProcessIO();        // See user\user.c & .h
    }*///end while


	//Exercise_Example();
/*
	OpenTimer2(TIMER_INT_OFF & T2_PS_1_16);
	SetDCPWM1(0);
	OpenPWM1(255);
	while(1)
	{
		if(sw2 == 0)
		{
			SetDCPWM1(800);
			PORTCbits.RC0 = 1;
			PORTCbits.RC1 = 1;
		}
		else
		{
			SetDCPWM1(0);
			PORTCbits.RC0 = 0;
			PORTCbits.RC1 = 0;
		}
	}*/










unsigned char b_write(unsigned char data_out)
{
  SSPBUF = data_out;           // write single byte to SSPBUF
  if ( SSPCON1bits.WCOL )      // test if write collision occurred
   return ( -1 );              // if WCOL bit is set return negative #
  else
  {
    //while( SSPSTATbits.BF );   // wait until write cycle is complete         
    IdleI2C();                 // ensure module is idle
    if ( SSPCON2bits.ACKSTAT ) // test for ACK condition received
    	 return ( -2 );
	else return ( 0 );              // if WCOL bit is not set return non-negative #
  }
}






//while(sw2 == 1){}
if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rstarting i2c\r\n");
		PIR2bits.BCLIF = 0;
		//if(SSPBUF == 0) {}
		SSPSTATbits.BF = 0;
		OpenI2C(MASTER, SLEW_ON);
		SSPADD = 60;


//while(sw2 == 1){}

		if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rI2C opened\r\n");
PORTCbits.RC0 = 0;
PORTCbits.RC1 = 1;
		IdleI2C();
		StartI2C();
		while ( SSPCON2bits.SEN );
		if(PIR2bits.BCLIF)           // test for bus collision
		{
			if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rBus Collision error\r\n");
		}
		else                            // start condition successful
		{
			
			if ( b_write( 0b10100110 ) )    // write byte - R/W bit should be 0
			{
				if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision\r\n");              // set error for write collision
			}

			//IdleI2C();                    // ensure module is idle
			if ( !SSPCON2bits.ACKSTAT )   // test for ACK condition received
			{ 
				if ( b_write( 0 ) )    // address low byte
				{
					if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision1\r\n");              // set error for write collision
				}
				if ( !SSPCON2bits.ACKSTAT ) // test for ACK condition received
				{ 
					if ( b_write( 0 ) )  // write word address for EEPROM
					{
						if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision2\r\n");            // set error for write collision
					}

					//IdleI2C();                  // ensure module is idle
					if ( !SSPCON2bits.ACKSTAT ) // test for ACK condition received
					{ 
						if ( b_write( 55 ) )   // data byte for EEPROM
						{
							if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision3\r\n");          // set error for write collision
						}
					}
					else
					{
						if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rnot ack\r\n");            // return with Not Ack error condition   
					}
				}
			}
			else
			{
				if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rnot ack2\r\n");              // return with Not Ack error condition   
			}
		}

		//IdleI2C();                      // ensure module is idle  
		StopI2C();                      // send STOP condition
		while ( SSPCON2bits.PEN );      // wait until stop condition is over 
		if ( PIR2bits.BCLIF )           // test for bus collision
		{
			if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rBus Collision error\r\n");                // return with Bus Collision error 
		}
		if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\reverything done writing\r\n");
PORTCbits.RC0 = 1;
			PORTCbits.RC1 = 0;
		/////////////////////////////////////////////////////////////////////////////////

		IdleI2C();                      // ensure module is idle
		StartI2C();                     // initiate START condition
		while ( SSPCON2bits.SEN );      // wait until start condition is over 
		if ( PIR2bits.BCLIF )           // test for bus collision
		{
			if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rbus collision\r\n");                // return with Bus Collision error 
		}
		else
		{
			if ( b_write( 0b10100110 ) )    // write 1 byte
			{
				if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision\r\n");              // return with write collision error
			}

			//IdleI2C();                    // ensure module is idle
			if ( !SSPCON2bits.ACKSTAT )   // test for ACK condition, if received
			{
				if ( b_write( 0 ) )  // WRITE word address for EEPROM
				{
					if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision2\r\n");            // return with write collision error
				}
				if ( b_write( 0 ) )  // WRITE word address for EEPROM
				{
					if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision2a\r\n");            // return with write collision error
				}
				//IdleI2C();                  // ensure module is idle
				if ( !SSPCON2bits.ACKSTAT ) // test for ACK condition, if received
				{
					RestartI2C();             // generate I2C bus restart condition
					while ( SSPCON2bits.RSEN );// wait until re-start condition is over 
					if ( PIR2bits.BCLIF )     // test for bus collision
					{
						if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rbus collision2\r\n");          // return with Bus Collision error 
					}

					if ( b_write( 0b10100111 ) )// write 1 byte - R/W bit should be 1
					{
						if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rwrite collision3\r\n");          // return with write collision error
					}

					//IdleI2C();                // ensure module is idle
					if ( !SSPCON2bits.ACKSTAT )// test for ACK condition, if received
					{
						SSPCON2bits.RCEN = 1;       // enable master for 1 byte reception
						while ( SSPCON2bits.RCEN ); // check that receive sequence is over
						NotAckI2C();              // send ACK condition
						while ( SSPCON2bits.ACKEN ); // wait until ACK sequence is over 
						StopI2C();              // send STOP condition
						while ( SSPCON2bits.PEN ); // wait until stop condition is over 
						if ( PIR2bits.BCLIF )   // test for bus collision
						{
							if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rbus collision3\r\n");         // return with Bus Collision error 
						}
					}
					else
					{
						if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rnot ack4\r\n");          // return with Not Ack error
					}

				}
				else
				{
					if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rnot ack5\r\n");            // return with Not Ack error
				}
			}
			else
			{
				if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rnot ack6\r\n");              // return with Not Ack error
			}
		}
		//return ( (unsigned int) SSPBUF );     // return with data
		if(SSPBUF == 55)
		{
			if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rread correct value from eeprom\r\n");
PORTCbits.RC0 = 1;
			PORTCbits.RC1 = 1;
		}
		else
		{
			if(mUSBUSARTIsTxTrfReady()) putrsUSBUSART("\rread different value from eeprom\r\n");
		}
