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
        private uint flightDatasetCount;

        public string testContents()
        {
            //string r = "";
            return flights[0].ToString();
            //return r;
        }

        public void parseEEPROM(byte[] eeprom)
        {
            /* little-endian format in eeprom */
            /*
             * [dataSetCount]
             * 
             * ['A']['P']['D']
             * [frequencyL][frequencyH]
             * [dataPointCountL][dataPointCount][dataPointCount][dataPointCountH]
             * [dataPointL][dataPointH]
             * ...
             */
            int pointer = 1;
            UInt32 dataPointCount;
            //byte[] dataPoints;
            
            if(eeprom.Length < 2)
                return;     //handle better?

            if (!BitConverter.IsLittleEndian)
                throw new Exception("Processor not little endian architecture");
            
            //get dataset count
            flightDatasetCount = eeprom[0];

            flights = new FlightDataSet[flightDatasetCount];
            
            for (uint i = 0; i < flightDatasetCount; i++)
            {
                uint[] dataPoints;
                flights[i] = new FlightDataSet();
                //check for start bytes
                if (eeprom[pointer] != 'A' || eeprom[pointer + 1] != 'P' || eeprom[pointer + 2] != 'D')
                    return; //handle bad data better
                pointer += 3;

                //read frequency in Hz
                frequency = BitConverter.ToUInt16(eeprom, pointer);
                pointer += 2;

                //read number of datapoints
                dataPointCount = BitConverter.ToUInt32(eeprom, pointer);
                pointer += 4;
                dataPoints = new uint[dataPointCount];

                for (int j = 0; j < dataPointCount; j++)
                {
                    dataPoints[j] = BitConverter.ToUInt16(eeprom, pointer);
                    pointer += 2;
                }
                //Array.Copy(eeprom, pointer, dataPoints, 0, dataPointCount * 2);

                //load up datapoints into the structure
                flights[i].loadData(frequency, dataPoints);
            }
        }
    }
}
