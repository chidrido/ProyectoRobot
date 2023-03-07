#ifndef LIBRERIA_LCD_H
#define	LIBRERIA_LCD_H

#define _XTAL_FREQ 20000000UL

#include <xc.h> // include processor files - each processor file is guarded.  

#define  LCD_PinRS      PORTEbits.RE0
#define  LCD_PinRW      PORTEbits.RE1
#define  LCD_PinEnable	PORTEbits.RE2
#define  LCD_BusDatos	PORTD

char lcd_dato;                              // variable para guardar los datos.
char aux_port;                              // variable para guardar el puerto.
char LCD_GuardaTRISD;
char LCD_GuardaDato;
char LCD_GuardaDatoAux;
int num, num1, num2, num3, num4;

void LCD_EscribeLCD(char comando);

void LCD_EnviaComando(char comandos);

void LCD_Caracter(char datos);

void LCD_CursorIncr();

void LCD_Linea1();

void LCD_Linea2();

void LCD_Linea3();

void LCD_Linea4();

void LCD_PosicionLinea1();

void LCD_PosicionLinea2();

void LCD_OFF();

void LCD_CursorON();

void LCD_CursorOFF();

void LCD_Borra();

void LCD_2Lineas4Bits5x7();

void LCD_Iniciliza();


#endif	/* XC_HEADER_TEMPLATE_H */

