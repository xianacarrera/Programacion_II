#include "matriz.h"

matriz* producto(matriz *M1, matriz *M2) {
    matriz *aux = 0;
    int i, k, l;
    if (M1 != 0 && M2 != 0) {
        if (M1->columnas != M2->filas) {    //if (M1->filas != M2->columnas) {
            printf("El numero de columnas de la primera matriz y de filas de la segunda deben ser iguales\n");
            return aux;
        }

        aux = crearMatriz(M1->filas, M2->columnas);
        if (aux)    
            //Se debería comprobar que la reserva de memoria haya funcionado.
            //En caso contrario, aux valdrá 0 y crearMatriz mostrará un mensaje de error.
            for (i = 0; i < M1->filas; i++)
                for (k = 0; k < M2->columnas; k++) {
                    //*(aux->datos + i * M2->columnas + k) = 0;
                    // (Se puede eliminar la línea porque crearMatriz ya inicializa todos los valores de aux a 0).
                    for (l = 0; l < M1->columnas; l++) {
                        *(aux->datos + i * M2->columnas + k) += *(M1->datos + i * M1->columnas + l) * *(M2->datos + l * M2->columnas + k);
                    }
                }

        //return aux;
        //Esta secuencia se ha movido al final para que la función siempre devuelva una matriz, por coherencia con su tipo.
    } else
        printf("Alguna de las matrices no existe\n");
    
    return aux;
}
