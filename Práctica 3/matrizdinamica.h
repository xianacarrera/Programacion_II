/* 
 * File:   matrizdinamica.h
 * Author: mariajose
 *
 * Created on 14 de enero de 2020, 12:43
 */

#ifndef MATRIZDINAMICA_H
#define MATRIZDINAMICA_H

/*Tipo de datos de los elementos de la matriz*/
typedef float TELEMENTO;
/*tipo opaco, los detalles de implementación están ocultos al usuario*/
typedef void * matrizP;

/* Función crear: asigna memoria y devuelve la asignación a la matriz. Recibe m1 
 * por referencia para devolver al programa principal la dirección de memoria 
 * reservada por este procedimiento*/
void crear(matrizP *m1, short nfilas, short ncolumnas);

/* Función asignar: Llena una posición de la matriz con un valor. Recibe una 
 * copia de la dirección de memoria reservada para la matriz m1*/
void asignar(matrizP *m1, short fila, short columna, TELEMENTO valor);

/* Función liberar: recibe m1 por referencia mediante un puntero y libera 
 * la memoria asignada a ella y a sus datos*/
void liberar(matrizP *m1);

/* Función recuperar: recibe una copia de m1 (pues la matriz no va a ser
 * modificada) junto con la fila y la columna del dato a devolver, que en este
 * caso es de tipo float*/
TELEMENTO recuperar(matrizP m1, short fila, short columna);

/* Función producto escalar: recibe una copia de la matriz m1 y un escalar.
 * Multiplica cada elemento por dicho escalar y devuelve la matriz resultante*/
matrizP prodescalar(matrizP m1, float esc);

/* Función nfilas: recibe una copia de m1 y devuelve su número de filas*/
short nfilas(matrizP m1);

/* Función ncolumnas: recibe una copia de m1 y devuelve su número de columnas*/
short ncolumnas(matrizP m1);

/* Función inicializar: da valores aleatorios a los elementos de una matriz*/
void inicializar(matrizP *matrix);

/* Función trasposición: traspone una matriz*/
void trasp(matrizP *result, matrizP m1);

/* Función multiplicación: multiplica dos matrices*/
void mult(matrizP *result, matrizP m1, matrizP m2);

#endif /* MATRIZDINAMICA_H */

