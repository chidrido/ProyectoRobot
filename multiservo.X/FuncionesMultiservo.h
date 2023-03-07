
#ifndef XC_FUNCIONESMULTISERVO_H
#define	XC_FUNCIONESMULTISERVO_H

#include <xc.h> // include processor files - each processor file is guarded.

#define vel  200
#define del  200

static char bandera_servo[8];
static char servo_1;
static char servo_2;
static char servo_3;
static char servo_4;
static char servo_5;
static char servo_6;
static char servo_7;
static char servo_8;

static char pos_servo1 = 0;
static char pos_servo2 = 0;
static char pos_servo3 = 0;
static char pos_servo4 = 0;

static void borraPosiciones();
static void posicionInicial();
static void grados();
static void posicion0();

/////////////////////////////////// Funciones //////////////////////////////////

static void servo1(char num_1, int vel_1);
static void servo2(char num_2, int vel_2);
static void servo3(char num_3, int vel_3);
static void servo4(char num_4, int vel_4);
static void servos(char num_1, char num_2, char num_3, char num_4, int vel_);
static void servo12(char num_11, char num_12, int vel_12);

static void andar();

#endif

