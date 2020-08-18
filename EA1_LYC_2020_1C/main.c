#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./arbol_sintactico.h"

int main(){
    nodoTerceto *var;
    nodoTerceto *var1;
    nodoTerceto *var2;
    nodoTerceto *var3;
    nodoTerceto *pila[10];
    void* asd;
    var1 = crearTerceto("=", "a", "@aux");
    var2 = crearTerceto("+", "b", "@aux");
    var3 = crearTerceto("=", var2, "@aux");
    pila[0] = var1;
    pila[1] = var2;
    pila[2] = var3;

    //var3 = crearTerceto("-", var2, var1);
    //var = crearTerceto("=", "a", var3);
    escribirTerceto(pila, 3);
    var = var2->op3;
    printf("op1: %s t\n", (char *) var1->op1);
    printf("op2: %s t\n", (char *) var1->op2);
    printf("op3: %s t\n\n", (char *) var1->op3);

    asd = var1;
    


    printf("op1: %s t\n", (char *) var2->op1);
    printf("op2: %s t\n", (char *) var2->op2);
    printf("op3: %p t\n\n", (char *) var2->op3);

    printf("op1: %s t\n", (char *) var->op1);
    printf("op2: %s t\n", (char *) var->op2);
    printf("op3: %s t\n", (char *) var->op3);
    int i = 0;
    for ( i = 0 ; i < 10000; i++)
    {
        
    }
    
    printf("%d\n", sizeof(nodoTerceto));
    printf("%d\n", sizeof( *((nodoTerceto*) asd))   );

    free(var1->op1);
    free(var1->op2);
    free(var1->op3);
    free(var2->op1);
    free(var2->op2);
    free(var2->op3);
    free(var3->op1);
    free(var3->op2);
    free(var3->op3);
    return 0;
}