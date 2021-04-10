/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   matrizdinamica.c
 * Author: Xiana
 *
 * Created on 15 de febrero de 2020, 21:18
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

/*Se vuelve a definir el tipo de datos que contiene la matriz*/
typedef float TELEMENTO;

/*Implementación del TAD matrizP */
typedef struct {
    TELEMENTO *datos;   /*valores de la matriz*/
    short nfilas,ncols; /*tamaño de la matriz (filas, columnas)*/
}STMATRIZ;              /*definición del tipo de datos estructura*/
typedef STMATRIZ *matrizP; /*puntero a estructura*/

/*Funciones de manipulación de datos */
/*Función crear: asigna memoria y devuelve la asignación a la matriz*/
void crear(matrizP *m1, short tamf, short tamc)
{
    long i;
    
    if (tamf <= 0 || tamc <= 0){
        *m1 = NULL;
        printf("El número de filas y el de columnas deben ser positivos\n");
    }
    else{
        *m1=(matrizP)malloc(sizeof(STMATRIZ));
        if (*m1){
            (*m1)->datos=(TELEMENTO*)malloc(tamf*tamc*sizeof(TELEMENTO));
            (*m1)->nfilas=tamf; (*m1)->ncols=tamc;
            for(i = 1; i <= tamf*tamc; i++)
                /*Inicialización a 0 de las componentes de la matriz*/
                *((*m1)->datos+i-1) = 0;
        }
        else 
            printf("Error en la reserva de memoria para la matriz\n");
    }
}

/*Función asignar: Asigna un valor a una posición de la matriz */
void asignar(matrizP *m1, short fila, short columna, TELEMENTO valor){
    *((*m1)->datos + (fila-1)*(*m1)->ncols + columna-1)=valor;
}

/*Función liberar: Libera la memoria ocupada por la matriz*/
void liberar(matrizP *m1)
{
    if(*m1){    //Comprobación de que la matriz haya sido creada correctamente.
        if ((*m1)->datos){
            free((*m1)->datos);
            (*m1)->datos = NULL;
        }
        free(*m1);
        *m1 = NULL;
    }    
}

/* Función recuperar: Devuelve el valor que se encuentra en la posición seleccionada*/ 
TELEMENTO recuperar(matrizP m1, short fila, short columna)
{
    TELEMENTO valor;
    
    if (m1){
        if ((fila <= 0 || fila > m1->nfilas) || (columna <= 0 || columna > m1->ncols)) {
            printf("El elemento elegido no existe\n");
            return 0;
        }
        
        valor = *((m1->datos) + (fila-1) * (m1->ncols) + (columna-1));
        return valor;
    }
    
    return 0;
}

/* Función prodescalar: multiplica la matriz por un escalar*/
matrizP prodescalar(matrizP m1, float esc)
{
    matrizP aux = NULL;
    short i, j;
    
    if (m1){
        crear(&aux, m1->nfilas, m1->ncols);
        if (aux) 
            for (i = 0; i < m1->nfilas; i++)
                for (j = 0; j < m1->ncols; j++)
                    *((aux->datos) + i * (aux->ncols) + j) = *((m1->datos) + i * (m1->ncols) + j) * esc;
    } else
        printf("La matriz no existe\n");
    
    return aux;
}

/* Función nfilas: devuelve el número de filas de la matriz*/
short nfilas(matrizP m1)
{
    if (m1)
        return m1->nfilas;
    else
        return 0;
}

/* Función ncolumnas: devuelve el número de columnas de la matriz*/
short ncolumnas(matrizP m1)
{
    if (m1)
        return m1->ncols;
    else
        return 0;
}

/* Función inicializar: da valores aleatorios a cada elemento*/
void inicializar(matrizP *matrix)
{
    short i, j;
    TELEMENTO element;
    
    if (*matrix){       // Se comprueba que la matriz ya haya sido creada
        for (i = 1; i <= (*matrix)->nfilas; i++)
            for (j = 1; j <= (*matrix)->ncols; j++){
                // Se recorren todas las filas y columnas
                element = 10.0 * (TELEMENTO) rand() / RAND_MAX;
                // Se genera un float entre 0 y 10 al azar
                asignar(matrix, i, j, element);     // Se guarda en la matriz
            }
    } else          // La función envía un mensaje de error
        printf("La matriz no existe\n");
}

/* Función trasp: traspone una matriz*/
void trasp(matrizP *result, matrizP m1)
{
    short i, j;
    TELEMENTO elem;
    
    if(m1 && *result)    // Se comprueba que ambas matrices hayan sido creadas
        /* El número de filas de result debe ser el número de columnas de m1 y
         * su número de columnas, las filas de m1*/
        if (m1->nfilas == (*result)->ncols && m1->ncols == (*result)->nfilas)
            for (i = 1; i <= m1->nfilas; i++)
                for (j = 1; j <= m1->ncols; j++){
                    elem = recuperar(m1, i, j);
                    asignar(result, j, i, elem);      
                    /* Los elementos de m1 de la fila i y la columna j se
                     * almacenan en la fila j y la columna i de result*/
                }
        else
            printf("La matriz para el resultado no tiene las dimensiones "
                    "adecuadas\n");           
    else
        printf("Las matrices deben haber sido creadas\n");
}

/* Función mult: multiplica dos matrices*/
void mult(matrizP *result, matrizP m1, matrizP m2)
{
    short i, j, k;
    TELEMENTO elem1, elem2, tot = 0;
    
    if (m1 && m2 && *result)        // Se comprueba que las matrices existan
        if (m1->ncols == m2->nfilas)
            if (((*result)->nfilas == m1->nfilas) && 
                    ((*result)->ncols == m2->ncols))
                // Se realizan 2 if separados para especificar un error concreto
                
                for (i = 1; i <= (*result)->nfilas; i++)
                    for (j = 1; j <= (*result)->ncols; j++){
                        tot = 0;    
                        // Se reinicia tot para cada elemento de result
                        for (k = 1; k <= m1->ncols; k++){
                            /* Se recorren las filas de la primera matriz, las
                             * columnas de la segunda y las columnas de la
                             * primera (que coinciden con las filas de la
                             * segunda)*/
                            elem1 = recuperar(m1, i, k);
                            elem2 = recuperar(m2, k, j);
                            // Se multiplican los datos y se van sumando
                            tot += elem1 * elem2;  
                        }
                        asignar(result, i, j, tot);
                        // Se guarda el total calculado en result
                    }
            else
                printf("La matriz para el resultado no tiene las dimensiones "
                        "adecuadas\n"); 
        else
            printf("El número de columnas de la primera matriz no coincide con"
                    " el número de filas de la segunda matriz\n");         
    else
        printf("Las matrices deben haber sido creadas\n");
}