%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    #include "arbol_sintactico.h"
    FILE  *yyin;
    int yystopparser=0;
    int yylineno;

    nodo* O=NULL;
    nodo* S=NULL;
    nodo* CUERPO=NULL;
    nodo* OPERAR=NULL;
    nodo* ASIGNA=NULL;
    nodo* L_aux;
    nodo* hojaAux;
    char* pila[50];
    int cont=0;
    int cant=0;
    int tope=0;
    nodo* PL=NULL;
    char buffer[10];
    char* polacaInversa[20];
    int indexPolaca=0;

    void printRule(const char *, const char *);
    int yyerror(const char *);
    int pilaVacia();
    char* desapilar();
    void apilar(char*);
    


%}

%union {
    char *str_val;
}

%token <str_val> CONST
%token <str_val> ID
%token <str_val> VALOR
%token TAKE
%token PN_C
%token P_A
%token P_C
%token C_A
%token C_C
%token ASIG
%token MUL
%token SUMA

%start S
%%
S:
    ID ASIG TAKE P_A operardor PN_C CONST {cant = atoi($7);} PN_C C_A lista C_C P_C 
    {
        apilar("@aux");
        apilar($1);
        apilar("=");
        
        ASIGNA = crearNodo("=", crearHoja($1), crearHoja("@aux"));
        S = crearNodo("CUERPO", CUERPO, ASIGNA);

        //crearTerceto("=", "@aux", $1);

        escribirGragh(S);
        escribirGraghPolaca(pila, tope-1);
        printRule("S", "ID ASIG TAKE P_A operardor PN_C cte PN_C C_A lista C_C P_C");
    }
    ;

operardor:
      SUMA { O = crearHoja("+"); printRule("OPERADOR", "SUMA");}
    | MUL  { O = crearHoja("*"); printRule("OPERADOR", "MUL");}
    ;

lista:
      ID        { 
                  cont++;
                  if(cant>=cont) {
                    apilar("@aux");
                    apilar($1);
                    apilar("=");
                    CUERPO = crearNodo("=", crearHoja("@aux"), crearHoja($1));
                    //listaTerceto = crearTerceto("=", $1, "@aux");
                  }
                  printRule("LISTA", "ID");
                }
    | lista ID  { 
                  cont++;
                  if(cant>=cont) {
                    apilar("@aux");
                    apilar($2);
                    apilar(O->dato);
                    apilar("@aux");
                    apilar("=");
                    OPERAR = crearNodo(O->dato, crearHoja("@aux"), crearHoja($2)); 
                    ASIGNA = crearNodo("=", crearHoja("@aux"), OPERAR);
                    CUERPO = crearNodo("CUERPO", CUERPO, ASIGNA);
                    //listaTercetoAux = crearTerceto(O->dato, $2, "@aux");
                    //listaTerceto = crearTerceto("=", listaTercetoAux, "@aux");
                  }
                  printRule("LISTA", "LISTA ID");
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

int pilaVacia() {
    return tope==0?1:0;
}
char* desapilar(){
    tope--;
    return pila[tope];
}
void apilar(char* n) {
    pila[tope] = n;
    tope++;
}
