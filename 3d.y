%{
#include <stdlib.h>
#include <stdio.h>

int yylex(void);
void yyerror(char *s);

%}

%token INTEGER

%%

program: 
    line program
    | line
    ;

line: 
    expr '\n' { printf("Result: %d\n", $1); }
    | '\n'    { /* Empty line */ }
    ;

expr: 
    expr '+' mulex { $$ = $1 + $3; }
    | expr '-' mulex { $$ = $1 - $3; }
    | mulex { $$ = $1; }
    ;

mulex: 
    mulex '*' term { $$ = $1 * $3; }
    | mulex '/' term { 
        if($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3; 
        }
      }
    | term { $$ = $1; }
    ;

term: 
    '(' expr ')' { $$ = $2; }
    | INTEGER { $$ = $1; }
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Simple Calculator (Enter expressions, Ctrl+D to exit)\n");
    printf("Example: 2 + 3 * (4 - 1)\n> ");
    yyparse();
    return 0;
}
