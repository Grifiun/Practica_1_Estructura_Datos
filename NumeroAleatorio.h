/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Entidad de Generacion de numeros aleatorios

*******************************************************************************/
#include <stdlib.h>

#ifndef _NUMERO_ALEATORIO_H_
#define _NUMERO_ALEATORIO_H_

int getNumeroAleatorio(){
    int numeroAleatorio;
    //numeroAleatorio = rand () % (N-M+1) + M;   // Este está entre M y N
    numeroAleatorio = rand () % (2);   // Este está entre 0 y 1

    return numeroAleatorio;
}


#endif //_NUMERO_ALEATORIO_H_