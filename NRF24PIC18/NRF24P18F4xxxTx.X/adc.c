#include <xc.h>
#include "p18cxxx.h"
#include "HardwareConfig.h"

#if defined (__PIC18F4520__)
    #include <pic18f4520.h>
#endif
#if defined (__PIC18F4620__)
    #include <p18f4620.h>
#endif
//#include <timers.h>
//#include <delays.h>
#include <GenericTypeDefs.h>
#include "uart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"

float f_value_adc=0.0;
unsigned int ui_value_adc=0;

void Delay1KTCYx(unsigned char unit)
{
	do {
		_delay(1000);
	} while(--unit != 0);
}

void Delay1TCYx(unsigned char unit)
{
	do {
		_delay(1);
	} while(--unit != 0);
}

void ADC_Init(void){
    
    ADCON1=0b00001010;//channel 3 1011 -channel4 1010
    //ADCON2=0b10100100;
    ADCON2=0b10111100;
    
/*
 * ADCON2
*
*   bit 5-3 ACQT2:ACQT0: A/D Acquisition Time Select bits
*
111 = 20 T AD
110 = 16 T AD
101 = 12 T AD
        100 = 8 T AD
        011 = 6 T AD
        010 = 4 T AD
        001 = 2 T AD
        000 = 0 T AD (1)
*
*   bit 2-0 ADCS2:ADCS0: A/D Conversion Clock Select bits
* 
*   111 = F RC (clock derived from A/D RC oscillator) (1)
*   110 = F OSC /64
*   101 = F OSC /16
*   100 = F OSC /4
*   011 = F RC (clock derived from A/D RC oscillator) (1)
*   010 = F OSC /32
*   001 = F OSC /8
*   000 = F OSC /2
* 
*/

    //ADCON0=0b00001101;//channel 3
      ADCON0=0b00010001;//channel 4
    
}

unsigned int ADC_Convert(void)
{ 
    unsigned int value_adc_tmp;
    ADCON0bits.GO_DONE=1;            
    while (ADCON0bits.GO_DONE == 1); 
    value_adc_tmp=ADRESL;
    value_adc_tmp|=(ADRESH<<8);
    return(unsigned int)(value_adc_tmp);
}




unsigned int adc_prom(void){
    unsigned int adc_tmp;
    int i=100;
    //while(i--)adc_tmp+=(unsigned int)ADC_Convert();         
    adc_tmp=(unsigned int)ADC_Convert();         
    //adc_tmp=(unsigned int)adc_tmp/100;
    return adc_tmp;
}



unsigned int get_adc(void){
    unsigned int adc=0;
    adc=(unsigned int)ADC_Convert();
    return adc;
}

void second(void){
    UINT16 x=10;        
    while(x--)Delay1KTCYx(1000);  
}


void compare(unsigned int value){
    static unsigned int memory_tmp=0;
    char buffer[40];

    if(memory_tmp!=value){                    
            sprintf(buffer,"adc %d\r\n",value);
            UART_String(buffer);               
            memory_tmp=value;
        }
    else {
        return;
    }    
}

void print_adc(unsigned int value){
char buffer[32];
    sprintf(buffer,"adc %d\r\n",value);
    UART_String(buffer);               
}            

void run(){
unsigned int adc;
unsigned int adc_buffer[64];
unsigned int count=1;
unsigned char flag_adc=0;
while(1){
    adc=(unsigned int)ADC_Convert();
    while( adc>0)
    {
        adc_buffer[count]=adc;
        adc=(unsigned int)ADC_Convert();    
        count++;
        flag_adc=1;
        LATAbits.LATA0=1;
    }
    if(flag_adc==1){       
        while(count){
                print_adc(adc_buffer[count]);
                flag_adc=0;
                count--;
            }
            LATAbits.LATA0=0;             
        }
    }
}