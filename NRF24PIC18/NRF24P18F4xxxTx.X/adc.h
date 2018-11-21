/* 
 * File:   adc.h
 * Author: optimus
 *
 * Created on October 2, 2018, 12:00 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void compare(unsigned int);
void ADC_Init(void);
unsigned int get_adc(void);
unsigned int ADC_Convert(void);
unsigned int adc_prom(void);
void second(void);
void run();
void print_adc(unsigned int);
void Delay1KTCYx(unsigned char);
void Delay1TCYx(unsigned char);
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

