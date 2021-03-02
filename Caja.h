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
    int tiempoServicioCompletado;
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
    nodoAux-> tiempoServicioCompletado = 0;
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

    int tiempoServicio = 1;
    printf("tiempo de servicio de la caja %d: ", intAux);
    scanf("%d", &tiempoServicio);
    if(tiempoServicio > 0){//si se ingreso un numero valido
        nodoAux->tiempoServicio = tiempoServicio;
    }else{//le asignamos 1 en caso de recibir un numero invalido
        nodoAux->tiempoServicio = 1;
    }

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

/*Agregamos un cliente a la primera caja disponible que engcuentre*/
void agregarNodoClienteCaja(Caja* cajaAux, Cliente* clienteAux){ 
    int encontrado = 0;       
    //instanciamos el nodo auxiliar
    
    if(cajaAux == NULL){
        printf("\nCaja nula\n");
    }else{        
        cajaAux->cliente = clienteAux;
        cajaAux->estado = 1;//ocupado     
    }
}

/*Despachamos un cliente y asignamos su carreta a las pilas*/
void despacharClienteCajaYAgregarCarretaPilas(ListadoCaja* listado, int idCajaAux, ListadoCarreta* pilaCarreta1, ListadoCarreta* pilaCarreta2){
    
    //instanciamos el nodo auxiliar
    Caja* nodoAux2 = listado->inicio;
    if(listado->inicio == NULL){
        printf("\nNo hay cajas en el sistema\n");
    }else{
        while(nodoAux2 != NULL){//mientras hay cajas las recorremos
            if(nodoAux2->id == idCajaAux && nodoAux2->cliente != NULL){//Si la caja es la que nos indicaron, procedemos a agregar la carreta a las pilas de forma aleatoria, y ademas de liberar al cliente
                //obtenemos su carreta
                Carreta* carretaAux = nodoAux2->cliente->carreta;
                //liberamos el cliente
                liberarNodoCliente(nodoAux2->cliente);  
                nodoAux2->cliente = NULL;//le asignamos un cliente nulo
                nodoAux2->estado = 0;//estado vacio
                nodoAux2->tiempoServicioCompletado = 0;//reiniciamos el conteo de los turnos en caja
                agregarCarretaPilas(pilaCarreta1, pilaCarreta2, carretaAux);//asignamos la carreta de forma aleatoria a las 2 pilas       
                break;//Cerramos
            }
            nodoAux2 = nodoAux2->siguiente;//Iteramos           
        }
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

/*Obtener caja con id*/
Caja* obtenerCajaConId(ListadoCaja* listado, int id){
    Caja* inicio = listado->inicio;

    while(inicio != NULL){
        if(inicio->id == id){//si el id concuerda con el dado
            return inicio;//retornamos la caja
        }
        inicio = inicio->siguiente;//iteramos
    }

    return NULL;
}

/*se imprime el listado*/
void imprimirListadoCaja(ListadoCaja* listado){
    Caja* nodoAux;
    int i = 1;
    if(listado -> inicio){
         nodoAux = listado -> inicio;
        while(nodoAux){
            if(nodoAux->cliente != NULL)
                printf("CAJA: %d, CLI: %d, CARR: %d-> ", nodoAux -> id, nodoAux->cliente->id, nodoAux->cliente->carreta->id);
            else 
                printf("CAJA: %d -> ", nodoAux -> id);
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