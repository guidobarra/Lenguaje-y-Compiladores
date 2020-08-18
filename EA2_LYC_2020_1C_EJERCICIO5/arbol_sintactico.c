#include "arbol_sintactico.h"

nodo* crearNodo(const char *d, nodo* hI, nodo* hD) {
	nodo* nodoPadre = (nodo*)malloc(sizeof(nodo));
    if(nodoPadre == NULL) {
        printf("No hay memoria disponible");
        exit(1);
    }
    strcpy(nodoPadre->dato, d);
    nodoPadre->hijoDer = hD;
    nodoPadre->hijoIzq = hI;
    return nodoPadre;
}

nodo* crearHoja(const char *d) {
	nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
    if(nuevoNodo == NULL) {
        printf("No hay memoria disponible");
        exit(1);
    }
    strcpy(nuevoNodo->dato, d);
    nuevoNodo->hijoDer = NULL;
    nuevoNodo->hijoIzq = NULL;
    return nuevoNodo;
}

void liberarMemoria(nodo* padre) {
    if(padre == NULL) {
        return;
    }
    liberarMemoria(padre->hijoDer);
    liberarMemoria(padre->hijoIzq);
    free(padre);
    return;
}

void llenarGragh(nodo* padre, FILE *arch, int numNodo) {
    if(padre == NULL) {
        return;
    }
    int numHI = numNodo*2+1;
    int numHD = numNodo*2+2;
    
    if(padre->hijoIzq) {
        fprintf(arch, "\t\"%s@%d\" -> \"%s@%d\"\n", padre->dato, numNodo, padre->hijoIzq->dato, numHI);
    }
    if(padre->hijoDer) {
        fprintf(arch, "\t\"%s@%d\" -> \"%s@%d\"\n", padre->dato, numNodo, padre->hijoDer->dato, numHD);
    }
    llenarGragh(padre->hijoIzq, arch, numHI);
    llenarGragh(padre->hijoDer, arch, numHD);
    return;
}

void escribirGragh(nodo* padre) {
    FILE *archivo;

	archivo = fopen("gragh.dot", "w");
	if (archivo == NULL) {
		return;
	}
    //escribir la plantilla para dibujar el grafo
    fprintf(archivo, "%s\n", "digraph G {");
    llenarGragh(padre, archivo, 0);
    fprintf(archivo, "%s", "}");
    
    fclose(archivo);
    liberarMemoria(padre);
    return;
}

void llegarGraghPolaca(char** arrayNodo, FILE *arch, int cantElem) {
    int i=0;
    for(i=0; i<cantElem; i++, arrayNodo++) {
        fprintf(arch, "\t\"%s@%d\" -> \"%s@%d\"\n", *arrayNodo, i, *(arrayNodo+1), i+1);
    }
}

void escribirGraghPolaca(char** arrayNodo, int cantElem) {
    FILE *archivo;

	archivo = fopen("graghPolaca.dot", "w");
	if (archivo == NULL) {
		return;
	}
    //escribir la plantilla para dibujar el grafo
    fprintf(archivo, "%s\n", "digraph G {");
    llegarGraghPolaca(arrayNodo, archivo, cantElem);
    fprintf(archivo, "%s", "}");
    //iberarMemoriaPolaca(arrayNodo, cantElem);
}