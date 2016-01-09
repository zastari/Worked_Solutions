/* KR 6-2: Write a program that reads a C program and prints in alphabetical
 *   order each group of variable names that are identical in the first 6
 *   characters, but different somewhere thereafter. Don't count words within
 *   strings and comments. Make 6 a parameter that can be set from the command
 *   line
 *
 * Solution Notes:
 *   This solution assumes that any word that isn't on the reserved word
 *   listing represents a variable. This isn't completely accurate since
 *   custom types also fall into this category.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define NKEYS (sizeof reservedwords / sizeof(char *))

char *reservedwords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

struct tnode {
    char *key;
    int count;
    struct tnode *left;
    struct tnode *right;
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
int getword(char *word, int maxlen);
int binsearch(char *word, char **words, int len);
struct tnode *addtree(struct tnode *node, char *key);
void printtree(struct tnode *node);


int main(int argc, char **argv)
{
    char varname[MAXWORD];
    struct tnode *root = NULL;
    int matchlen = 6;

    if(argv[1]) {
        matchlen = atoi(argv[1]);
    }

    while(getword(varname, MAXWORD) != EOF) {
        if(binsearch(varname, reservedwords, NKEYS) < 0) {
            char vargroup[matchlen+1];
            strncpy(vargroup, varname, matchlen);
            vargroup[matchlen] = '\0';

            root = addtree(root, vargroup);
        }
    }

    printtree(root);

    return 0;
}


struct tnode *addtree(struct tnode *node, char *key)
{
    /* Add key to the node tree. If key already exists, increment its count */

    int cmp;

    if(!node) {
        node = (struct tnode *)malloc(sizeof(struct tnode));
        node->count = 1;
        node->key = strdup(key);
        node->left = node->right = NULL;
    }
    else if((cmp = strcmp(key, node->key)) < 0) {
        node->left = addtree(node->left, key);
    }
    else if(cmp > 0) {
        node->right = addtree(node->right, key);
    }
    else {
        node->count++;
    }

    return node;
}


void printtree(struct tnode *node)
{
    /* Print tree via inorder traversal */

    if(node) {
        printtree(node->left);
        printf("%s\n", node->key);
        printtree(node->right);
    }
}


int getword(char *word, int maxlen)
{
    /* Retrieve the next word from the input stream */

    int c, i;
    /* Advance to next word */
    while((c = getfchar()) != EOF && !isalnum(c) && c != '_');

    if(c == EOF) {
        return EOF;
    }

    for(i = 0; isalpha(c) && i < maxlen-1; i++) {
        *(word+i) = c;
        c = getfchar();
    }

    *(word+i) = '\0';
    return i;
}


int binsearch(char *word, char **words, int len)
{
    /* Perform a binary search. Return the index if the word is in the words
     *     list. Return -1 if it is not in the list.
     */

    int low = 0, high = len-1;
    int mid;
    int comp;

    while(low <= high) {
        mid = (high - low)/2 + low;
        comp = strcmp(word, words[mid]);

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
    /* Return the next character in the input stream that is not a part of a
       preprocessor directive, comment, quote, or escape sequence */

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
