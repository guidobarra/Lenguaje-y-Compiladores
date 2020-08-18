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

nodoTerceto* crearTerceto(void* op1, void* op2, void* op3)  {
    nodoTerceto* nuevoTerceto = (nodoTerceto*) malloc(sizeof(nodoTerceto));
    //asignarOperando(nuevoTerceto->op1, op1);
    //asignarOperando(nuevoTerceto->op2, op2);
    //asignarOperando(nuevoTerceto->op3, op3);
    if (sizeof( *((nodoTerceto*) op1)) == sizeof(nodoTerceto)) {
        printf("------------------------------------\n");
        nuevoTerceto->op1 = op1;
    } else {
        int cantChar = strlen((char*) op1) + 1;
        nuevoTerceto->op1 = malloc(sizeof(cantChar*sizeof(char)));
        strcpy((char*) nuevoTerceto->op1, (const char*) op1);
    }
    if (sizeof( *((nodoTerceto*) op2)) == sizeof(nodoTerceto)) {
        printf("------------------------------------\n");
        nuevoTerceto->op2 = op2;
    } else {
        int cantChar = strlen((char*) op2) + 1;
        nuevoTerceto->op2 = malloc(sizeof(cantChar*sizeof(char)));
        strcpy((char*) nuevoTerceto->op2, (const char*) op2);
    }
    if (sizeof( *((nodoTerceto*) op3)) == sizeof(nodoTerceto)) {
        printf("------------------------------------\n");
        nuevoTerceto->op3 = op3;
    } else {
        int cantChar = strlen((char*) op3) + 1;
        nuevoTerceto->op3 = malloc(sizeof(cantChar*sizeof(char)));
        strcpy((char*) nuevoTerceto->op3, (const char*) op3);
    }
    return nuevoTerceto;
}

void asignarOperando(void* operandoAsignar, void* operando) {
    if (sizeof(*operando) == sizeof(nodoTerceto)) {
        printf("------------------------------------");
        operandoAsignar = operando;
    } else {
        int cantChar = strlen((char*) operando) + 1;//sizeof( (char*) operando)/sizeof(char);
        //operandoAsignar = malloc(sizeof(cantChar*sizeof(char)));
        //strcpy((char*) operandoAsignar, (const char*) operando);
        memcpy(operandoAsignar, operando, cantChar);
    }
}

void escribirTerceto(nodoTerceto** pila, int cant) {
    FILE *archivo;

	archivo = fopen("terceto.txt", "w");
	if (archivo == NULL) {
		return;
	}
    int i = 0;
    for (;i < cant; i++) {
        fprintf(archivo, "%p \t",pila[i]);
        nodoTerceto aux= *pila[i];
        if (sizeof( *((nodoTerceto*) (aux.op1))) == sizeof(nodoTerceto)) {
            fprintf(archivo, "( %p, ",aux.op1);
        } else {
            fprintf(archivo, "( %s   , ",(char*) aux.op1);
        }
        if (sizeof( *((nodoTerceto*) (aux.op2))) == sizeof(nodoTerceto)) {
            fprintf(archivo, "%p, ",aux.op2);
        } else {
            fprintf(archivo, "( %s   , ",(char*)aux.op2);
        }
        if (sizeof( *((nodoTerceto*) (aux.op3))) == sizeof(nodoTerceto)) {
            fprintf(archivo, "%p)\n",aux.op3);
        } else {
            fprintf(archivo, "( %s   , ",(char*) aux.op3);
        }
    }
    fclose(archivo);
}