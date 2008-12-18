using System;
using System.Collections.Generic;
using System.Text;

namespace APD
{
    public class Constants
    {
        public const uint PACKET_SIZE = 65; // 64 + leading 0
        //public const uint USB_REPORTLENGTH = 64;

        //
        public const ushort MChipVendorID = 0x04D8;
        public const ushort Pk2DeviceID = 0x0055;
        //
        public enum AltBoardUSB
        {
            found,              // implies firmware version is good.
            notFound,
            writeError,
            readError,
            firmwareInvalid,
            bootloader
        };
        
        // COMMUNICATIONS PROTOCOL
        public const byte NO_OPERATION = 0x5A;
        public const byte GET_FIRMWARE_VERSION = 0x76;
        public const byte DISABLE_BUZZER = 0xAA;
        public const byte ENABLE_BUZZER = 0xAB;
        public const byte RESET = 0xAC;
        public const byte END_OF_BUFFER = 0xAD;
        public const byte READ_EEPROM = 0xAE;
        public const byte WRITE_EEPROM = 0xAF;
        public const byte READ_INT_EE = 0xB0;
        public const byte WRITE_INT_EE = 0xB1;

    }
        
}
