/*
 * File:   spi_pic18f.c
 * Author: 
 */
#include <xc.h>
#include "HardwareConfig.h"
#ifdef __PIC18F4520__
        #include <pic18f4520.h>
#endif
#ifdef __PIC18F4620__
#include <p18f4620.h>
#endif
//#include <GenericTypeDefs.h>
#include "spi_pic18f.h" 

void SPI_Init(void){
TRIS_SCK = 0; TRIS_SDO = 0; TRIS_SDI = 1; TRIS_SS = 0;
SSPCON1bits.SSPEN=1;   // Enable SPI port

 
SSPSTAT = 0xC0; 
//SSPSTATbits.RW=1;
//SSPSTATbits.S=1;
 

SSPCON1 = 0x21;
//SSPCON1bits.SSPM0=1;
//SSPCON1bits.SSPEN=1;
 
//bit 3-0 SSPM3:SSPM0: Synchronous Serial Port Mode Select bits
//0101 = SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin
//0100 = SPI Slave mode, clock = SCK pin, SS pin control enabled
//0011 = SPI Master mode, clock = TMR2 output/2
//0010 = SPI Master mode, clock = F OSC /64
//0001 = SPI Master mode, clock = F OSC /16
//0000 = SPI Master mode, clock = F OSC /4
  
}

void SPI_Close(void){
SSPCON1 &= 0xDF;
}

void SPI_Write(unsigned char data){    
////SSPCON1bits.WCOL = 0;//Write Collision Detect bit
SSPBUF = data;
while(!SSPSTATbits.BF);  
data = SSPBUF;
}

unsigned char SPI1_Read(void){    
SSPBUF = 0x00;
while(!SSPSTATbits.BF);
return SSPBUF; 
}

void SPI_mode(unsigned char CPOL,unsigned char CPHA,unsigned char sample)   
{
 SSPCON1bits.CKP=CPOL; SSPSTATbits.CKE=1-CPHA;
 SSPSTATbits.SMP=sample;
}

void SPI_master(unsigned char clock)  
{
 SSPCON1 = (SSPCON1 & 0xF0) | clock;
}

// Set SPI port as slave.  
// ss=0 -> no dedicated SS pin, 
// ss=1 -> dedicated SS pin (RA5 in PIC18F4520)
void SPI_slave(unsigned char ss)  
{
 ss=1-ss; ss = ss+4;
 SSPCON1 = (SSPCON1 & 0xF0) | ss;
}


/*
unsigned char SPI_transf(unsigned char x)   // basic SPI transfer
{
SSPBUF = x;  while(SSPSTATbits.BF==0);  return(SSPBUF);
}

*/