#include <stdio.h>

int factorial(int n) {
    int valor = 1;
    if (n >= 0) {   //if (n > 0)
        int i;
        for (i = 2; i <= n; i++) //for (i=0; i <=n; i++) 
            valor = valor * i;
    } else {
        printf("Error factorial: el parámetro (%d) no es un entero no negativo\n", n);
        //printf("Error factorial: el parámetro (%f) no es un entero positivo\n");
        /* Aclaración: he cambiado %f por %d porque, por la construcción del
         * programa, n siempre será un entero. Se especifica que sea no negativo
         * en lugar de positivo porque el factorial de 0 existe y vale 1.
         */
    }
    return valor;
}

