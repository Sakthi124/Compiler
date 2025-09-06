#include<stdio.h>
#include<string.h>
#include<ctype.h>

struct op {
    char l;
    char r[20];
} op[10], pr[10];

int main() {
    int i, j, k, n, z = 0, m, q;
    char *p, temp, t;
    char tem[20];
    
    printf("Enter the Number of Values: ");
    scanf("%d", &n);
    getchar(); // Consume newline
    
    // Input expressions
    for(i = 0; i < n; i++) {
        printf("Expression %d:\n", i+1);
        printf("  left: ");
        scanf("%c", &op[i].l);
        getchar(); // Consume newline
        printf("  right: ");
        scanf("%s", op[i].r);
        getchar(); // Consume newline
    }
    
    // Display intermediate code
    printf("\nIntermediate Code:\n");
    for(i = 0; i < n; i++) {
        printf("%c = %s\n", op[i].l, op[i].r);
    }
    
    // Dead Code Elimination
    // Mark variables that are used on right side
    int used[256] = {0}; // Track which variables are used
    used[(int)op[n-1].l] = 1; // Final result is always used
    
    // Backward pass to find used variables
    for(i = n-1; i >= 0; i--) {
        if(used[(int)op[i].l]) {
            // This variable is used, mark all variables in its right side as used
            for(j = 0; j < strlen(op[i].r); j++) {
                if(isalpha(op[i].r[j])) {
                    used[(int)op[i].r[j]] = 1;
                }
            }
        }
    }
    
    // Copy only used expressions
    z = 0;
    for(i = 0; i < n; i++) {
        if(used[(int)op[i].l]) {
            pr[z].l = op[i].l;
            strcpy(pr[z].r, op[i].r);
            z++;
        }
    }
    
    printf("\nAfter Dead Code Elimination:\n");
    for(k = 0; k < z; k++) {
        printf("%c = %s\n", pr[k].l, pr[k].r);
    }
    
    // Common Subexpression Elimination
    for(i = 0; i < z; i++) {
        for(j = i+1; j < z; j++) {
            if(strcmp(pr[i].r, pr[j].r) == 0 && pr[i].l != pr[j].l) {
                // Found common subexpression
                printf("Found common expression: %s\n", pr[i].r);
                
                // Replace all occurrences of pr[j].l with pr[i].l
                for(m = j+1; m < z; m++) {
                    p = strchr(pr[m].r, pr[j].l);
                    if(p != NULL) {
                        *p = pr[i].l;
                    }
                }
                
                // Remove the duplicate
                pr[j].l = '\0';
            }
        }
    }
    
    printf("\nAfter Common Subexpression Elimination:\n");
    for(i = 0; i < z; i++) {
        if(pr[i].l != '\0') {
            printf("%c = %s\n", pr[i].l, pr[i].r);
        }
    }
    
    // Remove null entries and create optimized code
    int opt_count = 0;
    struct op optimized[10];
    
    for(i = 0; i < z; i++) {
        if(pr[i].l != '\0') {
            optimized[opt_count].l = pr[i].l;
            strcpy(optimized[opt_count].r, pr[i].r);
            opt_count++;
        }
    }
    
    printf("\nOptimized Code:\n");
    for(i = 0; i < opt_count; i++) {
        printf("%c = %s\n", optimized[i].l, optimized[i].r);
    }
    
    return 0;
}
