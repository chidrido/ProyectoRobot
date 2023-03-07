#include "FuncionesMultiservo.h"
#define _XTAL_FREQ 20000000UL


////////////////////////////// Control de Servos ///////////////////////////////
static void servo1(char num_1, int vel_1){          // Funcion para mover el servo 1
    bandera_servo[1] = 1;
    servo_1 = num_1;
    while(vel_1 > 0){
        vel_1--;
        __delay_us(990);
    }
    bandera_servo[1] = 0;
}

static void servo2(char num_2, int vel_2){          // Funcion para mover el servo 2
    bandera_servo[2] = 1;
    servo_2 = num_2;
    while(vel_2 > 0){
        vel_2--;
        __delay_us(990);
    }
    bandera_servo[2] = 0;
}

static void servo3(char num_3, int vel_3){          // Funcion para mover el servo 3
    bandera_servo[3] = 1;
    servo_3 = num_3;
    while(vel_3 > 0){
        vel_3--;
        __delay_us(990);
    }
    bandera_servo[3] = 0;
}

static void servo4(char num_4, int vel_4){          // Funcion para mover el servo 4
    bandera_servo[4] = 1;
    servo_4 = num_4;
    while(vel_4 > 0){
        vel_4--;
        __delay_us(990);
    }
    bandera_servo[4] = 0;
}

static void servos(char num_1, char num_2, char num_3, char num_4, int vel_){
    bandera_servo[1] = 1;
    bandera_servo[2] = 1;
    bandera_servo[3] = 1;
    bandera_servo[4] = 1;
    servo_1 = num_1;
    servo_2 = num_2;
    servo_3 = num_3;
    servo_4 = num_4;
    
    while(vel_ > 0){
        vel_--;
        __delay_us(990);
    }
    bandera_servo[1] = 0;
    bandera_servo[2] = 0;
    bandera_servo[3] = 0;
    bandera_servo[4] = 0;
}

static void servo12(char num_11, char num_12, int vel_12){
    bandera_servo[1] = 1;
    bandera_servo[2] = 1;
    servo_1 = num_11;
    servo_2 = num_12;
    while(vel_12 > 0){
        vel_12--;
        __delay_us(990);
    }
    bandera_servo[1] = 0;
    bandera_servo[2] = 0;
}

//////////////////////////// Funciones de posicion /////////////////////////////
static void borraPosiciones(){
    pos_servo1 = 0;
    pos_servo2 = 0;
    pos_servo3 = 0;
    pos_servo4 = 0;
}

static void posicionInicial(){
    servos(36, 36, 36, 36, 500);
}

static void grados() {
    servo1(0, vel);
    __delay_ms(del);
    servo1(1, vel);
    __delay_ms(del);
    servo1(2, vel);
    __delay_ms(del);
    servo1(3, vel);
    __delay_ms(del);
    servo1(4, vel);
    __delay_ms(del);
    servo1(5, vel);
    __delay_ms(del);
    servo1(6, vel);
    __delay_ms(del);
    servo1(7, vel);
    __delay_ms(del);
    servo1(8, vel);
    __delay_ms(del);
    servo1(9, vel);
    __delay_ms(del);
    servo1(10, vel);
    __delay_ms(del);
    
    servo1(11, vel);
    __delay_ms(del);
    servo1(12, vel);
    __delay_ms(del);
    servo1(13, vel);
    __delay_ms(del);
    servo1(14, vel);
    __delay_ms(del);
    servo1(15, vel);
    __delay_ms(del);
    servo1(16, vel);
    __delay_ms(del);
    servo1(17, vel);
    __delay_ms(del);
    servo1(18, vel);
    __delay_ms(del);
    servo1(19, vel);
    __delay_ms(del);
    servo1(20, vel);
    __delay_ms(del);
    
    servo1(21, vel);
    __delay_ms(del);
    servo1(22, vel);
    __delay_ms(del);
    servo1(23, vel);
    __delay_ms(del);
    servo1(24, vel);
    __delay_ms(del);
    servo1(25, vel);
    __delay_ms(del);
    servo1(26, vel);
    __delay_ms(del);
    servo1(27, vel);
    __delay_ms(del);
    servo1(28, vel);
    __delay_ms(del);
    servo1(29, vel);
    __delay_ms(del);
    servo1(30, vel);
    __delay_ms(del);
    
    servo1(31, vel);
    __delay_ms(del);
    servo1(32, vel);
    __delay_ms(del);
    servo1(33, vel);
    __delay_ms(del);
    servo1(34, vel);
    __delay_ms(del);
    servo1(35, vel);
    __delay_ms(del);
    servo1(36, vel);
    __delay_ms(del);
    servo1(37, vel);
    __delay_ms(del);
    servo1(38, vel);
    __delay_ms(del);
    servo1(39, vel);
    __delay_ms(del);
    servo1(40, vel);
    __delay_ms(del);
    
    servo1(41, vel);
    __delay_ms(del);
    servo1(42, vel);
    __delay_ms(del);
    servo1(43, vel);
    __delay_ms(del);
    servo1(44, vel);
    __delay_ms(del);
    servo1(45, vel);
    __delay_ms(del);
    servo1(46, vel);
    __delay_ms(del);
    servo1(47, vel);
    __delay_ms(del);
    servo1(48, vel);
    __delay_ms(del);
    servo1(49, vel);
    __delay_ms(del);
    servo1(50, vel);
    __delay_ms(del);
}

static void posicion0(){
    servo1(0, 300);
    servo2(0, 300);
    servo3(0, 300);
    servo4(0, 300);
}

///////////////////////////////// Movimientos //////////////////////////////////
#define tiempoM  100
#define tiempoR  200
static void andar(){
   
    servos(30, 45, 45, 30, tiempoM);
    __delay_ms(tiempoR);
    
    servos(37, 45, 45, 37, tiempoM);
    __delay_ms(tiempoR);
    
    servos(44, 30, 30, 44, tiempoM);
    __delay_ms(tiempoR);
    
    servos(37, 30, 30, 37, tiempoM);
    __delay_ms(tiempoR);
    
    
}