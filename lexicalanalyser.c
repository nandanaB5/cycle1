#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100

const char *keywords[] = {
    "int","float","if","else","while","for","do","return","break","switch",
    "case","char","double","void","long","short","struct","typedef","static"
};
int keywordCount = sizeof(keywords)/sizeof(keywords[0]);

bool isKeyword(char *str) {
    for (int i = 0; i < keywordCount; i++)
        if (strcmp(str, keywords[i]) == 0) return true;
    return false;
}

bool isIdentifier(char *str) {
    if (!isalpha(str[0]) && str[0] != '_') return false;
    for (int i = 1; str[i]; i++)
        if (!isalnum(str[i]) && str[i] != '_') return false;
    return true;
}

bool isInteger(char *str) {
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i])) return false;
    return (strlen(str) > 0);
}

bool isDelimiter(char c) {
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == ',' || c == ';' || c == '(' || c == ')' ||
            c == '{' || c == '}' || c == '[' || c == ']');
}

int isOperator(char c, char next) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '>' || c == '<' || c == '!')
        return 1;
    return 0;
}

void lexicalAnalyzer(char *input) {
    int len = strlen(input);
    int left = 0, right = 0;

    while (right <= len) {
        // Skip whitespace
        if (input[right] == ' ' || input[right] == '\t' || input[right] == '\n') {
            if (left != right) {
                char token[MAX];
                strncpy(token, input + left, right - left);
                token[right - left] = '\0';

                if (isKeyword(token)) printf("Keyword     : %s\n", token);
                else if (isInteger(token)) printf("Integer     : %s\n", token);
                else if (isIdentifier(token)) printf("Identifier  : %s\n", token);
                else printf("Unidentified: %s\n", token);
            }
            right++;
            left = right;
            continue;
        }

        if (isOperator(input[right], input[right+1])) {
            if (left != right) {
                char token[MAX];
                strncpy(token, input + left, right - left);
                token[right - left] = '\0';

                if (isKeyword(token)) printf("Keyword     : %s\n", token);
                else if (isInteger(token)) printf("Integer     : %s\n", token);
                else if (isIdentifier(token)) printf("Identifier  : %s\n", token);
                else printf("Unidentified: %s\n", token);
            }

            if ((input[right] == '=' && input[right+1] == '=') ||
                (input[right] == '!' && input[right+1] == '=') ||
                (input[right] == '>' && input[right+1] == '=') ||
                (input[right] == '<' && input[right+1] == '=')) {
                printf("Operator    : %c%c\n", input[right], input[right+1]);
                right += 2;
            } else {
                printf("Operator    : %c\n", input[right]);
                right++;
            }
            left = right;
            continue;
        }

        if (isDelimiter(input[right])) {
            if (left != right) {
                char token[MAX];
                strncpy(token, input + left, right - left);
                token[right - left] = '\0';

                if (isKeyword(token)) printf("Keyword     : %s\n", token);
                else if (isInteger(token)) printf("Integer     : %s\n", token);
                else if (isIdentifier(token)) printf("Identifier  : %s\n", token);
                else printf("Unidentified: %s\n", token);
            }
            right++;
            left = right;
            continue;
        }

        right++;
    }
}

int main() {
    char code[MAX] = "   int   a  =   b +  c   ";
    printf("Anagha S\n");
    printf("For Expression: %s\n", code);
    lexicalAnalyzer(code);

    printf("\n");

    char code2[MAX] = "int x = ab + bc + 30 + switch + 0y";
    printf("For Expression: %s\n", code2);
    lexicalAnalyzer(code2);

    return 0;
}
