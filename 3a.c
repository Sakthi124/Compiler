%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

%token num let
%left '+' '-'
%left '*' '/'
%%
Stmt : Stmt '\n' { printf("\n..valid expression..\n"); exit(0); }
     | expr '\n' { printf("\n..valid expression..\n"); exit(0); }
     | error '\n' { printf("\n..invalid expression..\n"); exit(0); }
     ;

expr : num
     | let
     | expr '+' expr
     | expr '-' expr
     | expr '*' expr
     | expr '/' expr
     | '(' expr ')'
     ;
%%

int main() {
    printf("Enter an expression to validate: ");
    yyparse();
    return 0;
}

int yylex() {
    int ch;
    while((ch = getchar()) == ' '); // Skip whitespace
    
    if(ch == EOF) return 0;
    
    if(isdigit(ch)) {
        // Read all digits
        while(isdigit(ch = getchar()));
        ungetc(ch, stdin);
        return num;
    }
    
    if(isalpha(ch)) {
        // Read all letters
        while(isalpha(ch = getchar()));
        ungetc(ch, stdin);
        return let;
    }
    
    return ch;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
