/* KR 1-23: Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C
 * comments do not nest.
 */
#include <stdio.h>

int main()
{
    /* A few test strings */
    char *j = "Hey \" look a // string with /* comment blocks */ and nested quotes";
    int k = '"';
    k = '\'';

     /* Mode types: 0 - In normal code block
                    1 - In single line comment
                    2 - In block comment
                    3 - Inside single-quoted string
                    4 - Inside double-quoted string
                    5 - Inside escape sequence */
    int c, c_prev, mode, mode_prev;
    mode = mode_prev = c_prev = 0;
    while((c=getchar()) != EOF) {
        if((mode==0 && c!='/') || mode==3 || mode==4 || mode==5)
            putchar(c);

        switch(mode) {
        case 0:
            if(c == '/') {
                c_prev = c;
                c = getchar();
                if(c == '/')        /* mode = 1 if we encounter "//" in the input buffer */
                    mode = 1;
                else if(c == '*')
                    mode = 2;       // mode = 2 if we encounter "/*" in the input buffer */
                else {
                    putchar(c_prev);
                    if(c != EOF)    // Handle programs that end with a '/'
                        putchar(c);
                }
            }
            else if(c == '\'')
                mode = 3;
            else if(c == '"')
                mode = 4;
            else if(c == '\\') {
                mode_prev = mode;
                mode = 5;
            }
            break;
        case 1:
            if(c == '\n') {
                putchar(c);
                mode = 0;
            }
            break;
        case 2:
            if(c == '*') {
                while((c=getchar()) == '*');    /* Handle comments like this one **//* or this one ****/
                if(c == '/')
                    mode = 0;
            }
            break;
        case 3:
            if(c == '\'')
                mode = 0;
            else if(c == '\\') {
                mode_prev = mode;
                mode = 5;
            }
            break;
        case 4:
            if(c == '"')
                mode = 0;
            else if(c == '\\') {
                mode_prev = mode;
                mode = 5;
            }
            break;
        case 5:
            mode = mode_prev;
            break;
        }
    }

    return 0;
}
