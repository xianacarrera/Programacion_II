/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Autora: Xiana Carrera
 * 
 * Fecha: 6 de febrero de 2020, 17:05
 * Este programa calcula potencias de los elementos de un array.
 */

/* Comentarios del ejercicio:
 * Al ejecutar el programa paso a paso podemos ver cómo cambian las variables.
 * Originalmente, los arrays (a y c) contienen valores aleatorios en todas sus
 * componentes. El array a cambia cada una tras llevar a cabo el scanf donde se
 * piden sus elementos. Los resultados de las potencias se guardan uno a uno en 
 * la correspondiente posición del array c tras ejecutarse la línea 88 o la
 * 90, ya que, aunque estamos manejando el array result dentro de una función,
 * en realidad los cambios tienen lugar también sobre c, pues los vectores
 * en C se pasan siempre por referencia.
 * 
 * Con el resto de variables ocurre lo mismo: sus valores son aleatorios antes 
 * de inicializarse (por ejemplo, antes de llegar a la línea 81 dentro de la
 * función potencia, pot no tiene por qué valer 1). Después de realizar alguna
 * operación con ellas, como en la línea 86, vuelven a cambiar.
 * 
 * Con respecto a las direcciones de memoria de los elementos del array, podemos
 * observar que la menor es &a[0] y la mayor, &a[3]. La diferencia entre cada
 * dirección es de 4 bytes, pues a es un array de enteros, que ocupan 4 bytes
 * cada uno. Es decir, en total se reservan 16 bytes de forma ascendente (con
 * direcciones mayores para los sucesivos elementos del array) en la pila.
 * Por ejemplo, en una ejecución se han obtenido los datos:
 *      &a[0] = 4294953888
 *      &a[1] =	4294953892
 *      &a[2] =	4294953896	
 *      &a[3] =	4294953900			 
 * 
 * Al restar &a[1] y &a[0], se tratan como direcciones de memoria de enteros, 
 * por lo que el valor devuelto es 1, es decir, hay un dato de diferencia
 * entre ellos. Si primero hacemos una conversión a enteros (en concreto,
 * a unsigned long int por su gran tamaño) y los restamos entonces, vemos
 * que en efecto hay 4 bytes entre ambos.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

void potencia(int base[], int exp, float result[]);

int main(int argc, char** argv) {
    int a[4];
    int b, i;
    float c[4];
    
    printf("Introduzca los cuatro números enteros a elevar: ");
    for (i=0; i<4; i++)
        scanf("%d", &a[i]);
    printf("Introduzca el exponente: ");
    scanf("%d", &b);
    
    potencia(a, b, c);
    for (i=0; i<4; i++){
        if (a[i] | b)
            printf("%d^%d = %.3f\n", a[i], b, c[i]);
        else
            printf("Error al elevar 0 a 0: indeterminación\n");
    }
    
    printf("Al restar las direcciones de a[1] y a[0] se obtiene: %ld\n",
            &a[1] - &a[0]);
    printf("Si las restamos conviertiéndolas primero a enteros obtenemos: %lu\n",
            (unsigned long int) &a[1] - (unsigned long int) &a[0]);
    
    return (EXIT_SUCCESS);
}

void potencia(int base[], int exp, float result[]) {
    int i, j;
    int pot = 1;
    
    for (i=0; i<=3; i++)
        if (base[i] | exp){
            for (j=0; j<abs(exp); j++)
                pot *= base[i];
            if (exp<0)
                result[i] = 1./pot;
            else
                result[i] = pot;
            pot = 1;
        }
}    

