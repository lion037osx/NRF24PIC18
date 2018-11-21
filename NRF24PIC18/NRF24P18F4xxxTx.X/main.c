/*
 * File:   main.c
 * Author: Lion
 * Description:  PIC 18F4xxx  + NRF24L01 MODE TX 
 * Created on November 15, 2018, 8:53 AM
 */
#include <xc.h>
#include "HardwareConfig.h"
#if defined (__PIC18F4520__)
    #include <pic18f4520.h>
#endif
#if defined (__PIC18F4620__)
    #include <p18f4620.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spi_pic18f.h"
#include "nrf24l01.h"
#include "time_delay.h"
#include "uart.h"
#include "adc.h"

//#pragma config  WDTPS = 128
#pragma config OSC = XT, FCMEN = OFF, IESO = OFF                       // CONFIG1H
#pragma config PWRT = OFF, BOREN = OFF, BORV = 0                        // CONFIG2L
#pragma config WDT = OFF, WDTPS = 32768                                    // CONFIG2H
#pragma config MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = PORTC       // CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF							      // CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF                   // CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                         // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF                // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                            // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF           // CONFIG7L
#pragma config EBTRB = OFF      

void main(void) {
unsigned char i;
char bufferTmp[32];
unsigned char bufferTX[32];

OSCCON = 0b01110000;
OSCTUNEbits.PLLEN = 1; // turn on the PLL 64 MHz
//ANSELA = 0; ANSELB = 0; ANSELC = 0; ANSELD = 0; ANSELE = 0;
PORTA=PORTB=PORTC=PORTD=PORTE=0;
TRISA=TRISB=TRISC=TRISD=TRISE=0;
UARTInit();
UART_String((char *)"\r\nPIC 18F4xxx + NRF24L01 MODE Tx\r\n");  
ADC_Init();
SPI_Close();
SPI_Init();
NRF24L01_Init(TX_MODE, 0x40); 
while(1)
  {
   bufferTX[0] = 1;   
   for(i = 0; i < 8; i++)
      {
       NRF24L01_SendData(0x40); 
       //NRF24L01_SendData(bufferTX); 
       sprintf(bufferTmp, "Sending: %03d\r\n", bufferTX[0]);
       UART_String(bufferTmp);
       bufferTX[0] = bufferTX[0] << 1;
       Delay_ms(300);  
      }
   bufferTX[0] = 128;
   for(i = 0; i < 6; i++)
      {
       bufferTX[0] = bufferTX[0] >> 1;
       NRF24L01_SendData(0x40); 
       //NRF24L01_SendData(bufferTX); 
       sprintf(bufferTmp, "Sending: %03d\r\n", bufferTX[0]);
       UART_String(bufferTmp);
       Delay_ms(300);  
      }
   //PORTAbits.RA1=~PORTAbits.RA1;
   LATAbits.LA1=~LATAbits.LA1;
  }
while(1);
return;
}
