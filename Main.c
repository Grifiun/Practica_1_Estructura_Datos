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

/*Funcion que se usara para iniciar el programa e indicar la cantidad de nodos en cada lista*/
void ingresarCantidadDatosListas(ListadoCliente* listadoClienteEsperaCarretas, ListadoCliente* listadoClienteColaPago, ListadoCarreta* pilaCarreta1, ListadoCarreta* pilaCarreta2){
    /*       
    ● Cantidad de clientes comprando    
    ● Cantidad de cajas 
    */
    int cantidadClientesEsperaCarretas;
    int cantidadCarretasPila1;
    int cantidadCarretasPila2;
    int cantidadClientesComprando;
    int cantidadClientesColaPago;
    int cantidadCajasPago;

    /*● Cantidad clientes en cola de espera de carretas  */
    printf("\nIngrese la cantidad de clientes en la cola de espera de carretas: ");
    generarColasClientes(listadoClienteEsperaCarretas, 0);
    /*● Cantidad de clientes en cola de pagos  */
    printf("Ingrese la cantidad de clientes en la cola de pago: ");
    generarColasClientes(listadoClienteColaPago, getLongitudListaCliente (listadoClienteEsperaCarretas));

    /*● Cantidad de carretas por pila */
    printf("Ingrese la cantidad de carretas en la primera pila: ");
    generarPilasCarreta(pilaCarreta1, 0);  
    printf("Ingrese la cantidad de carretas en la segunda pila: ");
    generarPilasCarreta(pilaCarreta2, getLongitudListaCarreta(pilaCarreta1)); 
        
/*
    printf("\nIngrese la cantidad de clientes comprando: ");
    scanf("%d", &cantidadClientesComprando);
    
    printf("\nIngrese la cantidad de cajas de pagos: ");
    scanf("%d", &cantidadCajasPago);
*/



}

int main(){
    //Instanciacion de listas
    ListadoCliente* listadoClienteEsperaCarretas;
    ListadoCliente* listadoClienteColaPago;

    ListadoCarreta* pilaCarreta1;
    ListadoCarreta* pilaCarreta2;

    //Inicializamos las listas
    
    if ((listadoClienteEsperaCarretas = (ListadoCliente *) malloc (sizeof (ListadoCliente))) == NULL) { return -1; }   
    if ((listadoClienteColaPago = (ListadoCliente *) malloc (sizeof (ListadoCliente))) == NULL) { return -1; }
    if ((pilaCarreta1   = (ListadoCarreta *) malloc (sizeof (ListadoCarreta))) == NULL) { return -1; } 
    if ((pilaCarreta2   = (ListadoCarreta *) malloc (sizeof (ListadoCarreta))) == NULL) { return -1; } 
    
    //Inicializamos las listas
    InicializacionListadoCliente (listadoClienteEsperaCarretas);
    InicializacionListadoCliente (listadoClienteColaPago);
    InicializacionListadoCarreta (pilaCarreta1);
    InicializacionListadoCarreta (pilaCarreta2);

    //ingresamos los datos iniciales de nodos en cada lista
    ingresarCantidadDatosListas(listadoClienteEsperaCarretas, listadoClienteColaPago, pilaCarreta1, pilaCarreta2);


    //menu

    int opcion;
    do{
        /*
        printf("CLIENTES: \n");
        printf("1: Listar clientes en espera de las carretas\n"); 
        printf("2: Listar clientes en cola de pago\n"); 
        printf("3. Listar carretas\n");
        printf("4: Salir\n");*/
        
        scanf("%d", &opcion);
        
        switch(opcion){            
            case 1: 
                printf("\n\nLISTADO CLIENTES EN ESPERA DE LAS CARRETAS\n");
                ImprimirListadoCliente(listadoClienteEsperaCarretas);
                break;
            case 2: 
                printf("\n\nLISTADO CLIENTES EN COLA DE PAGO\n");
                ImprimirListadoCliente(listadoClienteColaPago);
                break;
            
            case 3:
                printf("\n\nPILAS DE CARRETAS\n");
                //imprimimos la pila 1
                printf("PILA 1: ");
                ImprimirListadoCarreta(pilaCarreta1);
                //imprimimos la pila 2
                printf("PILA 2: ");
                ImprimirListadoCarreta(pilaCarreta2);
                break;
            default:
                //Imprimimos las listas
                printf("Cola de espera de carretas: ");
                ImprimirListadoCliente(listadoClienteEsperaCarretas);
                printf("Cola de cola de pago      : ");
                ImprimirListadoCliente(listadoClienteColaPago);
                printf("Pila de carretas 1        : ");
                ImprimirListadoCarreta(pilaCarreta1);
                printf("Pila de carretas 2        : ");
                ImprimirListadoCarreta(pilaCarreta2);
                break;
        }

    }while(opcion > 0 && opcion < 5);    
    
    return 0;
}

