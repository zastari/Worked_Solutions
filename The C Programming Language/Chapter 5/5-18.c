/* KR 5-18: Make dcl recover from input errors.
 *
 * Solution Notes:
 *     - Converts character-at-a-time input scanning to getline() to cleanly
 *       abort on syntax errors.
 *     - Adds an ERROR gettoken() return  type that will be passed through the
 *       declarator stack if a token resolves an error.
 *     - Tightens array tokenization to only allow valid array declarations
 *       that match the regex:
 *           \[\s*[0-9]*\s*\]
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, ERROR };

int dcl(void);
int dirdcl(void);
int gettoken(void);
void skipspace(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char *line = NULL;

/* dcl: parse a declarator */
int dcl(void)
{
    int ns;

    for(ns = 0; gettoken() == '*'; ns++)
        ;

    if(dirdcl() == -1) {
        return -1;
    }

    while(ns-- > 0) {
        strcat(out, " pointer to");
    }

    return 0;
}


/* dirdcl: parse a direct declarator */
int dirdcl(void)
{
    int type;

    if(tokentype == '(') {
        if(dcl() == -1) {
            return -1;
        }
        if(tokentype != ')') {
            printf("Error: missing )\n");
            return -1;
        }
    }
    else if(tokentype == NAME) {
        strcpy(name, token);
    }
    else {
        printf("Error: Expected name or (dcl)\n");
        return -1;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if(type == PARENS) {
            strcat(out, " function returning");
        }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }

    if(tokentype != ERROR) {
        return 0;
    }
    else {
        return -1;
    }
}


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
    while((line = NULL) || getline(&line, &n, stdin) != -1) {
        out[0] = '\0';
        gettoken();
        if(isalpha(*token)) {
            strcpy(datatype, token);
        }
        else {
            printf("Syntax Error: Invalid declaration specifier\n");
            continue;
        }

        if(dcl() == -1) {
            printf("Syntax Error: Invalid declarator\n");
            continue;
        }

        if(tokentype == '\n') {
            printf("%s: %s %s\n", name, out, datatype);
        }
        else {
            printf("Syntax Error: Invalid declarator\n");
        }
    }
    return 0;
}
