%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

%token let dig
%%
TERM : XTERM '\n' { 
        printf("\nAccepted - Valid variable pattern\n"); 
        exit(0); 
      }
     | error '\n' { 
        printf("\nRejected - Invalid variable pattern\n"); 
        exit(1); 
      }
     ;

XTERM : XTERM let
      | XTERM dig
      | let
      | dig
      ;
%%

int main() {
    printf("Enter a variable pattern: ");
    yyparse();
    return 0;
}

int yylex() {
    int ch;
    
    // Skip whitespace (except newline)
    while((ch = getchar()) == ' ' || ch == '\t');
    
    if(ch == EOF) return 0;
    
    if(isalpha(ch)) {
        // Read all consecutive letters
        while(isalpha(ch = getchar()));
        ungetc(ch, stdin);
        return let;
    }
    
    if(isdigit(ch)) {
        // Read all consecutive digits
        while(isdigit(ch = getchar()));
        ungetc(ch, stdin);
        return dig;
    }
    
    return ch;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
