/*
 * PROGRAMA PARA REALIZAR OPERACIONES BÁSICAS CON UNA MATRIZ DINÁMICA
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES
 * DOCUMENTAR LAS CORRECCIONES INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 *
 * PRUEBAS:
 * - número de filas o columnas: 0
 * - acceder a un dato con índices negativos
 * - verificar todas las operaciones, para matrices pequeñas (2,3 filas/cols)
 *      - número de filas y columnas distintos en las dos matrices
 *      - número de filas igual y de columnas distinto
 *      - número de columnas igual y de filas distinto
 */

/* 
 * File:   main.c
 * Xiana Carrera
 * 
 * Fecha: 7 de febrero de 2020, 17:32
 * Este programa realiza sumas y multiplicaciones de matrices.
 */

/* Comentarios del ejercicio:
 * Inicialmente la memoria no se liberaba correctamente. Cuando destruirMatriz
 * realizaba los free necesarios, no se volvía a inicializar las matrices a 0,
 * por lo que las comprobaciones en el main y en otras funciones 
 * de que estas estuvieran apuntando a una dirección de memoria válida 
 * (que fueran distintas de 0) fallaban, produciéndose errores que abortaban el 
 * programa.
 * 
 * Para evitar esto, la solución es igualar los punteros a 0 tras llamar a
 * destruirMatriz. Aunque es algo que se podría realizar en el main, he optado
 * por utilizar dobles punteros para poder incluir esta línea dentro de la
 * función, con lo que el código queda más compacto.
 * 
 * Por otro lado, se han añadido dos llamadas a destruirMatriz al inicio de
 * crearMatriz, pues si se utilizaba la opción 1 dos veces seguidas, la memoria
 * anteriormente reservada no era liberada y quedaba inaccesible.
 * 
 * Casos del enunciado:
 * Si las filas o las columnas de alguna matriz son 0 o un número negativo,
 * crearMatriz devuelve 0, por lo que no se llega a crear nada. Si intentamos
 * asignar elementos, obtener elementos, etc. obtendremos los mensajes de error
 * asignados a este caso ("debe definir primero la matriz", "la matriz no
 * existe"...).
 * 
 * Si se intenta acceder a un dato con índices negativos, obtenerElemento
 * avisará de que este no existe y devolverá 0. No debería haber confusión con
 * un caso donde el elemento sí existe y vale 0, pues entonces no aparecería
 * el mensaje de error.
 * 
 * Si tanto el número de filas como el número de columnas en las dos matrices
 * son distintos, no se podrán sumar ni multiplicar. Si difieren solo en el
 * número de columnas no se podrán sumar, pero sí multiplicar en el caso de que
 * las columnas de a coincidan con las filas de b. Si difieren solo en el número
 * de filas ocurre lo mismo: no se pueden sumar, pero sí multiplicar si
 * las columnas de a coindiciden con las filas de b. En cualquier caso el
 * tamaño de la matriz producto será las filas de a por las columnas de b.
 * 
 * Tras corregir destruirMatriz y seguir los pasos 1, 7 y 0, podemos comprobar
 * que el programa finaliza con toda la memoria liberada. El bucle do-while
 * termina y se pasa a la línea "return (EXIT_SUCCESS)". Anteriormente
 * si en el modo depuración se veía el contenido de a y b, estas no estaban
 * vacías al no haber sido igualadas a 0.
 *  */

#include "matriz.h"

int main(int argc, char** argv) {
    int f, c; //int i, k, f, c;
    // Podemos no declarar ni i ni k porque no se usan dentro del main.
    float valor;
    matriz *a = 0, *b = 0, *aux = 0;
    matriz **point;
    char opcion, resp;


    do {
        printf("---------------------Libreria matrices---------------------\n\n");
        printf("1-Crear matrices\n");
        printf("2-Asignar elementos\n");
        printf("3-Obtener elemento\n");
        printf("4-Imprimir matrices\n");
        printf("5-Sumar matrices\n");
        printf("6-Producto de matrices\n");
        printf("7-Eliminar matrices\n");
        printf("0-Salir\n");
        printf("Opcion: ");
        scanf(" %c", &opcion);   //scanf(" %c", opcion)

        switch (opcion) {
            case '0':
                printf("Saliendo del programa\n");
                break;
            case '1':
                point = &a;
                destruirMatriz(point);
                point = &b;
                destruirMatriz(point); 
                printf("Introduzca el numero de filas de la matriz 'a': ");
                scanf("%d", &f);    //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'a': ");
                scanf("%d", &c);
                a = crearMatriz(f, c);

                printf("Introduzca el numero de filas de la matriz 'b': ");
                scanf("%d", &f);    //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'b': ");
                scanf("%d", &c);
                b = crearMatriz(f, c);

                break;
            case '2':
                printf("Matriz A\n");
                if (a){
                //Si no se ha inicializado la matriz a, buscar a->filas y a->columnas dará error.
                    for (f = 0; f < a->filas; f++)
                        for (c = 0; c < a->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, a);
                        }
                }
                else
                    printf("Debe definir primero la matriz a\n");
                printf("Matriz B\n");
                if (b){
                    //Si no se ha inicializado la matriz b, buscar b->filas y b->columnas dará error.
                    for (f = 0; f < b->filas; f++)
                        for (c = 0; c < b->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, b);
                            //asignarElemento(f, c, valor, a);
                        }
                    }
                else
                    printf("Debe definir primero la matriz b\n");

                break;
            case '3':
                do {
                    printf("De que matriz quieres ver un elemento? (a/b): ");
                    scanf(" %c", &resp);
                } while (resp != 'a' && resp != 'b');
                printf("Introduce fila y columna (fila columna): ");
                scanf("%d %d", &f, &c);
                if (resp == 'a') {
                    valor = obtenerElemento(f, c, a);
                    //valor = obtenerElemento(f, c, b);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                } else if (resp == 'b') {
                    valor = obtenerElemento(f, c, b);
                    //valor = obtenerElemento(f, c, a);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                }
                break;
            case '4':
                printf("Matriz A\n");
                imprimirMatriz(a);
                printf("Matriz B\n");
                imprimirMatriz(b);
                break;
            case '5':
                aux = suma(a, b);
                if (aux){
                    /* Con esta condición evitamos que haya 2 mensajes de error seguidos: uno para
                     * suma y otro para imprimirMatriz, y nos ahorramos dos llamadas a funciones.
                     */
                    imprimirMatriz(aux);
                    point = &aux;
                    destruirMatriz(point);    //destruirMatriz(aux);
                }
                break;
            case '6':
                aux = producto(a, b);
                if (aux){
                    imprimirMatriz(aux);
                    point = &aux;
                    destruirMatriz(point);    //destruirMatriz(aux);
                }
                //destruirMatriz(aux);
                break;
            case '7':
                point = &a;
                destruirMatriz(point);  //destruirMatriz(a);
                point = &b;
                destruirMatriz(point);  //destruirMatriz(b);
                printf("Matrices eliminadas...\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion != '0');

    return (EXIT_SUCCESS);
}