/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de user
 * 
 * Aquí se definen macros, tipos de datos y se declaran las funciones y datos 
 * externos de user
 */
#ifndef USER_H
#define USER_H
/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/
/* User Level #define Macros                                                 */
/* TODO: Los parámetros de user.c pueden ponerse aquí */
    
//Teclas
#define PIN_LED1    PORTDbits.RD1
#define TRIS_LED1   TRISDbits.TRISD1

#define SOL1        PORTAbits.RA5
#define TRIS_SOL1   TRISAbits.TRISA5

#define SOL2        PORTAbits.RA4
#define TRIS_SOL2   TRISAbits.TRISA4

//#define ENABLEA     PORTDbits.RD2
//#define TRIS_ENA    TRISDbits.TRISD2
//
//#define ENABLEB     PORTDbits.RD7
//#define TRIS_ENB    TRISDbits.TRISD7
//
#define MOT_DER1       PORTDbits.RD3
#define TRIS_MOT_DER1    TRISDbits.TRISD3

#define MOT_IZQ1       PORTDbits.RD4
#define TRIS_MOT_IZQ1    TRISDbits.TRISD4

#define MOT_DER2       PORTDbits.RD5
#define TRIS_MOT_DER2    TRISDbits.TRISD5

#define MOT_IZQ2       PORTDbits.RD6
#define TRIS_MOT_IZQ2    TRISDbits.TRISD6

#define DER1        PORTCbits.RC6
#define TRIS_DER1   TRISCbits.TRISC6

#define IZ1         PORTCbits.RC5
#define TRIS_IZ1    TRISCbits.TRISC5

#define PAT1         PORTCbits.RC7
#define TRIS_PAT1    TRISCbits.TRISC7

#define DER2        PORTCbits.RC1
#define TRIS_DER2   TRISCbits.TRISC1

#define IZ2         PORTCbits.RC0
#define TRIS_IZ2    TRISCbits.TRISC0

#define PAT2         PORTCbits.RC2
#define TRIS_PAT2    TRISCbits.TRISC2
//Alias de los Leds
//Buzzer
#define	TRIS_SOUNDER    TRISDbits.TRISD0
#define	BUZZER       PORTDbits.RD0

//Definición de notas
#define LA_4        1136
//...
#define Silencio    0

//Definición de Figuras
#define Semifusa    50
//...

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/
//extern char datoUser; //Ejemplo

/*==================[declaraciones de funciones externas]====================*/
/* TODO: Los prototipos de User level (ej. InitApp) van aquí */
void appInit(void);     /* Inicializa las I/O y los periféricos */
void delayTMR0mSeg(uint16_t tmsegs); /* Demora una cantidad de mSegs basado en desbordes de TMR0 */

/*==================[fin del archivo]========================================*/
#endif// USER_H
