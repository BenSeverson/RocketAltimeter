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

        public override string ToString()
        {
            string r = "";
            foreach (AltitudePoint a in altitudeData)
            {
                //r += Math.Round(a.time, 3, MidpointRounding.AwayFromZero) + ": " + a.altitude + Environment.NewLine;
                r += String.Format("{0:0.000}", a.time) + ": " + a.altitude + Environment.NewLine;
            }
            return r;
            //return base.ToString();
        }

        public void loadData(int frequency, uint[] values)
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

        public static int ADCtoAltitude(uint ADCvalue)
        {
            double pressure_kPa;
            double voltage;
            int calculated_altitude;
            int altitude;

            //ADC is 10 bit right now so reject out of range
            if (ADCvalue < 0 || ADCvalue > 1023)
                return -1;


            if (ADCvalue == 0)
                voltage = VREF_NEG;
            else
                voltage = ((VREF_POS - VREF_NEG) / 1024) * ADCvalue;

            pressure_kPa = (voltage / VREF_POS + 0.095) / 0.009;

            calculated_altitude = Convert.ToInt32(Math.Round((1 - Math.Pow((pressure_kPa / 101.325), 0.190263)) * (288.15 / 0.00198122), MidpointRounding.AwayFromZero));

            // equation only good to 36k ft
            //if (calculated_altitude > 36019)
            //    return -1;

            // altitude greater than 36019ft or negative
            if (ADCvalue < 112 || ADCvalue > 836)
                return -1;

            altitude = Convert.ToInt32(Constants.ADCALTITUDES[ADCvalue - 112]);

            return altitude;
        }
    }
}
