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
    nodo* O=NULL;
    nodo* CUERPO=NULL;
    nodo* OPERAR=NULL;
    //nodo* ASIGNA=NULL;
    int cant;
    int cont;

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
%token TAKE
%token PN_C
%token P_A
%token P_C
%token C_A
%token C_C

%start S
%%
S:
    asig {printRule("S", "MULT");}
    ;

asig:
      ID ASIG exp {
        printRule("ASIG", "ID ASIG EXP");
        //AUX = crearNodo("=", crearHoja("@aux"), E);
        S = crearNodo("=", crearHoja($1), E);
        escribirGragh(S);
        }
    ;

lista:
      ID {
        printRule("LISTA", "ID");
        cont++;
        if(cant>=cont) {
            CUERPO = crearHoja($1);
            //CUERPO = crearNodo("=", crearHoja("@aux"), crearHoja($1));
            }         
        }
    | lista ID {
        printRule("LISTA", "LISTA ID");
        cont++;
        if(cant>=cont) {
                //OPERAR = crearNodo(O->dato, crearHoja("@aux"), crearHoja($2)); 
                //ASIGNA = crearNodo("=", crearHoja("@aux"), OPERAR);
                //CUERPO = crearNodo("CUERPO_TAKE", CUERPO, ASIGNA);
                CUERPO = crearNodo(O->dato, CUERPO, crearHoja($2));
            }
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
    | TAKE {cont=0;} P_A operardor PN_C CONST {cant = atoi($6);} PN_C C_A lista C_C P_C {
                                                                                    //ASIGNA = crearNodo("=", crearHoja($1), crearHoja("@aux"));
                                                                                    F = CUERPO;//crearNodo("CUERPO", CUERPO, ASIGNA); 
                                                                               } 
    ;

operardor:
      SUMA { 
          O = crearHoja("+"); 
          printRule("OPERADOR", "SUMA");
          }
    | MUL  { 
        O = crearHoja("*"); 
        printRule("OPERADOR", "MUL");
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

