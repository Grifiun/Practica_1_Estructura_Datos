/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Entidad Carretas

*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "NumeroAleatorio.h"

#ifndef _CARRETA_H_
#define _CARRETA_H_

typedef struct Carreta{
    int id;
    struct Carreta* siguiente;
    struct Carreta* anterior;
} Carreta;


typedef struct ListadoCarreta{
    Carreta* inicio;
    int longitud;
} ListadoCarreta;

/*
    Inicializamos el listado de carretas
*/
void inicializacionListadoCarreta (ListadoCarreta* listado){
  listado -> inicio = NULL;
  listado -> longitud = 0;
}

/*
    Creamos un nuevo nodo en el listado de carretas con un id igual al valor asignado
*/
Carreta* crearNodoCarreta(int valor){
    Carreta* nodoAux = (Carreta*) malloc (sizeof(Carreta));
    nodoAux-> id = valor;
    nodoAux-> siguiente = NULL;
    nodoAux-> anterior = NULL;
    return nodoAux;
}
/*
    Liberamos el espacio en memoria que ya no se usara
*/
void liberarNodoCarreta(Carreta* nodoAux){
    free(nodoAux);
}

/*
Se inserta el nodo al inicio, y el inicio se apunta al nuevo nodo (PILA)
*/
void agregarCarretaPorId(ListadoCarreta* listado, int idCarreta){
    
    Carreta* nodoAux;
    nodoAux = crearNodoCarreta(idCarreta);
    
    nodoAux -> siguiente = listado -> inicio;
    //Si existe un inicio
    if(listado -> inicio != NULL){
        listado -> inicio -> anterior = nodoAux;//Agregamos el anterior del inicio apuntando al nuevo nodo
    }
    
    listado -> longitud = listado -> longitud + 1;
    listado -> inicio = nodoAux;
}

/* Se agrega el nodo dado a la lista*/
void agregarCarretaPorNodo(ListadoCarreta* listado, Carreta* nodoAux){
    
    nodoAux -> siguiente = listado -> inicio;
    //Si existe un inicio
    if(listado -> inicio != NULL){
        listado -> inicio -> anterior = nodoAux;//Agregamos el anterior del inicio apuntando al nuevo nodo
    }
    
    listado -> longitud = listado -> longitud + 1;
    listado -> inicio = nodoAux;
}

/*se imprime el listado*/
void imprimirListadoCarreta(ListadoCarreta* listado){
    Carreta* nodoAux;
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

/*Ingresar cantidad carretas, y los id iran de inicioId hasta inicioId + cantidadCarretas*/
void generarPilasCarreta(ListadoCarreta* listado1, int idUsados){
    int i = 0;
    int cantidadCarretasPilaAux;
    //leemos la cantidad
    scanf("%d", &cantidadCarretasPilaAux);

    //Generamos un ciclo para agregar la cantida de carretas dada
    while(i < cantidadCarretasPilaAux){
            //agregamos la carreta a la pila
            /* Asignamos a la pila */
            //Agregamos la pila donde se agregara la carreta y el id, el cual es el iterador + 1 (para que empiece en 1)
            agregarCarretaPorId(listado1, idUsados + 1 + i);        
        //agregamos el iterador
        i++;
    }    
}

/*Ingresar cantidad carretas*/
void agregarCarretaPilas(ListadoCarreta* listado1, ListadoCarreta* listado2){
    int cantidadCarretasAux = 1;
    int i = 0;
    //Generamos un ciclo para agregar la cantida de carretas dada
    while(i < cantidadCarretasAux){
        int numeroAleatorio = getNumeroAleatorio();

        switch (numeroAleatorio)
        {
        case 0:
            /* Asignamos a la pila 1 */
            //Agregamos la pila donde se agregara la carreta y el id, el cual es el iterador + 1 (para que empiece en 1)
            agregarCarretaPorId(listado1, i + 1);
            break;
        case 1:
            /* Asignamos a la pila 2 */
            //Agregamos la pila donde se agregara la carreta y el id, el cual es el iterador + 1 (para que empiece en 1)
            agregarCarretaPorId(listado2, i + 1);
            break;
        default:
            break;
        }
        //agregamos el iterador
        i++;
    }
    
}

/*obtener lognitud de la lista*/
int getLongitudListaCarreta(ListadoCarreta* listado){
    return listado->longitud;
}

#endif //_CARRETA_H_