/*
 * File:   main.c
 * Author: Lion
 * Description:  PIC 18F4xxx  + NRF24L01 MODE RX 
 * Created on November 15, 2018, 8:53 AM
 */

#include <xc.h>
#include "HardwareConfig.h"
#ifdef __PIC18F4520__
#include <pic18f4520.h>
#endif
#ifdef __PIC18F4620__
#include <p18f4620.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spi_pic18f.h"
#include "nrf24l01.h"
#include "time_delay.h"
#include "uart.h"

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
unsigned char bufferRX[32];
unsigned char bufferRX_TMP[32];
OSCCON = 0b01110000;
OSCTUNEbits.PLLEN = 1; // turn on the PLL 64 MHz
//ANSELA = 0; ANSELB = 0; ANSELC = 0; ANSELD = 0; ANSELE = 0;
PORTA=PORTB=PORTC=PORTD=PORTE=0;
TRISA=TRISB=TRISC=TRISD=TRISE=0;
UARTInit(); 
UART_String((char *)" PIC 18F4xxx  + NRF24L01 MODE RX \r\n");  
SPI_Close();
SPI_Init();
NRF24L01_Init(RX_MODE, 0x40); 
while(1)
  {
    while(NRF24L01_DataReady()){}
    NRF24L01_ReadData(bufferRX);
    PORTA = bufferRX[0];
    if((bufferRX[0]!=0) && (bufferRX!=bufferRX_TMP)){
    UART_String((char *)bufferRX);
    strcpy(bufferRX_TMP,bufferRX);
   }
  }
while(1);
return;
}
