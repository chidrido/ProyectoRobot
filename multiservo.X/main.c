/*
 * File:   main.c
 * Author: Pablo
 * /////////////////////////// Control de Servomotores ///////////////////////////
 * Para el control de 8 servomotores de manera independiente se ha utilizado la siguiente solucion
 * Usando una terrupcion por desbordamiento del TMR0 se consigue obtener un tren de pulsos de 2,5ms.
 * Como se necesita 20 ms para poder mover los motores Futaba se requieren 8 ciclos de 2,5 ms, entonces con la ayuda del contador_servo
 * contamos dichos 8 ciclos, cada uno correspondiente a un servo, seguidamente se  llama a la funcion temporizaciones la cual se encarga
 * de asignarle su respectivo dutty cycle con el TMR1.  
 *
 * Created on 7 de febrero de 2023, 19:46
 */
#pragma config PLLDIV = 2, CPUDIV = OSC1_PLL2, USBDIV = 2
#pragma config FOSC = HS, FCMEN = OFF, IESO = OFF
#pragma config PWRT = OFF, BOR = OFF, BORV = 3, VREGEN = OFF
#pragma config WDT = OFF
#pragma config WDTPS = 32768
#pragma config CCP2MX = OFF, PBADEN = OFF, LPT1OSC = OFF, MCLRE = ON
#pragma config STVREN = OFF, LVP = OFF, ICPRT = OFF, XINST = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
#pragma config CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
#pragma config EBTRB = OFF

//#define _XTAL_FREQ 20000000
#include <xc.h>
#include <stdio.h>

#include "FuncionesMultiservo.c"
#include "Libreria_LCD.h"
#include "uart.h"

///////////////////////////////  Varibales /////////////////////////////////////

#define     S1	    LATBbits.LB4
#define		S2	    LATBbits.LB5
#define		S3	    LATBbits.LB6
#define		S4	    LATBbits.LB7

char contador_servos;
char servo_bit;

void mensajeInicial(){
    LCD_Caracter('R');
    LCD_Caracter('o');
    LCD_Caracter('b');
    LCD_Caracter('o');
    LCD_Caracter('t');
    LCD_Caracter(' ');
    LCD_Caracter('Z');
    LCD_Caracter('o');
    LCD_Caracter('w');
    LCD_Caracter('i');
}

/*////////////////////////////////// Main //////////////////////////////////////
 * Para un cristal de 20Mz, segun el datasheet se necesitan 16 Tocs
 * 1/20MZ = 50 ns.
 * 16Tosc = 16 x 50ns = 0.8us
 * El tiempo minimo de conversion debe ser mayor de 2.45us.
 * 0.8 x TAD = 0.8us x 6 = 2.86us > 2.45us
*/
void main(){        
    LCD_Iniciliza();
    Uart_Init(9600);
    
    ADCON1bits.PCFG = 0b1111;
    INTCON2bits.nRBPU = 0;                          // Habilita el modo nRBPU en el Puerto B.
    TRISB = 0x0F;                                   // Puerto B como salida para motores.
    LATB = 0xF0;
     
    T0CON = 0b00000000;                             // Configuracion de TMR0, Preescaler de 2 para conseguir 2,5 ms.
    INTCONbits.GIE = 1;                             // Habilita interrupcion General.
    INTCONbits.TMR0IE = 1;                          // Activa interrupcion por desbordamiento del TMR0.  
    T0CONbits.TMR0ON = 1;                           // Activa TMR0.     
    
    mensajeInicial();
    
    contador_servos = 0;
    borraPosiciones();
    posicionInicial();
    
    Uart_Send_String("Robot zowi\r\n");
    ////////////////////////////  Zona de codigo ///////////////////////////////
    while(1) {
        
        if (PORTBbits.RB0 == 0) {
            andar();
            
        }else{
            borraPosiciones();
        }
    }
}

/*//////////////////////// Temporizaciones TMR1 ////////////////////////////////
 * En teoria debe haber 90 posiciones, 180º/90 = 2º. Para mover cada grado se necesita un incremento de 0.02222222222 ms.
 * El temporizador de 0.5 ms corresponden a un intervalo donde el servo no responde 
 * 
 * CARGA_50us  = 65536 - Tms/[(4/Fosc)*Pre] = 65536 - 0.5/[(4/20000)*1] = 63036
 * Pre = 1
 */

#define		CARGA_50us		63036                              // Corresponde a 0º

void Tim_50us(){                                                	
    T1CON = 0b11001000;
    TMR1 = CARGA_50us;
    T1CONbits.TMR1ON = 1;
    PIR1bits.TMR1IF = 0;
    while(PIR1bits.TMR1IF == 0) continue;
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 0;
}

// CARGA_2us  = 65536 - Tms/[(4/Fosc)*Pre] = 65536 - 0.02222222222/[(4/20000)*1] = 65424.89
// Pre = 1

#define		CARGA_2us		65430                             // Corresponde a los increnmentos de grados.

void Tim_2us(){                                                	
    T1CON = 0b11001000;
    TMR1 = CARGA_2us;
    T1CONbits.TMR1ON = 1;
    PIR1bits.TMR1IF = 0;
    while(PIR1bits.TMR1IF == 0) continue;
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 0;
}

/////////////////////////// Temporizaciones ////////////////////////////////////
void Temporizaciones(char contador, char pos_servo){
    if(contador >= pos_servo){
        contador = contador - pos_servo;
        pos_servo = contador;
        Tim_50us();
        for(char i = 0; i <= contador; i++){
            Tim_2us();
        }
    }else if(contador < pos_servo){
        contador = pos_servo - contador;
        pos_servo = contador;
        Tim_50us();
        for(char i = 0; i > contador; i--){
            Tim_2us();
        }
    }
}

/*////////////////////////// Interrupcion por TMR0 /////////////////////////////
 * Calculo del TMR0 para ontener 2.5 ms
 * Carga_TMR0  = 65536 - Tms/[(2/Fosc)*Pre] = 65536 - 2.5/[(2/48000)*2] = 59286
 * Pre = 2 
 */ 

#define     Carga_TMR0      59286
         
void __interrupt() Interrupcion_TMR0(){
    TMR0 = Carga_TMR0;

    if(INTCONbits.TMR0IF == 1){ 
        contador_servos++;
        if(contador_servos == 1 && bandera_servo[1] == 1){
            S1 = 1;
            Temporizaciones(servo_1, pos_servo1);    
            S1 = 0;
        }else if(contador_servos == 2 && bandera_servo[2] == 1){
            S2 = 1;
            Temporizaciones(servo_2, pos_servo2);
            S2 = 0;
        }else if(contador_servos == 3 && bandera_servo[3] == 1){
            S3 = 1;
            Temporizaciones(servo_3, pos_servo3);
            S3 = 0;
        }else if(contador_servos == 4 && bandera_servo[4] == 1){
            S4 = 1;
            Temporizaciones(servo_4, pos_servo4);
            S4 = 0;
        }else if(contador_servos == 8){
            contador_servos = 0;
        } 
        INTCONbits.TMR0IF = 0;
    } 
}

