/* KR 5-19: Modify undcl so that it does not add redundant parentheses to
 *   declarations.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, ERROR };

int gettoken(void);
void skipspace(void);

int tokentype;
char token[MAXTOKEN];
char out[1000];
char *line = NULL;

void skipspace(void)
{
    while(*line == ' ' || *line == '\t') {
        line++;
    }
}


/* gettoken: return next token */
int gettoken(void)
{
    char *p = token;
    skipspace();

    if(*line == '(') {
        if(*++line == ')') {
            strcpy(token, "()");
            line++;
            return tokentype = PARENS;
        }
        else {
            return tokentype = '(';
        }
    }
    else if(*line == '[') {
        *p++ = *line++;
        skipspace();    /* Ignore space of the form [   #] */
        while(isdigit(*line)) {
            *p++ = *line++;
        }
        skipspace();    /* Ignore space of the form [#   ] */
        if(*line == ']') {
            *p++ = *line++;
            *p = '\0';
            return tokentype = BRACKETS;
        }
        else {
            printf("Error: Missing ]\n");
            return tokentype = ERROR;
        }
    }
    else if(isalpha(*line)) {
        do {
            *p++ = *line++;
        } while(isalpha(*line));
        *p = '\0';
        return tokentype = NAME;
    }
    else {
        return tokentype = *line++;
    }
}


int main(void)
{
    size_t n = 0;
    int type;
    char temp[MAXTOKEN];
    int is_dcl;

    while((line = NULL) || getline(&line, &n, stdin) != -1) {
        is_dcl = 0;
        gettoken();
        strcpy(out, token);
        while((type = gettoken()) != '\n') {
            if(type == PARENS || type == BRACKETS) {
                if(is_dcl) {
                    is_dcl = 0;
                    sprintf(temp, "(%s)%s", out, token);
                    strcpy(out, temp);
                }
                else {
                    strcat(out, token);
                }
            }
            else if(type == '*') {
                is_dcl = 1;
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
            }
            else if(type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else {
                printf("Invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }

    return 0;
}
