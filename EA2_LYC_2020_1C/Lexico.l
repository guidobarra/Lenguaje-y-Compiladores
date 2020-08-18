%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
FILE  *yyin;
%}

%option noyywrap  
%option yylineno 

DIGITO		[0-9]
LETRA		[a-zA-Z]
ID          ({LETRA})({LETRA}|{DIGITO})*
CONST       ({DIGITO})+


%%

"="			{ return ASIG;}

"+"		    { return SUMA;}

"*"		    { return MUL;}

{CONST}       { yylval.str_val = strdup(yytext); return CONST; }

{ID}	        { yylval.str_val = strdup(yytext); return ID; }






"\n"
"\t"
" "
%%