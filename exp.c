#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main() {
    int i, j = 0, k = 2, k1 = 0;
    char ip[20], filename[20];
    FILE *fp;
    
    printf("\nEnter the filename of the intermediate code: ");
    scanf("%s", filename);
    
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("\nError in opening the file '%s'\n", filename);
        return 1;
    }
    
    printf("\nIntermediate Code from file:\n");
    printf("---------------------------\n");
    while(fscanf(fp, "%s", ip) != EOF) {
        printf("\t%s\n", ip);
    }
    
    rewind(fp);
    
    printf("\nTarget Code Generation:\n");
    printf("----------------------\n");
    printf("\tStatement\t\tTarget Code\n");
    printf("\t--------\t\t-----------\n");
    
    j = 0; // Register counter
    while(fscanf(fp, "%s", ip) != EOF) {
        printf("\t%s", ip);
        
        int len = strlen(ip);
        if(len < 5) {
            printf("\t\tInvalid expression\n");
            continue;
        }
        
        // Find the operator position
        int op_pos = -1;
        for(i = 0; i < len; i++) {
            if(ip[i] == '+' || ip[i] == '-' || ip[i] == '*' || ip[i] == '/') {
                op_pos = i;
                break;
            }
        }
        
        if(op_pos == -1) {
            printf("\t\tInvalid expression (no operator)\n");
            continue;
        }
        
        // Extract operands
        char result = ip[0];
        char op = ip[op_pos];
        char op1 = ip[op_pos-1];
        char op2 = ip[op_pos+1];
        
        // Generate target code
        printf("\t\tMOV %c, R%d\n", op1, j);
        
        switch(op) {
            case '+':
                printf("\t\tADD %c, R%d\n", op2, j);
                break;
            case '-':
                printf("\t\tSUB %c, R%d\n", op2, j);
                break;
            case '*':
                printf("\t\tMUL %c, R%d\n", op2, j);
                break;
            case '/':
                printf("\t\tDIV %c, R%d\n", op2, j);
                break;
            default:
                printf("\t\tUnknown operator %c\n", op);
                continue;
        }
        
        printf("\t\tMOV R%d, %c\n", j, result);
        printf("\n");
        
        j++; // Use next register for next operation
    }
    
    fclose(fp);
    return 0;
}
