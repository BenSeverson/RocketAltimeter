#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H


unsigned int EERandomReadBig( unsigned char control, 
							  unsigned int address, 
							  unsigned char block );
							  
unsigned char EEPageWriteBig( unsigned char control,
                              unsigned int address,
                              unsigned char *wrptr,
                              unsigned char length,
                              unsigned char block  );
                           
unsigned char EEByteWriteBig( unsigned char control,
                              unsigned int address,
                              unsigned char data, 
                              unsigned char block );
                           
unsigned char EESequentialReadBig( unsigned char control,
                                   unsigned int address,
                                   unsigned char *rdptr,
                                   unsigned char length,
                                   unsigned char block  );
                                  
signed char putsI2C_count( unsigned char *wrptr, unsigned char numbytes ) ;                                  
                                   
#endif //I2C_EEPROM_H
                                    