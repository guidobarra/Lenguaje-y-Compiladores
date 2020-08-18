#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include "terceto.h"

void generarAssembler(t_array_terceto);
int generarHeader();
int generarData();
int generarFooter();
int generarInstrucciones(t_array_terceto);
void recorreArbolAsm(FILE *, t_array_terceto);
int setFile(FILE*, char *, char*);
char * verSiVaInterrogacion(char *);
char *getNombre(const int i);
#endif