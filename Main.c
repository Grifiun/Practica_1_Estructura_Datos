/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Clase main

*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Cliente.h"
#include "Carreta.h"
#include "Compra.h"
#include "Caja.h"

/*Funcion que se usara para iniciar el programa e indicar la cantidad de nodos en cada lista*/
void ingresarCantidadDatosListas(ListadoCliente* listadoClienteEsperaCarretas, ListadoCliente* listadoClienteCompra, ListadoCliente* listadoClienteColaPago, ListadoCarreta* pilaCarreta1, ListadoCarreta* pilaCarreta2, ListadoCaja* listadoCaja){
    int cantidadClientesEsperaCarretas;
    int cantidadCarretasPila1;
    int cantidadCarretasPila2;
    int cantidadClientesComprando;
    int cantidadClientesColaPago;
    int cantidadCajasPago;

    /*● Cantidad clientes en cola de espera de carretas  */
    printf("Ingrese la cantidad de clientes en la cola de espera de carretas: ");
    generarColasClientes(listadoClienteEsperaCarretas, 0);
    /*● Cantidad de clientes comprando  */
    printf("Ingrese la cantidad de clientes comprando: ");
    generarListaCircularCompra(listadoClienteCompra, getLongitudListaCliente (listadoClienteEsperaCarretas));
    /*● Cantidad de clientes en cola de pagos  */
    printf("Ingrese la cantidad de clientes en la cola de pago: ");
    generarColasClientes(listadoClienteColaPago, getLongitudListaCliente (listadoClienteEsperaCarretas) + getLongitudListaCliente(listadoClienteCompra) );

    /*● Cantidad de carretas por pila */
    printf("Ingrese la cantidad de carretas en la primera pila: ");
    generarPilasCarreta(pilaCarreta1, getLongitudListaCliente(listadoClienteCompra));  
    printf("Ingrese la cantidad de carretas en la segunda pila: ");
    generarPilasCarreta(pilaCarreta2, getLongitudListaCarreta(pilaCarreta1) + getLongitudListaCliente(listadoClienteCompra) ); 
        
    /*● Cantidad de cajas */
    printf("Ingrese la cantidad de cajas de pagos: ");
    generarListadoCaja(listadoCaja, 0);
}

int main(){
    //Instanciacion de listas
    ListadoCliente* listadoClienteEsperaCarretas;
    ListadoCliente* listadoClienteCompra;
    ListadoCliente* listadoClienteColaPago;

    ListadoCarreta* pilaCarreta1;
    ListadoCarreta* pilaCarreta2;

    ListadoCaja*    listadoCaja;

    //Inicializamos las listas
    if ((listadoClienteEsperaCarretas = (ListadoCliente *) malloc (sizeof (ListadoCliente))) == NULL) { return -1; }  
    if ((listadoClienteCompra = (ListadoCliente *) malloc (sizeof (ListadoCliente))) == NULL) { return -1; }   
    if ((listadoClienteColaPago = (ListadoCliente *) malloc (sizeof (ListadoCliente))) == NULL) { return -1; }
    if ((pilaCarreta1   = (ListadoCarreta *) malloc (sizeof (ListadoCarreta))) == NULL) { return -1; } 
    if ((pilaCarreta2   = (ListadoCarreta *) malloc (sizeof (ListadoCarreta))) == NULL) { return -1; } 
    if ((listadoCaja   = (ListadoCaja *) malloc (sizeof (ListadoCaja))) == NULL) { return -1; } 
    
    //Inicializamos las listas
    inicializacionListadoCliente (listadoClienteEsperaCarretas);
    inicializacionListadoCliente (listadoClienteCompra);
    inicializacionListadoCliente (listadoClienteColaPago);
    inicializacionListadoCarreta (pilaCarreta1);
    inicializacionListadoCarreta (pilaCarreta2);
    inicializacionListadoCaja    (listadoCaja);

    //ingresamos los datos iniciales de nodos en cada lista
    ingresarCantidadDatosListas(listadoClienteEsperaCarretas, listadoClienteCompra, listadoClienteColaPago, pilaCarreta1, pilaCarreta2, listadoCaja);


    //menu

    int opcion;
    do{
        
        printf("CLIENTES: \n");
        printf("1: \n"); 
        printf("2: \n"); 
        printf("3. \n");
        printf("4. Listar todo\n");
        printf("5: Salir\n");
        
        scanf("%d", &opcion);
        
        switch(opcion){            
            case 1: 
                
                break;
            case 2: 
                
                break;
            
            case 3:
                
                break;
            case 4: 
                //Imprimimos las listas
                printf("Cola de espera de carretas %d: ", getLongitudListaCliente(listadoClienteEsperaCarretas));
                imprimirListadoCliente(listadoClienteEsperaCarretas);
                printf("Clientes comprando %d       : ", getLongitudListaCliente(listadoClienteCompra));
                imprimirListadoCompra(listadoClienteCompra);
                printf("Cola de cola de pago %d     : ", getLongitudListaCliente(listadoClienteColaPago));
                imprimirListadoCliente(listadoClienteColaPago);
                printf("Pila de carretas 1 %d       : ", getLongitudListaCarreta(pilaCarreta1));
                imprimirListadoCarreta(pilaCarreta1);
                printf("Pila de carretas 2 %d       : ", getLongitudListaCarreta(pilaCarreta1));
                imprimirListadoCarreta(pilaCarreta2);
                printf("Listado de cajas %d       : ", getLongitudListaCaja(listadoCaja));                
                imprimirListadoCaja(listadoCaja);

                //MOVER CLIENTE LISTADO ESPERA CARRETAS A LISTA COMPRA
                printf("\n");
                Cliente* aux = extraerNodoListadoCliente(listadoClienteEsperaCarretas, 5);
                agregarCompraPorNodo(listadoClienteCompra, aux);
                printf("\n");

                //Imprimimos las listas
                printf("Cola de espera de carretas %d: ", getLongitudListaCliente(listadoClienteEsperaCarretas));
                imprimirListadoCliente(listadoClienteEsperaCarretas);
                printf("Clientes comprando %d       : ", getLongitudListaCliente(listadoClienteCompra));
                imprimirListadoCompra(listadoClienteCompra);
                printf("Cola de cola de pago %d     : ", getLongitudListaCliente(listadoClienteColaPago));
                imprimirListadoCliente(listadoClienteColaPago);
                printf("Pila de carretas 1 %d       : ", getLongitudListaCarreta(pilaCarreta1));
                imprimirListadoCarreta(pilaCarreta1);
                printf("Pila de carretas 2 %d       : ", getLongitudListaCarreta(pilaCarreta1));
                imprimirListadoCarreta(pilaCarreta2);
                printf("Listado de cajas %d       : ", getLongitudListaCaja(listadoCaja));                
                imprimirListadoCaja(listadoCaja);

                //MOVER CLIENTE LISTA COMPRA A LISTA PAGO
                printf("\n");
                Cliente* aux2 = extraerNodoListadoCompra(listadoClienteCompra, 10);
                agregarClientePorNodo(listadoClienteColaPago, aux2);
                printf("\n");

                //Imprimimos las listas
                printf("Cola de espera de carretas %d: ", getLongitudListaCliente(listadoClienteEsperaCarretas));
                imprimirListadoCliente(listadoClienteEsperaCarretas);
                printf("Clientes comprando %d       : ", getLongitudListaCliente(listadoClienteCompra));
                imprimirListadoCompra(listadoClienteCompra);
                printf("Cola de cola de pago %d     : ", getLongitudListaCliente(listadoClienteColaPago));
                imprimirListadoCliente(listadoClienteColaPago);
                printf("Pila de carretas 1 %d       : ", getLongitudListaCarreta(pilaCarreta1));
                imprimirListadoCarreta(pilaCarreta1);
                printf("Pila de carretas 2 %d       : ", getLongitudListaCarreta(pilaCarreta1));
                imprimirListadoCarreta(pilaCarreta2);
                printf("Listado de cajas %d       : ", getLongitudListaCaja(listadoCaja));                
                imprimirListadoCaja(listadoCaja);
 
                break; 
            default:               
                break;
        }

    }while(opcion > 0 && opcion < 5);    
    
    return 0;
}

