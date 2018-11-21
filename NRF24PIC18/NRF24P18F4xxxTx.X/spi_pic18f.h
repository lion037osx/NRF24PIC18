/*
 * File:   spi_pic18f.h
 * Author: lion
 */

#ifndef SPI_PIC18F_H
#define	SPI_PIC18F_H

//============================================================================== 
//*GND                       *GND
//*RC2/pin36/RST             *GND
//*RC1/pin35/WAKE/nrf24-CSN            *VDD
//*RB0/INT0/pin8/INT         *NC
//*RC5/pin43/SDO             *RC0/pin32/CS/nrf24-CE
//*RC3/pin37/SCK             *RC4/pin42/SDI
//==============================================================================
//==============================================================================

#define TRIS_SCK1   TRISCbits.TRISC3 //pin37 (tqfp44)        
#define TRIS_SDO1   TRISCbits.TRISC5 //pin43 (tqfp44)
#define TRIS_SDI1   TRISCbits.TRISC4 //pin42 (tqfp44)
#define TRIS_SS1    TRISAbits.TRISA5 //pin24 (tqfp44)

// SPI functions aliases
#define spi_tx(x)   SPI_transf(x)      // sends TX data, ignores return value.
#define spi_rx()    SPI_transf(0xFF)   // sends dummy data, returns RX data.
#define spi_clock() SPI_transf(0xFF)   // send 8 clocks (nobody cares about the data)

void SPI_Init(void);
void SPI_Close(void);
void SPI_Write(unsigned char data);
unsigned char SPI1_Read(void);
void SPI_mode(unsigned char,unsigned char,unsigned char);
void SPI_master(unsigned char);  
void SPI_slave(unsigned char);
//unsigned char SPI_transf(unsigned char);

#endif	/* SPI_PIC18F_H */