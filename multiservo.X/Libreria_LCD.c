#include "xc.h"
#include "Libreria_LCD.h"
#include <stdint.h>

void LCD_EscribeLCD(char comando){
    lcd_dato = comando & 0xF0;              // Se queda con el nibble alto del dato que es el que hay que enviar y lo guarda.
    aux_port = LCD_BusDatos & 0x0F;         // Lee la informacion actual de la parte baja del Puerto B, que no se debe alterar.
    lcd_dato = aux_port ^ lcd_dato;         // Enviar la parte alta del dato de entrada y en la parte baja lo que habia antes.

    LCD_GuardaTRISD = TRISD;                // Guarda la configuracion que tenia antes TRISD.
    TRISD = TRISD & 0x0F;                   // Las 4 lineas inferiores del Puerto B se dejan omo estaban y las 4 superiores como salida.
    
    
    LCD_BusDatos = lcd_dato;                // Recupera el dato a enviar y envia el dato al modulo LCD.
    
    LCD_PinEnable = 1;                      // Permite funcionamiento del LCD mediante un corto
    LCD_PinEnable = 0;                      // pulso y termina impidiendo el funcionamiento del LCD.
    
    TRISD = LCD_GuardaTRISD;                // Restaura el antiguo valor en la configuracion del Puerto E.
}

void LCD_EnviaComando(char comandos){
    LCD_PinRS = 0;                          // Activa el Modo Comando, poniendo RS=0.
    
    LCD_GuardaDato = comandos;              // Guarda el dato a enviar.
    LCD_EscribeLCD(comandos);               // Primero envia el nibble alto.
                  
    num1 = comandos & 0x0F;                 // Ahora envia el nibble bajo. Para ello pasa el nibble bajo del dato a enviar a parte alta del byte.
    num2 = comandos & 0xF0;
    num1 = num1 << 4;                          
    num2 = num2 >> 4;
    LCD_GuardaDatoAux = num1 ^ num2;        // Ahora envia el nibble bajo. Para ello pasa el nibble bajo del dato a enviar a parte alta del byte.
    LCD_EscribeLCD(LCD_GuardaDatoAux );
    
    if(LCD_PinRS == 1){
        __delay_us(200);
        
    }else{
        __delay_ms(5);
    }
}   

void LCD_Caracter(char datos){
    LCD_PinRS = 1;                          // Activa el Modo Dato, poniendo RS=0.
    
    LCD_GuardaDato = datos;                 // Guarda el dato a enviar.
    LCD_EscribeLCD(datos);                  // Primero envia el nibble alto.
                  
    num3 = datos & 0x0F;                    // Ahora envia el nibble bajo. Para ello pasa el nibble bajo del dato a enviar a parte alta del byte.
    num4 = datos & 0xF0;
    num3 = num3 << 4;                           
    num4 = num4 >> 4;
    LCD_GuardaDatoAux = num3 ^ num4;        // Ahora envia el nibble bajo. Para ello pasa el nibble bajo del dato a enviar a parte alta del byte.
    LCD_EscribeLCD(LCD_GuardaDatoAux );
    
    if(LCD_PinRS == 1){
        __delay_us(200);
    }else{
        __delay_ms(5);
    }   
}

void LCD_CursorIncr(){
    LCD_EnviaComando(0b00000110);
}

void LCD_Linea1(){
    LCD_EnviaComando(0b10000000);    
}

void LCD_Linea2(){
    LCD_EnviaComando(0b11000000);    
}

void LCD_Linea3(){
    LCD_EnviaComando(0b10010100);    
}

void LCD_Linea4(){
    LCD_EnviaComando(0b11010100);    
}

void LCD_PosicionLinea1(){
    LCD_EnviaComando(0b10000000);    
}

void LCD_PosicionLinea2(){
    LCD_EnviaComando(0b11000000);    
}

void LCD_OFF(){
    LCD_EnviaComando(0b00001000);    
}

void LCD_CursorON(){
    LCD_EnviaComando(0b00001110);    
}

void LCD_CursorOFF(){
    LCD_EnviaComando(0b00001100);    
}

void LCD_Borra(){
    LCD_EnviaComando(0b00000001);    
}

void LCD_2Lineas4Bits5x7(){
    LCD_EnviaComando(0b00101000);
}

void LCD_Iniciliza(){
    ADCON1 = 0b00001111;                
    TRISEbits.TRISE0 = 0;                   // Configura las líneas conectadas al pines RS, R/W y E.
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE1 = 0;
    
    LCD_PinRW = 0;
    LCD_PinEnable = 0;		
    LCD_PinRS = 0;
    
    __delay_ms(20);
    
    LCD_EscribeLCD(0b00110000);             // Debe enviar el numero 3 por 3 veces.
    __delay_ms(5);
    
    LCD_EscribeLCD(0b00110000);
    __delay_us(200);
    
    LCD_EscribeLCD(0b00110000);
    __delay_us(200);
    
    LCD_EscribeLCD(0b00100000);
    __delay_us(200);

    LCD_2Lineas4Bits5x7();
    LCD_Borra();
    LCD_CursorOFF();
    LCD_CursorIncr();
}