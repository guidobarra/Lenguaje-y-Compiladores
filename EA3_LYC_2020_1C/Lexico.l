%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
#include "archivos_punto_H/tabla_simbolo.h"
#include "archivos_punto_H/constantes.h"
#include "archivos_punto_H/terceto.h"
FILE  *yyin;
void textoFuncion();
%}

%option noyywrap  
%option yylineno


DIGITO		[0-9]
LETRA		[a-zA-Z]
ID          ({LETRA})({LETRA}|{DIGITO})*
CONST       ({DIGITO})+
CARACTER 	[a-z,A-Z,0-9,=,>,),(,<,!,:,+,".",-,\-,*,/,�,?,_,",",";"]
TEXTO 		\"({CARACTER}|" ")+\"

%%

"("			{ return PARA;}

")"			{ return PARC;}

","			{ return COMA;}

"="			{ return ASIGNA;}

"/"		    { return OPDIV;}

"maximo"	{ return MAXIMO;}

"READ"		{ return READ;}

"WRITE"		{ return WRITE;}

{CONST}     { yylval.str_val = strdup(yytext); tsInsertarToken(CTE_INTEGER, strdup(yytext), yytext, 0); return CTE; }

{ID}	    { yylval.str_val = strdup(yytext); tsInsertarToken(T_INTEGER, yylval.str_val, "", 0); return ID; }

{TEXTO}     { textoFuncion(); return CTE_S;}

"\n"
"\t"
" "
%%

void textoFuncion() {
	int longitud = strlen(yytext)-2;
	char* subBuff = (char *) malloc(longitud + 1);
	strncpy(subBuff, yytext+1, longitud);
	subBuff[longitud] = '\0';

	// Reemplaza cada caracter invalido por un guion bajo
	int idx = 0;
	char caracteresRaros[] = {';', ' ', ':', '=', ',', '(', ')', '[', ']'};
	char *ptrCaracter;
	for(idx = 0; idx < strlen(caracteresRaros); idx++) {
		ptrCaracter = strchr(subBuff, caracteresRaros[idx]);
		while (ptrCaracter != NULL) {
			*ptrCaracter = '_';
			ptrCaracter = strchr(subBuff, caracteresRaros[idx]);
		}
	}
	
	yylval.str_val = strdup(subBuff);
	if (strlen(subBuff) > LIMITE_STR) {
		printf("Error: El string supero los 30 caracteres\n\tvariable: %s", yytext);
		exit(1);
	}
	tsInsertarToken(CTE_STRING, yylval.str_val, strdup(yytext), strlen(subBuff));
}