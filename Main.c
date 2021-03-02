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
#include "NumeroAleatorio.h"

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
    generarColasClientes(listadoClienteEsperaCarretas, 0, 0, 0);
    /*● Cantidad de clientes comprando  */
    printf("Ingrese la cantidad de clientes comprando: ");
    generarListaCircularCompra(listadoClienteCompra, getLongitudListaCliente (listadoClienteEsperaCarretas), 0);//el 0 es porque en la lista de esperas no hay carritos
    /*● Cantidad de clientes en cola de pagos  */
    printf("Ingrese la cantidad de clientes en la cola de pago: ");
    generarColasClientes(listadoClienteColaPago, getLongitudListaCliente (listadoClienteEsperaCarretas) + getLongitudListaCliente(listadoClienteCompra), 1, getLongitudListaCliente(listadoClienteCompra));//asignamos los carritos de las compras

    /*● Cantidad de carretas por pila */ //Iniciamos los ids de las carretas considerando los que tienen los clientes comprando y pagando
    printf("Ingrese la cantidad de carretas en la primera pila: ");
    generarPilasCarreta(pilaCarreta1, getLongitudListaCliente(listadoClienteCompra) +  getLongitudListaCliente(listadoClienteColaPago));  
    printf("Ingrese la cantidad de carretas en la segunda pila: ");
    generarPilasCarreta(pilaCarreta2, getLongitudListaCarreta(pilaCarreta1) + getLongitudListaCliente(listadoClienteCompra) +getLongitudListaCliente(listadoClienteColaPago)); 
        
    /*● Cantidad de cajas */
    printf("Ingrese la cantidad de cajas de pagos: ");
    generarListadoCaja(listadoCaja, 0);
}
/*1. Ingreso de clientes en la lista de espera a la lista de compras, siempre que hayan pilas  */
void listaEsperaACompra(ListadoCarreta* pilaCarreta1, ListadoCarreta* pilaCarreta2, ListadoCliente* listadoClienteEsperaCarretas, ListadoCliente* listadoClienteCompra){    
    while(pilaCarreta1->longitud + pilaCarreta2->longitud > 0 && listadoClienteEsperaCarretas->longitud > 0){//Si hay carretas en las 2 pilas
        //agregamos una carreta al cliente
        Carreta* carretaAux = sacarPrimeraCarretaDisponible(pilaCarreta1, pilaCarreta2);                   

        if(carretaAux != NULL){//si obtuvo una carreta, se agrega a la lista de compras
            Cliente* aux = extraerNodoListadoCliente(listadoClienteEsperaCarretas, listadoClienteEsperaCarretas->inicio->id);
            aux->carreta = carretaAux;
            agregarCompraPorNodo(listadoClienteCompra, aux);
            printf("El cliente %d entra a la cola de compras con el carrito %d\n", aux->id, aux->carreta->id);
        }else{
            break;
        }
    }
}
/*2. Mover clientes de la lista de compras a la lista de pago, se saca uno de forma aleatoria */
void listaCompraAPago(ListadoCliente* listadoClienteCompra, ListadoCliente* listadoClienteColaPago){
    int idClienteRandom = getNumeroAleatorio(1,100);
    Cliente* aux2 = extraerNodoListadoCompra(listadoClienteCompra, idClienteRandom);

    if(aux2 != NULL){//si existe el usuario con el id generado de forma aleatoria
        printf("El cliente %d con carrito %d decidio que comprar y se unio a la cola de pago\n", aux2->id, aux2->carreta->id);
        agregarClientePorNodo(listadoClienteColaPago, aux2);
    }else{
        printf("Ningun cliente abandono la lista de compras\n");
    }
}

/*3. Mover a los clientes de las colas de pago a las cajas disponibles*/
void listaPagoACaja(ListadoCliente* listaClienteColaPago, ListadoCaja* listadoCaja){

    for(int i = 0; i < listadoCaja->longitud; i++){
        //MOVER CLIENTE LISTA PAGO A CAJA
        if(listaClienteColaPago->inicio != NULL){//si hay clientes en ese listado
            Caja* cajaAux = obtenerCajaConId(listadoCaja, i + 1);

            if(cajaAux != NULL && cajaAux->estado == 0){//si se recibio un nodo caja exitoso y esta libre
                Cliente* aux3 = extraerNodoListadoCliente(listaClienteColaPago, listaClienteColaPago->inicio->id);
                agregarNodoClienteCaja(cajaAux, aux3);
                printf("La caja %d atiende al cliente %d con el carrito %d\n", cajaAux->id, aux3->id, aux3->carreta->id);
                cajaAux->tiempoServicioCompletado = 0;
            }

        }else{
            //Ya no hay clientes que agregar, se termina el ciclo
            break;
        }
    }
}

/*4. Terminar de darle el servicio al cliente en las cajas ocupadas*/
void servicioClienteEnCajaTerminado(ListadoCaja* listadoCaja, ListadoCarreta* pilaCarreta1, ListadoCarreta* pilaCarreta2){
    //DESPACHAR AL CLIENTE Y COLOCAR LA CARRETA EN LAS PILAS
    //Obtenemos la carreta
     for(int i = 0; i < listadoCaja->longitud; i++){
        //MOVER CLIENTE LISTA PAGO A CAJA
        Caja* cajaAux = obtenerCajaConId(listadoCaja, i + 1);//obtenemos la caja auxiliar
        //Condiciones
        //1. Si la caja no esta vacia
        //2. Si la caja esta ocupada
        //3. Si el tiempo de servicio es divisible entre entre el numero
        if(cajaAux != NULL && cajaAux->estado == 1){//se despacha            
            if(cajaAux->tiempoServicioCompletado == cajaAux->tiempoServicio){//ya paso los turnos necesarios para despachar al cliente                 
                //despues de despachar, hay que reiniciar el tiempo de servicio completado
                printf("La caja %d ya paso %d turnos atendiendo al cliente %d con la carreta %d, el cliente se marcha y se agrega la carreta a las pilas \n", cajaAux->id, cajaAux->tiempoServicio, cajaAux->cliente->id, cajaAux->cliente->carreta->id);
                //despachamos al cliente y retornamos la carreta a las pilas
                despacharClienteCajaYAgregarCarretaPilas(listadoCaja, i + 1, pilaCarreta1, pilaCarreta2);
            }
            cajaAux->tiempoServicioCompletado = cajaAux->tiempoServicioCompletado + 1;//Agregamos el tiempo completado
        }
    }

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
    int paso = 1;
    do{
        printf("1. Hacer simulacion\n");
        printf("2. Listar todo\n");
        printf("otro: Salir\n");
        
        scanf("%d", &opcion);
        
        switch(opcion){   
            case 1: 
                printf("\n***************************************** PASO %d ***********************************************\n", paso);
                //Simulacion
                //1. Ingreso de clientes en la lista de espera a la lista de compras, siempre que hayan pilas   
                listaEsperaACompra(pilaCarreta1, pilaCarreta2, listadoClienteEsperaCarretas, listadoClienteCompra);
                //2. Mover clientes de la lista de compras a la lista de pago, se saca uno de forma aleatoria
                listaCompraAPago(listadoClienteCompra, listadoClienteColaPago); 
                //3. Mover clientes a las cajas disponibles
                listaPagoACaja(listadoClienteColaPago, listadoCaja);
                //4. Terminar de darle el servicio al cliente en las cajas ocupadas
                servicioClienteEnCajaTerminado(listadoCaja, pilaCarreta1, pilaCarreta2);
                paso++;
                break;
            case 2:
                //Imprimimos las listas
                printf("Cola de espera de carretas %d: ", getLongitudListaCliente(listadoClienteEsperaCarretas));
                imprimirListadoCliente(listadoClienteEsperaCarretas);
                printf("Clientes comprando %d       : ", getLongitudListaCliente(listadoClienteCompra));
                imprimirListadoCliente(listadoClienteCompra);
                printf("Cola de cola de pago %d     : ", getLongitudListaCliente(listadoClienteColaPago));
                imprimirListadoCliente(listadoClienteColaPago);                
                printf("Listado de cajas %d       : ", getLongitudListaCaja(listadoCaja));                
                imprimirListadoCaja(listadoCaja);
                printf("Pila de carretas 1 %d       : ", getLongitudListaCarreta(pilaCarreta1));
                imprimirListadoCarreta(pilaCarreta1);
                printf("Pila de carretas 2 %d       : ", getLongitudListaCarreta(pilaCarreta2));
                imprimirListadoCarreta(pilaCarreta2);
                break; 
            default:               
                break;
        }

    }while(opcion > 0 && opcion < 3);    
    
    return 0;
}

