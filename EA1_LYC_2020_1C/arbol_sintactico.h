#ifndef ARBOL_SINTACTICO_H
#define ARBOL_SINTACTICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tabla de simbolos
typedef struct nodo{
    char dato[20];
    struct nodo* hijoDer;
    struct nodo* hijoIzq;
}nodo;

typedef struct nodoTerceto{
    void* op1;
    void* op2;
    void* op3;
}nodoTerceto;

nodo* crearNodo(const char* , nodo* , nodo* );
nodo* crearHoja(const char*);
void liberarMemoria(nodo* );
void llegarGragh(nodo* , FILE*, int );
void escribirGragh(nodo*);
void escribirGraghPolaca(char**, int);
void llegarGraghPolaca(char** , FILE*, int);
nodoTerceto* crearTerceto(void*, void*, void*);
void asignarOperando(void*, void*);
void escribirTerceto(nodoTerceto**, int );
#endif