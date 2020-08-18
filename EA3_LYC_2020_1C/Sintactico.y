%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    #include "archivos_punto_H/tabla_simbolo.h"
    #include "archivos_punto_H/constantes.h"
    #include "archivos_punto_H/terceto.h"
    #include "archivos_punto_H/assembler.h"
    FILE  *yyin;
    int yystopparser=0;
    int yylineno;

    void printRule(const char *, const char *);
    int yyerror(const char *);
    array_terceto t;
    char F_DATO[20];
    int Find;
    int Lind;
    int Xind;
    int Aind;


%}

%union {
    char *str_val;
}

%token <str_val> CTE
%token <str_val> ID
%token READ
%token WRITE
%token MAXIMO
%token ASIGNA
%token PARA
%token PARC
%token <str_val> CTE_S
%token COMA
%token OPDIV

%start S
%%
S:
    prog { 
        printRule("S", "MULT"); 
        imprimirTercetos(&t);
        guardarTercetos(&t);
        generarAssembler(&t);
        tsCrearArchivo();}
    ;

prog:
      sent {printRule("PROG", "SENT");}
    | prog sent {printRule("PROG", "PROG SENT");}
    ;

sent:
      read {printRule("SENT", "READ");}
    | write {printRule("SENT", "WRITE");}
    | asig {printRule("SENT", "ASIG");}
    ;

asig:
      ID ASIGNA max OPDIV factor {
          Aind = crearTerceto("/", "@max", F_DATO, &t);
          crearTerceto("=", getIndex(Aind), $1, &t);
          tsInsertarToken(T_INTEGER, "@aux", "", 0);
          tsInsertarToken(T_INTEGER, "@max", "", 0);
          printRule("ASIG", "ID ASIGNA max OPDIV factor");
          
          }
    | ID ASIGNA max {
        crearTerceto("=", "@max", $1, &t);
        tsInsertarToken(T_INTEGER, "@aux", "", 0);
        tsInsertarToken(T_INTEGER, "@max", "", 0);
        printRule("ASIG", "ID ASIGNA max");
        }
    ;

max:
      MAXIMO PARA lista PARC  {printRule("MAX", "MAXIMO PARA lista PARC");}
    ;

factor:
      ID {
        strcpy(F_DATO, $1);
        printRule("FACTOR", "ID");
        }
    | CTE {
        strcpy(F_DATO, $1);
        printRule("FACTOR", "CTE");
        }
    ;

read:
      READ ID {
          crearTerceto("read", $2, " ", &t);
          printRule("READ", "READ ID");
          }
    ;

lista: 
      CTE {
          Lind = crearTerceto("=", aConstante($1), "@max", &t);
          printRule("LISTA", "ID");
          }
    | lista COMA CTE {
        Lind = crearTerceto("=", aConstante($3), "@aux", &t);
        crearTerceto("CMP", "@aux", "@max", &t);
        crearTerceto("JNB", getIndex(Lind+4), " ", &t);
        crearTerceto("=", "@aux", "@max", &t);
        printRule("LISTA", "LISTA ID");
        }
    ;

write:
      WRITE CTE_S {
          crearTerceto("write", $2, " ", &t);
          printRule("WRITE", "WRITE CTE_S");
          }
    | WRITE ID {
        crearTerceto("write", $2, " ", &t);
        printRule("WRITE", "WRITE ID");}
    ;

%%

void printRule(const char *lhs, const char *rhs) {
    printf("%s -> %s\n", lhs, rhs);
    return;
}

int yyerror(const char *s) {
    printf("Syntax Error\n");
    printf("Nro. de linea: %d \t %s\n", yylineno, s);
    exit(1);
}

int main(int argc,char *argv[]) {

    inicializarTerceto(&t);

    if((yyin = fopen(argv[1], "rt")) == NULL) {
        printf("\nNo se puede abrir el archivo: %s\n", argv[1]);
    } else {
        yyparse();
    }

    fclose(yyin);
    return 0;
}


