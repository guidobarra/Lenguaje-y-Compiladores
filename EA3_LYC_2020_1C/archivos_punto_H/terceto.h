#ifndef TERCETO_H
#define TERCETO_H

#include "constantes.h"
#include "tabla_simbolo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct terceto{
    char d1[100];
    char d2[100];
    char d3[100];
}terceto;

// Estructura para los tercetos
typedef terceto t_terceto;

// ARRAY de tercetos
typedef struct array_terceto{
    t_terceto tercetos[1000];
    int cantElemTecetos; // cant de tercetos
}array_terceto;

// Estructura para los tercetos
typedef array_terceto* t_array_terceto;

int crearTerceto(const char*, const char*, const char*, t_array_terceto);
void inicializarTerceto(t_array_terceto);
void imprimirTercetos(t_array_terceto);
void guardarTercetos(t_array_terceto);
char* getIndex(int);
int getIndexNumero(char*);
#endif