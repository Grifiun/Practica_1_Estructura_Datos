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
void agregarCarretaPilas(ListadoCarreta* listado1, ListadoCarreta* listado2, Carreta* carretaAux){
    int cantidadCarretasAux = 1;
    int i = 0;
    //Generamos un ciclo para agregar la cantida de carretas dada
    while(i < cantidadCarretasAux){
        int numeroAleatorio = getNumeroAleatorio(0, 1);

        switch (numeroAleatorio)
        {
        case 0:
            /* Asignamos a la pila 1 */
            //Agregamos la pila donde se agregara la carreta y el id, el cual es el iterador + 1 (para que empiece en 1)
            agregarCarretaPorNodo(listado1, carretaAux);

            printf("La carreta %d volvio a la pila de carretas (%d) \n", carretaAux->id, 1);
            break;
        case 1:
            /* Asignamos a la pila 2 */
            //Agregamos la pila donde se agregara la carreta y el id, el cual es el iterador + 1 (para que empiece en 1)
            agregarCarretaPorNodo(listado2, carretaAux);
            printf("La carreta %d volvio a la pila de carretas (%d) \n", carretaAux->id, 2);
            break;
        default:
            break;
        }
        //agregamos el iterador
        i++;
    }
    
}

/*Ingresar cantidad carretas*/
Carreta* sacarPrimeraCarretaDisponible(ListadoCarreta* listado1, ListadoCarreta* listado2){
    /* Asignamos a la pila 1 */
    //Agregamos la pila donde se agregara la carreta y el id, el cual es el iterador + 1 (para que empiece en 1)
    if(listado1->inicio != NULL){
        Carreta* carretaAux = listado1->inicio;
        listado1->inicio = listado1->inicio->siguiente;//la pila de carretas comenzara en la siguiente
        carretaAux->siguiente = NULL;
        carretaAux->anterior = NULL;
        listado1->longitud = listado1->longitud - 1;//reducimos la longitud en 1
        return carretaAux;
    }else if(listado2->inicio != NULL){//si la primera pila esta vacia, se busca en la segunda
        Carreta* carretaAux = listado2->inicio;
        listado2->inicio = listado2->inicio->siguiente;//la pila de carretas comenzara en la siguiente
        carretaAux->siguiente = NULL;
        carretaAux->anterior = NULL;
        listado2->longitud = listado2->longitud - 1;//reducimos la longitud en 1
        return carretaAux;
    }
    return NULL;
    
}

/*obtener lognitud de la lista*/
int getLongitudListaCarreta(ListadoCarreta* listado){
    return listado->longitud;
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

/*se imprime el listado*/
FILE* ingresarSubGrafoCarreta(ListadoCarreta* listado, FILE* archivoDOT, const char *encabezadoSubgrafo, const char *tituloSubGrafo){
    Carreta* nodoAux;
    int i = 1;
    fputs(encabezadoSubgrafo, archivoDOT);//inicioSubGrafo    
    //Generamos los nodos en la figura
    if(listado -> inicio){
         nodoAux = listado -> inicio;
        while(nodoAux){   
            //Si no es el primer dato y el siguiente nodo es el inicio de la vuelta terminamos todo, difinimos este fin por si se usa para imprimir el listado circular de las compras
            if(i > 1 && nodoAux == listado->inicio){
                break;
            }

            char stra[50];
            sprintf(stra, "Carreta%d[label=\"Carreta: %d\"];\n", nodoAux -> id, nodoAux -> id);
            //printf("%s", stra);
            fputs(stra, archivoDOT);
            
            nodoAux = nodoAux -> siguiente;            
            i++;
        }
        
    }
       
    i = 1;
    if(listado -> inicio){
        nodoAux = listado -> inicio;
        while(nodoAux){   
            //Si no es el primer dato y el siguiente nodo es el inicio de la vuelta terminamos todo, difinimos este fin por si se usa para imprimir el listado circular de las compras
            if(i > 1 && nodoAux == listado->inicio){
                break;
            }
            char stra[50];
            if(nodoAux->siguiente != NULL){//si tiene un siguiente
                sprintf(stra, "Carreta%d -> Carreta%d;\n", nodoAux -> id, nodoAux -> siguiente -> id);
                fputs(stra, archivoDOT);
            }
            if(nodoAux->anterior != NULL){//si tiene un anterior
                sprintf(stra, "Carreta%d -> Carreta%d;\n", nodoAux -> id, nodoAux -> anterior -> id);
                fputs(stra, archivoDOT);
            }
            nodoAux = nodoAux -> siguiente;            
            i++;
        }
        
    }

    fputs(tituloSubGrafo, archivoDOT);//titulo del subgrafo
    fputs("}", archivoDOT);//fin del subgrafo
   return archivoDOT;
}

#endif //_CARRETA_H_