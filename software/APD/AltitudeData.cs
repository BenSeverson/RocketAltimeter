using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using ZedGraph;

namespace APD
{
    struct AltitudePoint
    {
        public double time;
        public int altitude;
    }

    class FlightDataSet
    {
        // part of board design - positive and negative references for the ADC
        // might change in future for better results - need to rev board
        private const double VREF_POS = 5.0;
        private const double VREF_NEG = 0.0;

        private AltitudePoint[] myAltitudeData;
        public AltitudePoint[] altitudeData
        {
            get
            {
                return myAltitudeData;
            }
        }
        private int frequency;
        private string name;
        private string rocketName;
        private string motor;
        private DateTime flightDate;

        public override string ToString()
        {
            string r = "";
            foreach (AltitudePoint a in myAltitudeData)
            {
                //r += Math.Round(a.time, 3, MidpointRounding.AwayFromZero) + ": " + a.altitude + Environment.NewLine;
                r += String.Format("{0:0.000}", a.time) + ": " + a.altitude + Environment.NewLine;
            }
            return r;
            //return base.ToString();
        }

        public void loadData(int frequency, uint[] values)
        {
            // just check for 0 frequency right now - might check for valid frequencys later
            if (frequency < 1)
                throw new Exception("Bad frequency: " + frequency);

            AltitudePoint[] output = new AltitudePoint[values.Length];
            double period = 1.0 / frequency;
            double timeCounter = 0.0;

            for (int i = 0; i < values.Length; i++)
            {
                output[i].altitude = ADCtoAltitude(values[i]);
                output[i].time = timeCounter;
                timeCounter += period;
            }

            myAltitudeData = output;
        }

        public static int ADCtoAltitude(uint ADCvalue)
        {
            double pressure_kPa;
            double voltage;
            int calculated_altitude;
            int altitude;

            //ADC is 10 bit right now so reject out of range
            if (ADCvalue < 0 || ADCvalue > 1023)
                throw new Exception("Attempted to convert bad ADC value to altitude: " + ADCvalue);

            //if (ADCvalue == 0)
            //    voltage = VREF_NEG;
            //else
            //    voltage = ((VREF_POS - VREF_NEG) / 1024) * ADCvalue;
            voltage = ((VREF_POS - VREF_NEG) / 1024) * ADCvalue;

            pressure_kPa = (voltage / VREF_POS + 0.095) / 0.009;
            
            // calculated altitude not used right now
            calculated_altitude = Convert.ToInt32(Math.Round((1 - Math.Pow((pressure_kPa / 101.325), 0.190263)) * (288.15 / 0.00198122), MidpointRounding.AwayFromZero));

            // equation only good to 36k ft
            if (calculated_altitude > 36019)
                throw new Exception("Calculated an altitude greater than 36019 ft");

            // altitude greater than 36019ft or negative
            if (ADCvalue < 112 || ADCvalue > 836)
                throw new Exception("Calculated an altitude greater than 36019 ft or negative");

            // look up altitude from table that matches table in firmware
            altitude = Convert.ToInt32(Constants.ADCALTITUDES[ADCvalue - 112]);

            return altitude;
        }

        public void getTimeAltitudes(ref Double[] times, ref Double[] altitudes)
        {
            times = new Double[myAltitudeData.Length];
            altitudes = new Double[myAltitudeData.Length];

            for (int i = 0; i < myAltitudeData.Length; i++ )
            {
                times[i] = myAltitudeData[i].time;
                altitudes[i] = myAltitudeData[i].altitude;
            }
        }
    }
}
