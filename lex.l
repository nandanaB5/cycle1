%{
#include <stdio.h>
#include <string.h>

char name[40];
char sub[5];   
%}

%%
[0-9A-Za-z]+ {
    if (strstr(yytext, sub) == NULL)
        printf("%-10s : does NOT contain '%s'\n", yytext, sub);
    else
        printf("%-10s : contains '%s'\n", yytext, sub);
}
[ \t\n]+    ;  
%%

int yywrap(void) {
    return 1;
}

int main() {
    printf("Enter your name: ");
    scanf("%s", name);
    
    strncpy(sub, name, 4);
    sub[4] = '\0';

    printf("Enter input text:\n");
    yylex();
    return 0;
}
