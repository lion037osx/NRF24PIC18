/*
 * File:   time_delay.c
 * Author: lions
 */
#include <xc.h>
#include "time_delay.h"
#define _XTAL_FREQ 4000000 // Select your XTAL
//#define _XTAL_FREQ 64000000 

void Delay_ms(unsigned int count){
unsigned int i;
for(i = 0; i < count; i++){
__delay_ms(1);
}
}

void Delay_us(unsigned int count){
unsigned int i;
for(i = 0; i < count; i++){
__delay_us(1);
}
}