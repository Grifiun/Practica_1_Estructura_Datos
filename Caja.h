/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Entidad Cajas

*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Cliente.h"

#ifndef _CAJA_H_
#define _CAJA_H_

typedef struct Caja{
    int id;
    int tiempoServicio;
    int estado;

    struct Cliente* cliente;
    struct Caja* siguiente;
    struct Caja* anterior;
} Caja;

typedef struct ListadoCaja{
    Caja* inicio;
    int longitud;
} ListadoCaja;

/*
    Inicializamos el listado de cajas
*/
void inicializacionListadoCaja (ListadoCaja* listado){
  listado -> inicio = NULL;
  listado -> longitud = 0;
}

Caja* crearNodoCaja(int valor){
    Caja* nodoAux = (Caja*) malloc (sizeof(Caja));
    nodoAux-> id = valor;
    nodoAux-> tiempoServicio = 0;
    nodoAux-> estado = 0;
    nodoAux-> siguiente = NULL;
    nodoAux-> anterior = NULL;
    nodoAux-> cliente = NULL;

    return nodoAux;
}

/*
    Liberamos el espacio en memoria que ya no se usara
*/
void liberarNodoCaja(Caja* nodoAux){
    free(nodoAux);
}

void agregarCajaPorId(ListadoCaja* listado, int intAux){    
    Caja* nodoAux;
    //instanciamos el nodo
    nodoAux = crearNodoCaja(intAux);
    
    Caja* nodoAux2 = listado->inicio;
    if(listado->inicio == NULL){
        nodoAux -> siguiente = NULL;
        //Si existe un inicio        
        //Agregamos el anterior del inicio apuntando al nuevo nodo
        nodoAux->anterior = NULL;    
        listado -> inicio = nodoAux;
        listado -> longitud = listado->longitud + 1;
    }else{
        while(nodoAux2->siguiente != NULL){
            nodoAux2 = nodoAux2->siguiente;//Iteramos
        }
        nodoAux2->siguiente = nodoAux;//Agregamos al final de la cola
        nodoAux->anterior = nodoAux2;//Agregamos el anterior del nodo a agregar
        listado -> longitud = listado->longitud + 1;
    }
}


/*Ingresar n cantidad de clientes a la cola, y los id iran de inicioId hasta inicioId + cantidadClientes*/
void generarListadoCaja(ListadoCaja* listado1, int idsUsados){
    int i = 0;
    int auxCajas;
    scanf("%d", &auxCajas);
    //Agregar a la lista circular
    //Lista, cantidad de cajas, inicio de id    

    //Generamos un ciclo para agregar la cantida de cajas dada
    while(i < auxCajas){
        //agregamos la clientes a la lista circular
        //Agregamos la cola donde se agregara la y el id, el cual es el iterador + 1 (para que empiece en 1)
        agregarCajaPorId(listado1, 1 + idsUsados + i);        
        //agregamos el iterador
        i++;
    }    
}

/*se imprime el listado*/
void imprimirListadoCaja(ListadoCaja* listado){
    Caja* nodoAux;
    int i = 1;
    if(listado -> inicio){
         nodoAux = listado -> inicio;
        while(nodoAux){
            printf("%d -> ", nodoAux -> id);
            nodoAux = nodoAux -> siguiente;
            i++;
        }
        
    }else{
        printf("Lista vacia");
        
    }
    //damos el salto de linea
    printf("\n");
   
}

/*obtener lognitud de la lista*/
int getLongitudListaCaja(ListadoCaja* listado){
    return listado->longitud;
}

#endif //_CAJA_H_