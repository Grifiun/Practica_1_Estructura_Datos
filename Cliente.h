/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Entidad cliente

*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Carreta.h"

#ifndef _CLIENTE_H_
#define _CLIENTE_H_
typedef struct Cliente{
    int id;
    
    struct Carreta* carreta;
    struct Cliente* siguiente;
    struct Cliente* anterior;
} Cliente;

typedef struct ListadoCliente{
    Cliente* inicio;
    int longitud;
} ListadoCliente;

/*
    Inicializamos el listado de clientes
*/
void inicializacionListadoCliente (ListadoCliente* listado){
  listado -> inicio = NULL;
  listado -> longitud = 0;
}

/*
    Creamos un nuevo nodo en el listado de clientes con un id igual al valor asignado
*/
Cliente* crearNodoCliente(int valor){
    Cliente* nodoAux = (Cliente*) malloc (sizeof(Cliente));
    nodoAux-> id = valor;
    nodoAux-> siguiente = NULL;
    nodoAux-> anterior = NULL;
    nodoAux-> carreta = NULL;

    return nodoAux;
}
/*
    Liberamos el espacio en memoria que ya no se usara
*/
void liberarNodoCliente(Cliente* nodoAux){
    free(nodoAux);
}

/*
Se inserta el nodo al inicio, y el inicio se apunta al nuevo nodo (PILA)
*/
void agregarClientePorId(ListadoCliente* listado, int intAux, int idCarreta){
    Cliente* nodoAux;
    //instanciamos el nodo
    nodoAux = crearNodoCliente(intAux);
    if(idCarreta > 0){//si es mayor a 0, lleva una carreta y por ende
        Carreta* carretaAux = crearNodoCarreta(idCarreta);//creamos la carreta si se le asigno una 
        nodoAux->carreta = carretaAux;//le asignamos la carreta al nodo auxiliar cliente
    }
    

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
        }
        nodoAux2->siguiente = nodoAux;//Agregamos al final de la cola
        nodoAux->anterior = nodoAux2;//Agregamos el anterior del nodo a agregar
        listado -> longitud = listado->longitud + 1;
    }
    
}

/*
Se inserta el nodo al inicio, y el inicio se apunta al nuevo nodo (PILA)
*/
void agregarClientePorNodo(ListadoCliente* listado, Cliente* nodoAux){

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
        }
        nodoAux2->siguiente = nodoAux;//Agregamos al final de la cola
        nodoAux->anterior = nodoAux2;//Agregamos el anterior del nodo a agregar
        listado -> longitud = listado->longitud + 1;
    }
    
}

/* Funcion para ubicar un nodo por su id, removerlo del listado y retornar un Cliente*/
Cliente* extraerNodoListadoCliente(ListadoCliente* listado, int idAux){
    int encontrado = 0, index = 1;
    Cliente* nodoAux = listado -> inicio;
      
    if(listado -> inicio){
        
        while(encontrado == 0){
            //si el siguiente nodo tiene el id deseado
            if(nodoAux -> id == idAux){
                encontrado = 1;
                 break;
            }else if(nodoAux -> id != idAux && nodoAux -> siguiente){
                index++;
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
            //agregamos las conexiones de los 2 nodos
            if(anterior != NULL)
                anterior->siguiente = siguiente; 
            if(siguiente != NULL)
                siguiente->anterior = anterior;

            nodoAux->anterior = NULL;
            nodoAux->siguiente = NULL;           

            listado->longitud = listado->longitud - 1;
            return nodoAux;
            
        }else{
            printf("Nodo no encontrado con el id dado (%d)\n", idAux);
        }
        
        
    }else{
        printf("Lista vacia\n");
        
    }
    
    return nodoAux;
}

/* Ordenamos el listado de datos segun el id de menor a mayor */
void ordenarListadoCliente(ListadoCliente* listado){
    //verificamos si existe un inicio
     if(listado -> inicio){
        Cliente* nodoAux = listado -> inicio;
        while(nodoAux -> siguiente != NULL){//recorremos la lista hasta que ya no haya un nodo siguiente al cual comparar
            //si el siguiente nodo tiene un id mayor al del siguiente nodo
            if((nodoAux -> id) > (nodoAux -> siguiente -> id)){
                //Entonces cambiamos posicion los NODOS
                //nodos auxiliares, a los que hay que cambiarles los punteros
                Cliente* anteriorAuxiliar = nodoAux -> anterior;
                Cliente* siguienteAuxiliar = nodoAux -> siguiente;
                
                //su nodo anterior sera el nodo a cambiar
                nodoAux -> anterior = siguienteAuxiliar;
                
                 //le agregamos el siguiente, el cual corresponde al siguiente del nodo a cambiar 
                nodoAux -> siguiente = siguienteAuxiliar -> siguiente;
               
               //cambiamos la direccion del siguiente al nodo 2
                siguienteAuxiliar -> siguiente = nodoAux;
                
                //cambiamos su anterior al anterior del nodo 1 
                siguienteAuxiliar -> anterior = anteriorAuxiliar;
                
               if(anteriorAuxiliar != NULL){
                    //agregamos el siguiente al nodo anterior al nodo 1 (si existe)
                    anteriorAuxiliar -> siguiente = siguienteAuxiliar;
                }else{
                    //finalmente agregamos el puntero del listado
                    //si no tiene anterior, significa que el nuevo inicio es el nodo 2
                    listado -> inicio = siguienteAuxiliar;
                }
                
            }else{
                //sino, no hacemos ningun cambiamos, y hacemos la siguiente iteracion
                nodoAux = nodoAux -> siguiente;
            }
        }
    }else{
        printf("Lista vacia\n");
        
    }
    
    
}

/*Ingresar n cantidad de clientes a la cola, y los id iran de inicioId hasta inicioId + cantidadClientes*/
void generarColasClientes(ListadoCliente* listado1, int idsUsados, int llevanCarretas, int idCarretasUsados){
    int i = 0;
    int cantidadClientesEsperaCarretas;
    scanf("%d", &cantidadClientesEsperaCarretas);
    //Agregar a la cola
    //Lista, cantidad de clientes a agregar, inicio de id    

    //Generamos un ciclo para agregar la cantida de clientes dada
    while(i < cantidadClientesEsperaCarretas){
        //agregamos la clientes a la cola
        //Agregamos la cola donde se agregara la y el id, el cual es el iterador + 1 (para que empiece en 1)
        if(llevanCarretas > 0)//si tiene carreta
            agregarClientePorId(listado1, 1 + idsUsados + i, idCarretasUsados + i + 1);   
        else{
            agregarClientePorId(listado1, 1 + idsUsados + i, 0); 
        }
             
        //agregamos el iterador
        i++;
    }    
}


/*se imprime el listado*/
void imprimirListadoCliente(ListadoCliente* listado){
    Cliente* nodoAux;
    int i = 1;
    if(listado -> inicio){
         nodoAux = listado -> inicio;
        while(nodoAux){   
            //Si no es el primer dato y el siguiente nodo es el inicio de la vuelta terminamos todo, difinimos este fin por si se usa para imprimir el listado circular de las compras
            if(i > 1 && nodoAux == listado->inicio){
                break;
            }

            if(nodoAux->carreta != NULL)//si tiene una carreta 
                printf("CL: %d , CARR: %d -> ", nodoAux -> id, nodoAux->carreta->id);    
            else   
                printf("CL: %d -> ", nodoAux -> id);
            
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
int getLongitudListaCliente(ListadoCliente* listado){
    return listado->longitud;
}

#endif //_CLIENTE_H_