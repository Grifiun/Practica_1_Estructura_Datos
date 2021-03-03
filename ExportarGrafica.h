/******************************************************************************

        201830313 Denilson Florentín de León Aguilar
        Estructura de datos
        Simulador MiniMarket Manager
        Entidad para generar el archivo.dot y exportar los nodos a 
        una grafica en formato png

*******************************************************************************/
#include <stdio.h>
#include "Cliente.h"
#include "Carreta.h"
#include "Compra.h"
#include "Caja.h"

#ifndef _EXPORTAR_GRAFICA_H
#define _EXPORTAR_GRAFICA_H_

/*Inicializas el archivo, si existe se sobreexcribe*/
FILE* inicializarArchivo(FILE* archivoDOT){
    archivoDOT = fopen("listas.dot", "w");
    return archivoDOT;
}

/*Cerramos el flujo del archivo*/
FILE* finalizarArchivo(FILE* archivoDOT){
    fclose (archivoDOT);
    return archivoDOT;
}

/*Una vez generado el archivo.dot se mandan comandos a la consola para que lo interprete y genere el png*/
void generarPNG(){
    system("dot -Tpng listas.dot -o listas.png");
}

/*Funcion principal*/
void exportarListas(ListadoCliente* listadoClienteEsperaCarretas, ListadoCliente* listadoClienteCompra, ListadoCliente* listadoClienteColaPago, ListadoCaja* listadoCaja, ListadoCarreta* pilaCarreta1, ListadoCarreta* pilaCarreta2){
    FILE* archivoDOT;
    //Inicializamos
    archivoDOT = fopen("listas.dot", "w");
    //Escribimos el encabezado
    fputs("digraph Grafica {\n", archivoDOT);
        //SUBGRAFO COLA DE ESPERA DE CARRETAS
        ingresarSubGrafoCliente(listadoClienteEsperaCarretas, archivoDOT, "subgraph cluster_ColaCarreta {\n", "label=\"Cola espera\"");
        //SUBGRAFO COLA DE COMPRA
        ingresarSubGrafoCliente(listadoClienteCompra, archivoDOT, "subgraph cluster_ColaCompra {\n", "label=\"Cola compra\"");
        //SUBGRAFO COLA DE PAGO
        ingresarSubGrafoCliente(listadoClienteColaPago, archivoDOT, "subgraph cluster_ColaPago {\n", "label=\"Cola pagos\"");
        //SUBGRAFO PILA DE CARRETAS 1
        ingresarSubGrafoCarreta(pilaCarreta1, archivoDOT, "subgraph cluster_Carreta1 {\n", "label=\"Pila carretas 1\"");
        //SUBGRAFO PILA DE CARRETAS 1
        ingresarSubGrafoCarreta(pilaCarreta2, archivoDOT, "subgraph cluster_Carreta2 {\n", "label=\"Pila carretas 2\"");
        //SUBGRAFO PILA DE CAJAS
        ingresarSubGrafoCaja(listadoCaja, archivoDOT, "subgraph cluster_ColaCaja {\n", "label=\"Cajas de pago\"");
    //Escribimos el fin del diagraph
    fputs("}", archivoDOT);
    //ceramos
    fclose (archivoDOT);
    generarPNG();
}

#endif //_EXPORTAR_GRAFICA_H