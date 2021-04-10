/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Xiana Carrera
 *
 * Created on 27 de abril de 2020, 16:24
 * Este programa multiplica dos matrices de manera convencional y mediante
 * la estrategia algorítmica Divide y Vencerás. Después, comprueba que el
 * resultado coincida.
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrizdinamica.h"

/*
 * 
 */

/*                      Respuesta a la pregunta planteada:
 * Si cambiamos el valor de 0.01 a 0.0001, nos encontramos con que el programa
 * funciona correctamente para tamaños 2, 4 y 8, pero con tamaño 16 el resultado
 * es que las matrices calculadas no son iguales. Para cualquier dimensión
 * mayor nos encontramos con la misma situación.
 * Esto se debe, fundamentalmente, a que la representación de cualquier número
 * decimal como un float o un double no es exacta, sino una aproximación. Es
 * decir, puede haber cifras que no coincidan exactamente con las del número
 * introducido. Por lo tanto, si realizamos una operación con estos valores,
 * obtendremos un resultado con un cierto error y, a mayor número de
 * operaciones, mayor será la desviación acumulada.
 * Los cálculos realizados con la función mult y mult_divide_venceras no son
 * los mismos, por lo que esos errores darán lugar a matrices diferentes, si
 * tenemos en cuenta una gran precisión decimal. Por este motivo, introducimos
 * en la función matricesIguales una comparación que depende del valor
 * precisión. Si utilizamos como precisión valores "grandes", como 0.01,
 * dejaremos un mayor margen para las diferencias, y estas no influirán
 * en el resultado. Ahora bien, si sustituimos 0.01 por 0.0001, entonces la
 * disparidad sí es significativa, al estar exigiendo que los elementos de las
 * matrices coincidan en un mayor número de cifras.
 * Este fenómeno no se percibe con tamaños inferiores a 16 porque el número de
 * operaciones no es lo suficientemente grande como para que se acumule el
 * suficiente error, y entonces los resultados pasan el "test". Si incrementamos
 * el tamaño, tanto en mult como en mult_divide_venceras se tendrán que realizar
 * más cálculos, por lo que empezamos a notar problemas.
 * La solución pasa por sustituir el tipo de los elementos de la matriz de
 * float a double (cambios en la línea 12 de matrizdinamica.h y en la línea
 * 23 de matrizdimanica.c). Esto se basa en que el tipo double tiene una
 * precisión mucho mayor que float, al admitir mayor cantidad de decimales,
 * y la representación de los números será una mejor aproximación a lo que
 * introducimos. En este caso, el error acumulado será mucho menor, pues las
 * cifras que presenten disparidad tendrán una magnitud más pequeña. Así,
 * nos encontramos con que las matrices pasan el test de comparación con
 * precisión 0.0001.
 */

void imprimir(matrizD m1);

int main(int argc, char** argv) {
    matrizD m1 = NULL, m2 = NULL, r1 = NULL, r2 = NULL;
    short n;
    
    if (argc == 2)
        n = atoi(argv[1]);      // Tamaño de las matrices
    else{
        printf("Número de argumentos incorrecto");
        exit(EXIT_FAILURE);     // Se sale del programa con un mensaje de error
    }
    
    // Creación de las 4 matrices con dimensiones n*n
    crear(&m1, n, n);
    crear(&m2, n, n);
    crear(&r1, n, n);
    crear(&r2, n, n);
    
    // Las matrices a operar se inicializan con valores aleatorios
    inicializar(&m1);
    inicializar(&m2);
    // Después, se imprimen
    printf("Matriz 1 a multiplicar:\n");
    imprimir(m1);
    printf("Matriz 2 a multiplicar:\n");
    imprimir(m2);   
    
    // Multiplicación por Divide y Vencerás
    mult_divide_venceras(&r1, m1, m2);
    printf("Resultado de la multiplicación por Divide y Vencerás:\n");
    imprimir(r1);
    
    // Multiplicación convencional
    mult(&r2, m1, m2);
    printf("Resultado de la multiplicación convencional de matrices:\n");
    imprimir(r2);
    
    // Comprobación del resultado
    if (matricesIguales(r1, r2))
        printf("El resultado es el mismo usando ambos métodos\n");
    else
        printf("Error: los resultados no coinciden\n");
    
    // Liberación de memoria
    liberar(&m1);
    liberar(&m2);
    liberar(&r1);
    liberar(&r2);
    
    return (EXIT_SUCCESS);
}

void imprimir(matrizD m1)
{
    short i, j, a, b;
    
    /* Este código recorre todas las filas y columnas de la matriz, recupera
     * cada uno de sus elementos y lo imprime por pantalla*/
    if (m1){
        a = nfilas(m1);
        b = ncolumnas(m1);
        for (i=1; i<=a; i++){ 
            for (j=1; j<=b; j++)
                printf("%f ", recuperar(m1, i, j));
            printf("\n");
        }
        printf("\n");
    } else
        printf("La matriz a imprimir no existe\n");
}
