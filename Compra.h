/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Entidad Compra

*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Cliente.h"

#ifndef _COMPRA_H_
#define _COMPRA_H_

//Usaremos el listado de clientes la entidad Cliente, auqnue para agregar nuevos nodos haremos una lista circular

void agregarCompraPorId(ListadoCliente* listado, int intAux, int idCarreta){
    Cliente* nodoAux;
    //instanciamos el nodo
    nodoAux = crearNodoCliente(intAux);
    
    Carreta* carretaAux = crearNodoCarreta(idCarreta);//creamos la carreta si se le asigno una 
    nodoAux->carreta = carretaAux;//le asignamos la carreta al nodo auxiliar cliente        

    Cliente* nodoAux2 = listado->inicio;
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

            if(nodoAux2->siguiente == listado->inicio)//si regresamos al inicio, terminamos el ciclo
                break;
        }
        nodoAux2->siguiente = nodoAux;//Agregamos al final de la cola
        nodoAux->anterior = nodoAux2;//Agregamos el anterior del nodo a agregar

        //Enlazamos el ultimo con el primero
        //El siguiente del ultimo elemento es el primer elemento
        nodoAux -> siguiente = listado -> inicio;
        //El anterior del primer elemento es el ultimo
        listado->inicio->anterior = nodoAux;
        listado -> longitud = listado->longitud + 1;
    }    
}

/*
Se inserta el nodo al inicio, y el inicio se apunta al nuevo nodo (PILA)
*/
void agregarCompraPorNodo(ListadoCliente* listado, Cliente* nodoAux){
    Cliente* nodoAux2 = listado->inicio;
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

            if(nodoAux2->siguiente == listado->inicio)//si regresamos al inicio, terminamos el ciclo
                break;
        }
        nodoAux2->siguiente = nodoAux;//Agregamos al final de la cola
        nodoAux->anterior = nodoAux2;//Agregamos el anterior del nodo a agregar

        //Enlazamos el ultimo con el primero
        //El siguiente del ultimo elemento es el primer elemento
        nodoAux -> siguiente = listado -> inicio;
        //El anterior del primer elemento es el ultimo
        listado->inicio->anterior = nodoAux;

        listado -> longitud = listado->longitud + 1;
    }
    
}

/**/
Cliente* extraerNodoListadoCompra(ListadoCliente* listado, int idAux){
    int encontrado = 0;
    Cliente* nodoAux = listado -> inicio;
      
    if(listado -> inicio){
        int i = 0;
        while(encontrado == 0 && i < listado->longitud){
            //si el siguiente nodo tiene el id deseado
            if(nodoAux -> id == idAux){
                encontrado = 1;
                break;
            }else if(nodoAux -> id != idAux && nodoAux -> siguiente){
                i++;
                nodoAux = nodoAux -> siguiente;
            }
        }

        if(encontrado == 1){
            //printf("Nodo con id %d encontrado con exito, en la posicion %d de la lista\n", idAux, index);
            if(listado->inicio == nodoAux){//si el que removemos es el primero de la lista, agregamos el nuevo inicio
                listado->inicio = nodoAux->siguiente;
            }
            Cliente* anterior = nodoAux->anterior;
            Cliente* siguiente = nodoAux->siguiente;
            //agregamos las conexiones de los 2 nodos en 2 direcciones
            if(anterior != NULL){
                anterior->siguiente = siguiente; 
                siguiente->anterior = anterior;
            }                

            nodoAux->anterior = NULL;
            nodoAux->siguiente = NULL;

            listado->longitud = listado->longitud - 1;
            return nodoAux;
            
        }else{
            //printf("Nodo no encontrado con el id dado (%d)\n", idAux);
        }
        
        
    }else{
        printf("Lista vacia\n");
        
    }
    
    return NULL;
}


/*Ingresar n cantidad de clientes a la cola, y los id iran de inicioId hasta inicioId + cantidadClientes*/
void generarListaCircularCompra(ListadoCliente* listado1, int idsUsados, int idCarretasUsados){
    int i = 0;
    int cantidadClienteCompra;
    scanf("%d", &cantidadClienteCompra);
    //Agregar a la lista circular
    //Lista, cantidad de clientes a comprar, inicio de id    

    //Generamos un ciclo para agregar la cantida de clientes dada
    while(i < cantidadClienteCompra){
        //agregamos la clientes a la lista circular
        //Agregamos la cola donde se agregara la y el id, el cual es el iterador + 1 (para que empiece en 1)
        agregarCompraPorId(listado1, 1 + idsUsados + i, idCarretasUsados + i + 1);        
        //agregamos el iterador
        i++;
    }    
}

/*se imprime el listado*/
void imprimirListadoCompra(ListadoCliente* listado){
    Cliente* nodoAux;
    int i = 1;
    if(listado -> inicio){
         nodoAux = listado -> inicio;
        while(nodoAux){
            //Si no es el primer dato y el siguiente nodo es el inicio de la vuelta terminamos todo
            if(i > 1 && nodoAux == listado->inicio){
                break;
            }
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


#endif //_COMPRA_H_