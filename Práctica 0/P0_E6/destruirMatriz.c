#include "matriz.h"

/* He optado por usar dobles punteros en lugar de un puntero normal. El motivo 
 * es que al terminar la función destruirMatriz debemos igualar a 0 la matriz 
 * que se ha liberado. Si no lo hiciésemos, podría haber un error fatal, por 
 * ejemplo, si utilizamos la opción 7 del menú dos veces seguidas, pues en la
 * segunda, M sería un valor aleatorio y podría detectarse M != 0. Entonces, se
 * haría free(M) y el programa fallaría.
 * 
 * Otra opción sería declarar el puntero a la matriz a 0 dentro del main,
 * pero he preferido modificar destruirMatriz para que sea un código más
 * completo y compacto.
 * 
 */

void destruirMatriz(matriz **M) {    //void destruirMatriz(matriz *M) {
    if (*M != 0) {   //if (M != 0) {
        free((*M)->datos); //free(M->datos);
        free(*M);    //free(M);
        *M = 0;
    }
}
