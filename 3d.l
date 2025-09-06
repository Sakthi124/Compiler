%{
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"

void yyerror(char*);
extern int yylval;
%}

%%

[ \t]+        ;  /* Skip whitespace */
[0-9]+        { yylval = atoi(yytext); return INTEGER; }
[-+*/()\n]    { return *yytext; }
.             { 
                 char msg[50];
                 sprintf(msg, "invalid character '%s'", yytext);
                 yyerror(msg);
               }

%%

int yywrap(void) {
    return 1;
}
