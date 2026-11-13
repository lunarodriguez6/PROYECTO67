/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene la función principal
 * 
 * Aquí se encuentra la implementación de la función principal
 */
/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* Para las definiciones de uint8_t por ej.*/
#include "system.h"     /* Funciones/Parametros System, como osc/peripheral config */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "uart.h"       /* Funciones/Parametros Uart */
#include "display.h"    /* Funciones/Parametros Display */
#include "tick.h"       /* Funciones/Parametros Tick */
#include <stdio.h>      /* Archivo de Encabezados StdIO */

/*==================[definiciones y macros]==================================*/
// Nuevo tipo de datos enumerado llamado estadoMEF_t
typedef enum{IZQUIERDA, DERECHA, REPOSO} estadoMEF_t;
typedef enum{INACTIVO, ACTIVO, COLDOWN} estadoMEFPAT_t;
#define TCOLDOWN  600
#define TPATADA   200

/*==================[definiciones de datos internos]=========================*/
estadoMEF_t  estadoActualJ1; // Variable de estado (global)
estadoMEF_t  estadoActualJ2; // Variable de estado (global)
estadoMEFPAT_t estadoActualPAT1; 
estadoMEFPAT_t estadoActualPAT2;

tick_t tInicio_P1; 
tick_t tInicio_P2; 

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
void InicializarMEF_J1(void);
void InicializarMEF_J2(void);
void ActualizarMEF_J1(void);
void ActualizarMEF_J2(void);
void InicializarMEF_P1(void);
void InicializarMEF_P2(void);
void ActualizarMEF_P1(void);
void ActualizarMEF_P2(void);

/*==================[funcion principal]======================================*/
void main(void) {
    /* TODO: Agregar el Cod1iogo de la Aplicación aquí */
    appInit(); /* Inicializa I/O y Periféricos de la aplicación */
    InicializarMEF_J1();
    InicializarMEF_J2();
    InicializarMEF_P1();
    InicializarMEF_P2();

    /*MOT_DER1 = 0;
    MOT_IZQ1 = 0;
    MOT_DER2 = 0;
    MOT_IZQ2 = 0;*/
    while (1) {
        /*MOT_DER1 = 1;
        MOT_IZQ1 = 0;
        __delay_ms(500);
        SOL1 = 1;
        __delay_ms(200);        
        SOL1 = 0;
        __delay_ms(200);
        MOT_DER1 = 0;
        MOT_IZQ1 = 1;        
        __delay_ms(500);
        
        MOT_DER2 = 1;
        MOT_IZQ2 = 0;
        __delay_ms(500);
        SOL2 = 1;
        __delay_ms(200);        
        SOL2 = 0;
        __delay_ms(200);
        MOT_DER2 = 0;
        MOT_IZQ2 = 1;        
        __delay_ms(500);
        */
        ActualizarMEF_J1();        
        ActualizarMEF_J2();
        ActualizarMEF_P1();
        ActualizarMEF_P2();

    }
}

/*==================[definiciones de funciones internas]=====================*/
// Función Inicializa MEF
void InicializarMEF_J1(void) {
    MOT_DER1 = 0;
    MOT_IZQ1 = 0;
    PIN_LED1 = 1;          // Apago el LED1
    estadoActualJ1 = REPOSO; // Establece estado inicial 
}

void InicializarMEF_J2(void) {
    MOT_DER2 = 0;
    MOT_IZQ2 = 0;
    estadoActualJ2 = REPOSO; // Establece estado inicial 
}
void InicializarMEF_P1(void) {
    SOL1 = 0;
    estadoActualPAT1 = INACTIVO; // Establece estado inicial 
}
void InicializarMEF_P2(void) {
    SOL2 = 0;
    estadoActualPAT2 = INACTIVO; // Establece estado inicial 
}
// Función Actualizar MEF
void ActualizarMEF_J1(void) {
    switch (estadoActualJ1) {
        case REPOSO:
            MOT_DER1 = 0;
            MOT_IZQ1 = 0;
            if (IZ1 == 0) {                 // Si presiona el botòn izquierdo
                estadoActualJ1 = IZQUIERDA;  // Mueve hacia la izuqierda               
            }else if (DER1 == 0){          // Si presiona el botòn derecho
                estadoActualJ1 = DERECHA;    // Mueve hacia la derecha
            }
            break;
        case DERECHA:
            MOT_DER1 = 1;
            MOT_IZQ1 = 0;
            if (DER1 == 1 && IZ1 == 1){          // Si presiona el botòn derecho
                estadoActualJ1 = REPOSO;    // Mueve hacia la derecha
            }else if (IZ1 == 0){
                estadoActualJ1 = IZQUIERDA;
            }
            break;
        case IZQUIERDA:
            MOT_DER1 = 0;
            MOT_IZQ1 = 1;
            if (DER1 == 1 && IZ1 == 1){          // Si presiona el botòn derecho
                estadoActualJ1 = REPOSO;    // Mueve hacia la derecha
            }else if (DER1 == 0){
                estadoActualJ1 = DERECHA;
            }
            break;
        default:
            //Si algo modificó la variable estadoActual 
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_J1();
    }
}

void ActualizarMEF_J2(void) {
    switch (estadoActualJ2) {
        case REPOSO:
            MOT_DER2 = 0;
            MOT_IZQ2 = 0;
            if (IZ2 == 0) {                 // Si presiona el botòn izquierdo
                estadoActualJ2 = IZQUIERDA;  // Mueve hacia la izuqierda               
            }else if (DER2 == 0){          // Si presiona el botòn derecho
                estadoActualJ2 = DERECHA;    // Mueve hacia la derecha
            }
            break;
        case DERECHA:
            MOT_DER2 = 1;
            MOT_IZQ2 = 0;
            if (DER2 == 1 && IZ2 == 1){          // Si presiona el botòn derecho
                estadoActualJ2 = REPOSO;    // Mueve hacia la derecha
            }else if (IZ2 == 0){
                estadoActualJ2 = IZQUIERDA;
            }
            break;
        case IZQUIERDA:
            MOT_DER2 = 0;
            MOT_IZQ2 = 1;
            if (DER2 == 1 && IZ2 == 1){          // Si presiona el botòn derecho
                estadoActualJ2 = REPOSO;    // Mueve hacia la derecha
            }else if (DER2 == 0){
                estadoActualJ2 = DERECHA;
            }
            break;
        default:
            //Si algo modificó la variable estadoActual 
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_J2();
    }
}


void ActualizarMEF_P1(void) {
    switch (estadoActualPAT1) {
        case INACTIVO:
            SOL1 = 0;
            if (PAT1 == 0) {                 // Si presiona boton 
                tInicio_P1 = tickRead();
                estadoActualPAT1 = ACTIVO;  // Mueve hacia la izuqierd
            }
            break;
            
        case ACTIVO:
            SOL1 = 1; 
            if(tickRead()-tInicio_P1 > TPATADA ){// si paso el tiempo
                tInicio_P1 = tickRead();
                estadoActualPAT1 = COLDOWN;
            }
            break;
            
        case COLDOWN:
            SOL1 = 0;
            if(tickRead()-tInicio_P1 > TCOLDOWN && PAT1==1){ // si paso el tiempo y solto el boton
                estadoActualPAT1 = INACTIVO;
            }
            break;
        default:
            //Si algo modificó la variable estadoActual 
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_P1();
    }
}

void ActualizarMEF_P2(void) {
    switch (estadoActualPAT2) {
        case INACTIVO:
            SOL2 = 0;
            if (PAT2 == 0) {                 // Si presiona boton 
                tInicio_P2 = tickRead();
                estadoActualPAT2 = ACTIVO;  // Mueve hacia la izuqierd
            }
            break;
            
        case ACTIVO:
            SOL2 = 1; 
            if(tickRead()-tInicio_P2 > TPATADA ){// si paso el tiempo
                tInicio_P2 = tickRead();
                estadoActualPAT2 = COLDOWN;
            }
            break;
            
        case COLDOWN:
            SOL2 = 0;
            if(tickRead()-tInicio_P2 > TCOLDOWN && PAT2==1){ // si paso el tiempo y solto el boton
                estadoActualPAT2 = INACTIVO;
            }
            break;
        default:
            //Si algo modificó la variable estadoActual 
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_P2();
    }
}
/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
