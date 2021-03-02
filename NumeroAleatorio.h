/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Entidad de Generacion de numeros aleatorios

*******************************************************************************/
#include <stdlib.h>

#ifndef _NUMERO_ALEATORIO_H_
#define _NUMERO_ALEATORIO_H_

int getNumeroAleatorio(int inicio, int fin){
    int numeroAleatorio;
    //numeroAleatorio = rand () % (N-M+1) + M;   // Este está entre M(inicio) y N(fin)
    numeroAleatorio = rand () % (fin - inicio + 1) + inicio;   
    return numeroAleatorio;
}


#endif //_NUMERO_ALEATORIO_H_