/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Xiana Carrera
 *
 * Created on 8 de abril de 2020, 21:06
 * Este programa mide el tiempo de ejecución de las operaciones de
 * trasposición y multiplicación sobre matrices de distintos tamaños.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrizdinamica.h"

/*
 * 
 */

int main(int argc, char** argv) {
    matrizP mat = NULL, mat2 = NULL, res = NULL;
    clock_t inicio = -1, fin = -1;
    short n, tin, tfin, paso;
    char opc;
    
    FILE *fp;   
    
    // Primero se comprueba que el número de argumentos sea correcto
    if (argc == 5){ 
        tin = atoi(argv[1]);
        tfin = atoi(argv[2]);
        paso = atoi(argv[3]);
        opc = argv[4][0];
        /* tin, tfin y paso son cantidades numéricas, por lo que se usa la
         * función atoi para convertir cada cadena de caracteres de argv en un
         * int. opc es un char, así que solo se coge el primer elemento de la 
         * cadena correpondiente*/
    } else{
        printf("Número de argumentos incorrecto. Finalizando programa...");
        exit(EXIT_FAILURE);        // Se cierra el programa
    }
                
    if (opc == 't'){        // Trasposición
        fp = fopen("out_trasp.txt", "w");
        /* Se abre el archivo donde se guardarán los resultados en modo
         * escritura (si ya existía, se sobreescribe, si no, se crea)*/

        for (n = tin; n <= tfin; n += paso){
            /* Se recorren tamaños que van desde tin hasta tfin, incrementándose
             * estos en cada iteración en la cantidad definida por paso*/
            
            crear(&mat, n, n/2);    // Se crea una matriz de tamaño n*n/2
            inicializar(&mat);      // Se le dan valores aleatorios
            crear(&res, n/2, n);    // Resultado: matriz de n/2*n
            
            /* Medición del tiempo: se guarda el tiempo inicial, se realiza la
             * operación y se guarda el tiempo nada más acabar esta*/
            inicio = clock();
            trasp(&res, mat);
            fin = clock();

            printf("n:%hi\tt(n):%.4lf\tini.:%d\tfin:%d\n", n, 
                    (fin - inicio) / (double) CLOCKS_PER_SEC, (int) inicio, 
                    (int) fin);
            /* Se imprime por pantalla el número de filas de la matriz, el
             * tiempo empleado en la trasposición, el número de periodos de 
             * reloj inicial y el número de periodos final*/
            fprintf(fp, "%hi\t%.4lf\n", n, (fin - inicio) / 
                    (double) CLOCKS_PER_SEC);
            /* Se guardan los resultados en el archivo de texto, con dos
             * columnas: una con el tamaño de la matriz y otra con su respectivo
             * tiempo*/

            // Liberación de las dos matrices empleadas
            liberar(&mat);
            liberar(&res);
        }
    } else if (opc == 'm'){     // Multiplicación
        fp = fopen("out_mult.txt", "w");
        // Se abre el correspondiente archivo de texto en modo escritura
        
        for (n = tin; n <= tfin; n += paso){
            crear(&mat, n, n);      // Se crea una matriz de tamaño n*n
            inicializar(&mat);      // Se le dan valores aleatorios
            crear(&mat2, n, n/2);   // Se crea una matriz de tamaño n*n/2
            inicializar(&mat2);     // Se le dan valores aleatorios
            crear(&res, n, n/2);    // Resutado: matriz de tamaño n*n/2

            // Medición del tiempo
            inicio = clock();
            mult(&res, mat, mat2);
            fin = clock();

            printf("n:%hi\tt(n):%.4lf\tini.:%d\tfin:%d\n", n, 
                    (fin - inicio) / (double) CLOCKS_PER_SEC, (int) inicio, 
                    (int) fin);
            fprintf(fp, "%hi\t%.4lf\n", n, (fin - inicio) / 
                    (double) CLOCKS_PER_SEC);

            // Liberación de las matrices
            liberar(&mat);
            liberar(&mat2);
            liberar(&res);
        }
    } else{
        printf("Opción incorrecta. Finalizando programa...");
        exit(EXIT_FAILURE);     // El programa termina con un mensaje de error
    }
    
    fclose(fp);     // Se cierra el archivo de texto
    return (EXIT_SUCCESS);
}
