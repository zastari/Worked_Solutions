/* KR 6-1: Our version of getword does not properly handle underscores,
 *   string constants, comments, or preprocessor control lines. Write a better
 *   version.
 *
 *   Solution Notes: Uses a modified version of 1-23's parser to evaluate
 *       whether a token is in a quote, comment, or preprocessor directive.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))

struct key {
    char *word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

/* Regular: Not in any special mode
      Init: Start of line (a # will be a valid preprocessor directive)
     Slash: A '/' was found that could lead into a comment
      Star: A '*' was found that could terminate a block comment
     Scomm: In a single-line comment "//"
     Bcomm: In a block comment
    Squote: In a single-quoted value
    Dquote: In a double-quoted value
       Esc: In an escape sequence
   Preproc: In a preprocessor block
 */
enum { REGULAR, INIT, SLASH, STAR, SCOMM, BCOMM, SQUOTE, DQUOTE, ESC, PREPROC };

int getfchar();
int getword(char *, int);
int binsearch(char *, struct key *, int);


int main(void)
{
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF) {
        if((n = binsearch(word, keytab, NKEYS)) > 0) {
            keytab[n].count++;
        }
    }

    for(n = 0; n < NKEYS; n++) {
        printf("%4d %s\n", keytab[n].count, keytab[n].word);
    }

    return 0;
}


int getword(char *word, int maxlen)
{
    int c, i;
    /* Advance to next word */
    while((c = getfchar()) != EOF && !isalnum(c) && c != '_');

    if(c == EOF) {
        return EOF;
    }

    /* Ignore tokens like _int or 3int */
    if(isdigit(c) || c == '_') {
        while((c = getfchar()) == '_' || isalnum(c));
        *word = '\0';
        return 0;
    }

    for(i = 0; isalpha(c) && i < maxlen-1; i++) {
        *(word+i) = c;
        c = getfchar();
    }

    /* Ignore tokens like int_ or int3 */
    if(isdigit(c) || c == '_') {
        *word = '\0';
        return 0;
    }

    *(word+i) = '\0';
    return i;
}


int binsearch(char *word, struct key *keytab, int len)
{
    int low = 0, high = len-1;
    int mid;
    int comp;

    while(low <= high) {
        mid = (high - low)/2 + low;
        comp = strcmp(word, keytab[mid].word);

        if(comp == 0) {
            return mid;
        }
        else if(comp < 0) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return -1;
}


int getfchar()
{
    static int mode = INIT;
    static int mode_prev = INIT;
    int c;

    while((c = getchar()) != EOF) {
        switch(c) {
        case '"':
            if(mode == REGULAR || mode == INIT) mode = DQUOTE;
            else if(mode == DQUOTE) mode = REGULAR;
            else if(mode == ESC) mode = mode_prev;
            break;
        case '\'':
            if(mode == REGULAR || mode == INIT) mode = SQUOTE;
            else if(mode == SQUOTE) mode = REGULAR;
            else if(mode == ESC) mode = mode_prev;
            break;
        case '\\':
            if(mode != ESC && mode != SCOMM && mode != BCOMM) {
                mode_prev = mode;
                mode = ESC;
            }
            else if(mode == ESC) mode = mode_prev;
            break;
        case '/':
            if(mode == REGULAR || mode == INIT) mode = SLASH;
            else if(mode == SLASH) mode = SCOMM;
            else if(mode == STAR) mode = REGULAR;
            else if(mode == ESC) mode = mode_prev;
            break;
        case '*':
            if(mode == SLASH) mode = BCOMM;
            else if(mode == BCOMM) mode = STAR;
            else if(mode == ESC) mode = mode_prev;
            else if(mode == REGULAR || mode == INIT) return c;
            break;
        case '#':
            if(mode == INIT) mode = PREPROC;
            break;
        case '\n':
            if(mode != ESC && mode != BCOMM) {
                mode = INIT;
                return c;
            }
            else if(mode == ESC) mode = mode_prev;
            break;
        default:
            if(mode == STAR) mode = BCOMM;
            else if(mode == SLASH) mode = REGULAR;
            else if(mode == ESC) mode = mode_prev;
            else if(mode == REGULAR || mode == INIT) {
                if(mode == INIT && !isspace(c)) {
                    mode = REGULAR;
                }
                return c;
            }
        }
    }

    return EOF;
}
