#include <stdio.h>

int absoluto(int n);
float potencia(int base, int exponente) { 
//int potencia(int base, int exponente) { 
    int valor = 1;
    int i;
    if (base | exponente)
        for (i=1; i <= absoluto(exponente); i++)
            valor = valor * base;
    else
        printf("Error potencia: indeterminación %d^%d\n", base, exponente);
    return (exponente < 0)? 1./valor : valor; 
    //return (exponente < 0)? 1/valor : valor; 

}

int absoluto(int n) {
    return (n<0)? -n : n;  //return (n<0)? n : n;
}