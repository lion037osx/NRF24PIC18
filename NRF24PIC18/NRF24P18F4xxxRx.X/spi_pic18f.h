/*
 * File:   spi_pic18f.h
 * Author: 
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


#define TRIS_SCK   TRISCbits.TRISC3         
#define TRIS_SDO   TRISCbits.TRISC5
#define TRIS_SDI   TRISCbits.TRISC4
#define TRIS_SS    TRISAbits.TRISA5

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