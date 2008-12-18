#include <p18f4553.h>
#include <usart.h>
#include <stdio.h>
#include <delays.h>
#include <adc.h>

//#include <pconfig.h>
#define ACCURACY 1000

#pragma config PLLDIV = 1, CPUDIV = OSC1_PLL2, USBDIV = 2
#pragma config FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF
#pragma config PWRT = ON, BOR = OFF, BORV = 3, VREGEN = ON
#pragma config WDT = OFF, WDTPS = 32768
#pragma config MCLRE = OFF, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = ON
#pragma config STVREN = OFF, LVP = OFF, ICPRT = OFF, XINST = OFF, DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF                   // CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                         // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF                // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                            // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF           // CONFIG7L
#pragma config EBTRB = OFF                                                  // CONFIG7H


void main (void)
{
  /* Make all bits on the Port B (LEDs) output bits.
   * If bit is cleared, then the bit is an output bit.
   */
  unsigned char x;
  int input,i,i2;
  double output;
  TRISD = 0;
  TRISA = 0xFF;
  OpenUSART(USART_TX_INT_OFF & 
            USART_RX_INT_OFF & 
            USART_BRGH_HIGH & 
            USART_CONT_RX & 
            USART_EIGHT_BIT & 
            USART_ASYNCH_MODE, 25);
  Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);

  /* Reset the LEDs */
	PORTD = 0xFF;
	
	OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_8_TAD, ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS, ADC_15ANA);
	

	
  while(1)
  {
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	  //printf("asdf\n");
	  //puts("test\r");
	  ConvertADC();
	
	while(BusyADC()) {}
	input = ReadADC();
	output = (double)input * 5.0 / 4096.0;
	
	i = (int) output;
	i2 = (int) ((output-i)*ACCURACY);
	printf("AN0 = %d.%03dV \r", i, i2);
  } 
/*  while(1)
  {
    PORTD = 0;
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	PORTD = 0xFF;
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
  }*/
  /* Light the LEDs */
  //PORTB = 0x5A;
  

  while (1)
    ;
}
