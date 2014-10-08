using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace APD
{
    class EEPROM
    {
        private FlightDataSet[] flights;
        private UInt16 frequency;
        private UInt16 deployAltitude1;
        private UInt16 deployAltitude2;
        private int flights;

        public void parseEEPROM(byte[] eeprom)
        {
            if (eeprom.Length == 0)
                return;
            BitConverter.ToInt16

        }
    }
}
