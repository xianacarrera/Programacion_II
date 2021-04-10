/*
 * PROGRAMA PARA CALCULAR EL FACTORIAL Y LA POTENCIA DE DOS NÚMEROS ENTEROS
 * PEDIDOS AL USUARIO/A POR TECLADO.
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. 
 * EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES. DOCUMENTAR LAS CORRECCIONES 
 * INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 * 
 * PRUEBAS: USAR LOS CASOS
 * 0 0  (factorial=1, potencia=0^0, indeterminación)
 * 3 0  (factorial=6, potencia=1)
 * 0 10 (factorial=1, potencia=0)
 * 0 -2 (factorial=1, potencia=1/0=infinito)
 * 10 2 (factorial=3628800, potencia=100)
 * 2 10 (factorial=2, potencia=1024)
 * -5 1 (factorial no existe por ser negativo, potencia=-5)
 * -5 -3 (factorial no existe por ser negativo, potencia=-0.008)
 */

/* 
 * File:   main.c
 * Xiana Carrera
 * 
 * Fecha: 3 de febrero de 2020, 18:18
 * Este programa calcula factoriales y potencias de números enteros.
 */

/* b) Si ejecutamos el modo depuración paso a paso, al llegar a la llamada a la
 * función factorial, podremos ver también cómo esta se ejecuta línea a línea,
 * es decir, pasaremos a encontrarnos en el archivo factorial.c. En la pestaña 
 * "variables" se nos mostrarán las variables locales de la función factorial, 
 * mientras que ya no podremos visualizar las variables locales del main.
 * 
 * c) Si en lugar de usar "step into" (F7) usamos "step over" (F8) al llegar a
 * la función potencia, el modo depuración no mostrará cómo esta funciona por
 * dentro ni cómo cambian sus variables, y la ejecución seguirá en el main en
 * todo momento. Este procedimiento es, por ejemplo, análogo al de ejecutar
 * printf, pues tampoco sabemos qué pasos está siguiendo interiormente.
 */

/* Nota: no se muestra ningún mensaje de error en el caso de la división entre
 * 0 porque este no es una indeterminación y C lo interpreta como infinito (inf)
 * de por sí.
 */

#include <stdio.h>
#include <stdlib.h>

int factorial(int n);
float potencia(int n, int m);   //int potencia(int n, int m);

int main(int argc, char** argv) {
    
    int a, b;
    int f;
    float p;    //int p;
    
    printf("Introduce dos números enteros: ");
    scanf("%d %d", &a, &b);      //scanf("%f%d", &a, &b);

    f = factorial(a);
    if (a>=0)
        printf("Factorial(%d) = %d\n", a, f);
    
    p = potencia(a, b);
    if (a | b)
        printf("Potencia(%d,%d) = %.3f\n", a, b, p); 
        //printf("Potencia(%d,%d) = %d\n", a, b, p);
    
    return (EXIT_SUCCESS);
}

