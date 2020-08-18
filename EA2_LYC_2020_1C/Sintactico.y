%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    #include "arbol_sintactico.h"
    FILE  *yyin;
    int yystopparser=0;
    int yylineno;

    nodo* AUX=NULL;
    nodo* ASIGNA=NULL;
    nodo* S=NULL;
    nodo* F=NULL;
    nodo* T=NULL;
    nodo* E=NULL;
    nodo* L=NULL;

    void printRule(const char *, const char *);
    int yyerror(const char *);
    


%}

%union {
    char *str_val;
}

%token <str_val> CONST
%token <str_val> ID
%token ASIG
%token MUL
%token SUMA

%start S
%%
S:
    mult {printRule("S", "MULT");}
    ;

mult:
      lista exp {
        printRule("MULT", "LISTA EXP");
        AUX = crearNodo("=", crearHoja("@aux"), E);
        S = crearNodo("CUERPO_PRINCIPAL", AUX, L);
        escribirGragh(S);
        }
    ;

lista:
      ID ASIG {
        printRule("LISTA", "ID ASIG");
        L = crearNodo("=", crearHoja($1), crearHoja("@aux"));
        }
    | lista ID ASIG {
        printRule("LISTA", "LISTA ID ASIG");
        ASIGNA = crearNodo("=", crearHoja($2), crearHoja("@aux"));
        L = crearNodo("CUERPO_LISTA", L, ASIGNA);
        }
    ;

exp:
      exp SUMA term {
        printRule("EXP", "EXP SUMA TERM");
        E = crearNodo("+", E, T);
        }
    | term {
        printRule("EXP", "TERM");
        E = T;
        }
    ;

term:
      term MUL factor {
        printRule("TERM", "TERM MUL FACTOR");
        T = crearNodo("*", T, F);
        }
    | factor {
        printRule("TERM", "FACTOR");
        T = F;
        }
    ;

factor:
      ID {
        printRule("FACTOR", "ID");
        F = crearHoja($1);
        }
    | CONST {
        printRule("FACTOR", "CONST");
        F = crearHoja($1);
        }
    ;
%%

void printRule(const char *lhs, const char *rhs) {
    //if (YYDEBUG) {
        printf("%s -> %s\n", lhs, rhs);
    //}
    return;
}

int yyerror(const char *s) {
    printf("Syntax Error\n");
    printf("Nro. de linea: %d \t %s\n", yylineno, s);
    exit(1);
}

int main(int argc,char *argv[]) {
    
    if((yyin = fopen(argv[1], "rt")) == NULL) {
        printf("\nNo se puede abrir el archivo: %s\n", argv[1]);
    } else {
        // si al ejecutar Primera.exe paso un tercer parametro, no va a imprimir
        //if (argc > 2) {
            //noImprimir();
        //}
        yyparse();
    }

    fclose(yyin);
    return 0;
}

