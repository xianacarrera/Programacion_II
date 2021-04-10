/* 
 * File:   matrizdinamica.h
 * Author: mariajose
 *
 * Created on 14 de enero de 2020, 12:43
 */

#ifndef MATRIZDINAMICA_H
#define MATRIZDINAMICA_H

/*Tipo de datos de los elementos de la matriz*/
typedef float TELEMENTO;            // typedef double TELEMENTO;
/*tipo opaco, los detalles de implementación están ocultos al usuario*/
typedef void * matrizD;

/* Función crear: asigna memoria y devuelve la asignación a la matriz. Recibe m1 
 * por referencia para devolver al programa principal la dirección de memoria 
 * reservada por este procedimiento*/
void crear(matrizD *m1, short nfilas, short ncolumnas);

/* Función asignar: Llena una posición de la matriz con un valor. Recibe una 
 * copia de la dirección de memoria reservada para la matriz m1*/
void asignar(matrizD *m1, short fila, short columna, TELEMENTO valor);

/* Función liberar: recibe m1 por referencia mediante un puntero y libera 
 * la memoria asignada a ella y a sus datos*/
void liberar(matrizD *m1);

/* Función recuperar: recibe una copia de m1 (pues la matriz no va a ser
 * modificada) junto con la fila y la columna del dato a devolver, que en este
 * caso es de tipo float*/
TELEMENTO recuperar(matrizD m1, short fila, short columna);

/* Función producto escalar: recibe una copia de la matriz m1 y un escalar.
 * Multiplica cada elemento por dicho escalar y devuelve la matriz resultante*/
matrizD prodescalar(matrizD m1, float esc);

/* Función nfilas: recibe una copia de m1 y devuelve su número de filas*/
short nfilas(matrizD m1);

/* Función ncolumnas: recibe una copia de m1 y devuelve su número de columnas*/
short ncolumnas(matrizD m1);

/* Función inicializar: da valores aleatorios a los elementos de una matriz*/
void inicializar(matrizD *matrix);

/* Función trasposición: traspone una matriz*/
void trasp(matrizD *result, matrizD m1);

/* Función multiplicación: multiplica dos matrices*/
void mult(matrizD *result, matrizD m1, matrizD m2);

/* Función inicializarSubMatriz: copia uno de los cuadrantes de una matriz
 * en otra*/
void inicializarSubMatriz(matrizD *submatriz, matrizD original, int cuadrante);

/* Función suma: suma dos matrices*/
void suma(matrizD *result, matrizD A, matrizD B);

/* Función matricesIguales: determina si dos matrices son iguales*/
int matricesIguales(matrizD m1, matrizD m2);

/* Función mult_divide_vencerás: multiplica dos matrices mediante la estrategia
 * de Divide y Vencerás*/
void mult_divide_venceras(matrizD *result, matrizD A, matrizD B);

#endif /* MATRIZDINAMICA_H */

