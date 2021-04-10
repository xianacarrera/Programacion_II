/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   matrizdinamica.c
 * Author: Xiana Carrera
 *
 * Created on 15 de febrero de 2020, 21:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 
 */

/*Se vuelve a definir el tipo de datos que contiene la matriz*/
typedef float TELEMENTO;            // typedef double TELEMENTO;

/*Implementación del TAD matrizD */
typedef struct {
    TELEMENTO *datos;   /*valores de la matriz*/
    short nfilas,ncols; /*tamaño de la matriz (filas, columnas)*/
}STMATRIZ;              /*definición del tipo de datos estructura*/
typedef STMATRIZ *matrizD; /*puntero a estructura*/

/*Funciones de manipulación de datos */
/*Función crear: asigna memoria y devuelve la asignación a la matriz*/
void crear(matrizD *m1, short tamf, short tamc)
{
    long i;
    
    if (tamf <= 0 || tamc <= 0){
        *m1 = NULL;
        printf("El número de filas y el de columnas deben ser positivos\n");
    }
    else{
        *m1=(matrizD)malloc(sizeof(STMATRIZ));
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
void asignar(matrizD *m1, short fila, short columna, TELEMENTO valor){
    *((*m1)->datos + (fila-1)*(*m1)->ncols + columna-1)=valor;
}

/*Función liberar: Libera la memoria ocupada por la matriz*/
void liberar(matrizD *m1)
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
TELEMENTO recuperar(matrizD m1, short fila, short columna)
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
matrizD prodescalar(matrizD m1, float esc)
{
    matrizD aux = NULL;
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
short nfilas(matrizD m1)
{
    if (m1)
        return m1->nfilas;
    else
        return 0;
}

/* Función ncolumnas: devuelve el número de columnas de la matriz*/
short ncolumnas(matrizD m1)
{
    if (m1)
        return m1->ncols;
    else
        return 0;
}

/* Función inicializar: da valores aleatorios a cada elemento*/
void inicializar(matrizD *matrix)
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
void trasp(matrizD *result, matrizD m1)
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
void mult(matrizD *result, matrizD m1, matrizD m2)
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

/* Función inicializarSubMatriz: copia uno de los cuadrantes de una matriz
 * en otra cuyo tamaño es la mitad que el de la original*/
void inicializarSubMatriz(matrizD *submatriz, matrizD original, int cuadrante)
{
    short i, j;
    
    if (*submatriz) // Ya se comprueba que original existe en mult_div_ven
        if ((*submatriz)->nfilas == original->nfilas/2 &&
                (*submatriz)->ncols == original->ncols/2)
            /* Se comprueba que submatriz tenga la mitad de filas y de columnas 
             *que original*/
            if (cuadrante == 1)
                for (i = 1; i <= original->nfilas/2; i++)
                    for (j = 1; j <= original->ncols/2; j++)
                        asignar(submatriz, i, j, recuperar(original, i, j));
                    /* El primer cuadrante abarca la primera mitad de las filas
                     * de original y la primera mitad de sus columnas*/

            else if (cuadrante == 2)
                    for (i = 1; i <= original->nfilas/2; i++)
                        for (j = original->ncols/2 + 1; j <= original->ncols; j++)
                            asignar(submatriz, i, j - original->ncols/2,
                                    recuperar(original, i, j));
                    /* El segundo cuadrante abarca la primera mitad de las filas
                     * de original y la segunda mitad de sus columnas*/

            else if (cuadrante == 3) 
                for (i = original->nfilas/2 + 1; i <= original->nfilas; i++)
                    for (j = 1; j <= original->ncols/2; j++)
                        asignar(submatriz, i - original->nfilas/2, j,
                                recuperar(original, i, j));
                    /* El tercer cuadrante abarca la segunda mitad de las filas
                     * de original y la primera mitad de sus columnas*/            

            else if (cuadrante == 4)
                for (i = original->nfilas/2 + 1; i <= original->nfilas; i++)
                    for (j = original->ncols/2 + 1; j <= original->ncols; j++)
                        asignar(submatriz, i - original->nfilas/2,
                                j - original->ncols/2, recuperar(original, i, j));
                    /* El cuarto cuadrante abarca la segunda mitad de las filas
                     * de original y la segunda mitad de sus columnas*/        

            else
                printf("Error: el cuadrante introducido debe ser 1, 2, 3 o 4\n");

        else
            printf("Error: la submatriz debe tener la mitad del tamaño de la "
                    "matriz original\n");  
    else
        printf("Error: la submatriz debe existir\n");
}

/* Función suma: suma dos matrices*/
void suma(matrizD *result, matrizD A, matrizD B)
{
    short i, j;
    
    if (A && B && *result)
        if (A->nfilas == B->nfilas && A->ncols == B->ncols &&
                A->nfilas == (*result)->nfilas && A->ncols == (*result)->ncols)
            /* Se comprueba que A, B y result tengan el mismo número de 
             * filas y columnas. Si se pasan las dos primeras igualdades,
             * bastará ver también que las dimensiones de A (o B) y result
             * coinciden para obtener que B (o A) y result también lo hacen*/
            for (i = 1; i <= (*result)->nfilas; i++)   // Recorre las filas
                for (j = 1; j <= (*result)->ncols; j++) // Recorre las columnas
                    asignar(result, i, j, recuperar(A, i, j) + recuperar(B, i, j));
            // Se suman los elementos de A y B uno a uno, recorriéndolos todos.
        else
            printf("Todas las matrices deben tener el mismo tamaño\n");            
    else
        printf("Las matrices deben haber sido creadas\n");     
}

/* Función matricesIguales: determina si dos matrices son iguales 
 * comparándolas elemento a elemento*/
int matricesIguales(matrizD m1, matrizD m2)
{
    short i, j;
    float prc = 0.01;     // Valor de precisión deseado
    
    if (m1 && m2){
        // Si los tamaños de m1 y m2 no coinciden, automáticamente son distintas
        if (m1->nfilas == m2->nfilas && m1->ncols == m2->ncols){
            // A continuación se recorren todas las filas y columnas
            for (i = 1; i <= m1->nfilas; i++)
                for(j = 1; j <= m1->ncols; j++)
                    if (fabs(recuperar(m1, i, j) - recuperar(m2, i, j)) > prc)
                        return 0;          
                    /* El valor absoluto de la diferencia de los elementos se
                     * compara con precisión. Si su diferencia es demasiado
                     * grande, se considera que no son iguales*/
            return 1;       // Se han superado todas las comprobaciones
        } else
            return 0;
    } else{
        printf("Las matrices deben haber sido creadas\n");
        return 0;
    }
}

/* Función mult_divide_vencerás: multiplica dos matrices mediante la estrategia
 * de Divide y Vencerás*/
void mult_divide_venceras(matrizD *result, matrizD A, matrizD B)
{
    matrizD A1 = NULL, A2 = NULL, A3 = NULL, A4 = NULL, B1 = NULL, B2 = NULL,
            B3 = NULL, B4 = NULL, C1 = NULL, C2 = NULL, C3 = NULL, C4 = NULL,
            aux = NULL;
    short i, j;
    
    if (A && B && (*result))    // Las matrices deben haber sido creadas
        if (A->nfilas == A->ncols && B->nfilas == B->ncols && 
                (*result)->nfilas == (*result)->ncols && A->nfilas == B->nfilas
                && B->nfilas == (*result)->nfilas && 
                (A->nfilas & (A->nfilas-1)) == 0){
                /* Se comprueba, en primer lugar, que A, B y result sean 
                 * matrices cuadradas. Si se pasan los tres and, se comprueba 
                 * que tengan el mismo tamaño (basta ver que coincida el número 
                 * de filas, pues este es igual al número de columnas en cada 
                 * matriz). Finalmente, partiendo de la suposición de que tienen
                 * la misma dimensión, se estudia si esta es potencia de 2*/
            if (A->nfilas == 2)     mult(result, A, B);    
            // 2 es el valor umbral (con este tamaño se multiplica directamente)
            else{
                // Se crea e inicializa cada submatriz cuadrante
                crear(&A1, A->nfilas/2, A->nfilas/2);
                crear(&A2, A->nfilas/2, A->nfilas/2);
                crear(&A3, A->nfilas/2, A->nfilas/2);
                crear(&A4, A->nfilas/2, A->nfilas/2);            
                crear(&B1, A->nfilas/2, A->nfilas/2);
                crear(&B2, A->nfilas/2, A->nfilas/2);
                crear(&B3, A->nfilas/2, A->nfilas/2);
                crear(&B4, A->nfilas/2, A->nfilas/2);

                inicializarSubMatriz(&A1, A, 1);
                inicializarSubMatriz(&A2, A, 2);
                inicializarSubMatriz(&A3, A, 3);
                inicializarSubMatriz(&A4, A, 4);
                inicializarSubMatriz(&B1, B, 1);
                inicializarSubMatriz(&B2, B, 2);
                inicializarSubMatriz(&B3, B, 3);
                inicializarSubMatriz(&B4, B, 4);

                // Se crean las submatrices para los cuadrantes del resultado
                crear(&C1, A->nfilas/2, A->nfilas/2);
                crear(&C2, A->nfilas/2, A->nfilas/2);
                crear(&C3, A->nfilas/2, A->nfilas/2);
                crear(&C4, A->nfilas/2, A->nfilas/2);
                crear(&aux, A->nfilas/2, A->nfilas/2);  // Auxiliar

                mult_divide_venceras(&C1, A1, B1);      // A1*B1
                mult_divide_venceras(&aux, A2, B3);     // A2*B3   
                suma(&C1, C1, aux);         // A1*B1 + A2*B3
                mult_divide_venceras(&C2, A1, B2);      // A1*B2
                mult_divide_venceras(&aux, A2, B4);     // A2*B4
                suma(&C2, C2, aux);         // A1*B2 + A2*B4
                mult_divide_venceras(&C3, A3, B1);      // A3*B1
                mult_divide_venceras(&aux, A4, B3);     // A4*B3
                suma(&C3, C3, aux);         // A3*B1 + A4*B3
                mult_divide_venceras(&C4, A3, B2);      // A3*B2
                mult_divide_venceras(&aux, A4, B4);     // A4*B4
                suma(&C4, C4, aux);         // A3*B2 + A4*B4

                /* Se copian las submatrices en C siguiendo un método
                 * análogo al de inicializarSubMatriz*/
                for (i = 1; i <= A->nfilas; i++)
                    for (j = 1; j <= A->ncols; j++)
                        if (i <= A->nfilas/2 && j <= A->ncols/2)
                            asignar(result, i, j, recuperar(C1, i, j));
                        else if (i <= A->nfilas/2 && j > A->ncols/2)
                            asignar(result, i, j, 
                                    recuperar(C2, i, j - A->ncols/2));
                        else if (i > A->nfilas/2 && j <= A->ncols/2)
                            asignar(result, i, j, 
                                    recuperar(C3, i - A->nfilas/2, j));
                        else
                            asignar(result, i, j, recuperar(C4, i - A->nfilas/2, 
                                    j - A->ncols/2));

                liberar(&A1);
                liberar(&A2);
                liberar(&A3);
                liberar(&A4);
                liberar(&B1);
                liberar(&B2);
                liberar(&B3);
                liberar(&B4);
                liberar(&C1);
                liberar(&C2);
                liberar(&C3);
                liberar(&C4);
                liberar(&aux);
            } 
        } else
            printf("Error: Las matrices deben ser cuadradas y tener el mismo "
                    "tamaño, que debe que ser potencia de 2\n");  
    else
        printf("Error: las matrices deben haber sido creadas\n");     
}
