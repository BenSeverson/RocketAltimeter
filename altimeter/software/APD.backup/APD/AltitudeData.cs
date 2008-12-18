using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace APD
{
    struct AltitudePoint
    {
        public double time;
        public int altitude;
    }

    class FlightDataSet
    {
        private const double VREF_POS = 5.0;
        private const double VREF_NEG = 0.0;

        private AltitudePoint[] altitudeData;
        private int frequency;
        private string name;
        private string rocketName;
        private string motor;
        private DateTime flightDate;

        public void loadData(int frequency, int[] values)
        {
            if (frequency <= 0)
                return; // error handle this

            AltitudePoint[] output = new AltitudePoint[values.Length];
            double period = 1.0 / frequency;
            double timeCounter = 0.0;

            for (int i = 0; i < values.Length; i++)
            {
                output[i].altitude = ADCtoAltitude(values[i]);
                output[i].time = timeCounter;
                timeCounter += period;
            }

            altitudeData = output;
        }

        public static int ADCtoAltitude(int ADCvalue)
        {
            double pressure_kPa;
            int altitude;

            //ADC is 10 bit right now so reject out of range
            if (ADCvalue < 0 || ADCvalue > 1023)
                return -1;


            if (ADCvalue == 0)
                pressure_kPa = VREF_NEG;
            else
                pressure_kPa = (VREF_POS - VREF_NEG) / (1024 * ADCvalue);

            altitude = Convert.ToInt32((1 - Math.Pow((pressure_kPa / 101.325), 0.190263)) * (288.15 / 0.00198122));

            // equation only good to 36k ft
            if (altitude > 36019)
                return -1;

            return altitude;
        }
    }
}
