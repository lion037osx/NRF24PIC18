#include "p18cxxx.h"
#include "HardwareConfig.h"
#ifdef __PIC18F4520__
    #include <pic18f4520.h>
#endif
#ifdef __PIC18F4620__
    #include <p18f4620.h>
#endif
#include "uart.h"

void UARTInit(void)
{ 
 // Procedimiento que inicializa la comunicacion serie
	// Inicializamos la comunicacion con una velocidad de 9600 bps
	// para ello asignamos un Baud rate de alta velocidad
	// y cargamos el registro SPBRG con 25 en decimal

	SPBRG = 25;
	// Configuramos los pines de salida
	TRISCbits.TRISC6 = 1;
	TRISCbits.TRISC7 = 1;
	
	// Comenzamos con la configuracion de la transmicion
	// modificando el registro de estado de la transmicion TXSTA

	TXSTA = 0b00100100;
	// Configuramos una comunicacion asincronica de 8 bits
	// en alta velocidad

	// Configuramos un generador de baudios de 8 bits
	BAUDCONbits.BRG16 = 0;

	RCSTAbits.SPEN = 1;	// Habilitamos el Port Serial
}


void UARTPutChar(char Dato)
{ // esta funcion envia caracteres por el puerto serie
	PIR1bits.TXIF = 0; 	// Borramos flag de transmision

	TXREG = Dato;		// Enviamos dato
	while(TXSTAbits.TRMT == 0); 	// esperamos a que se termine
								// la transmicion
}

 void UART_String(char * _string){
 while(*_string!=0x00)UARTPutChar(*_string++);
}
 