/* KR 1-24: Write a program to check a C program for rudimentary
 * syntax errors like unbalanced parentheses, brackets and braces. Don't forget
 * about quotes, both single and double, escape sequences, and comments.
 */
#include <stdio.h>
#define STACKDEPTH 100  /* Maximum depth for command stack */

void print_stack(char stack[], int i);
char stack_char_conv(int i, int state);


void print_stack(char stack[], int i)
{
    int j;
    for(j=0; j<=i; j++)
        printf("%c", stack_char_conv(stack[j], 0));
}


char stack_char_conv(int i, int state)
{
    if(i == 0) {
        if(state == 0)
            return '{';
        else
            return '}';
    }
    else if(i == 1) {
        if(state == 0)
            return '[';
        else
            return ']';
    }
    else if(i == 2) {
        if(state == 0)
            return '(';
        else
            return ')';
    }
    else
        return '\0';
}


int main()
{
    /* Mode types: 0 - In normal code block
                   1 - In single line comment
                   2 - In block comment
                   3 - Inside single-quoted string
                   4 - Inside double-quoted string
                   5 - Inside escape sequence */

    /* Stack types: 0 - {
                    1 - [
                    2 - ( */
    int c, i, mode, mode_prev;
    int line, position;

    char stack[STACKDEPTH];
    mode = mode_prev = i = 0;
    line = position = 1;
    while((c=getchar()) != EOF) {
        switch(mode) {
        case 0:
            switch(c) {
                case '/':
                    c = getchar();
                    position++;
                    if(c == '/')
                        mode = 1;
                    else if(c == '*')
                        mode = 2;
                    break;
                case '\'':
                    mode = 3;
                    break;
                case '"':
                    mode = 4;
                    break;
                case '\\':
                    mode_prev = mode;
                    mode = 5;
                    break;
                case '{':
                    stack[i++] = 0;
                    break;
                case '[':
                    stack[i++] = 1;
                    break;
                case '(':
                    stack[i++] = 2;
                    break;
                case '}':
                    if(i == 0) {
                        printf("%d:%d - Terminal } with no prior opening character\n", line, position);
                        return 1;
                    }
                    else if(stack[--i] != 0) {
                        printf("%d:%d - Unbalanced }, expected %c\n", line, position, stack_char_conv(stack[i], 1));
                        return 1;
                    }
                    break;
                case ']':
                    if(i == 0) {
                        printf("%d:%d - Terminal ] with no prior opening character\n", line, position);
                        return 1;
                    }
                    else if(stack[--i] != 1) {
                        printf("%d:%d - Unbalanced ], expected %c\n", line, position, stack_char_conv(stack[i], 1));
                        return 1;
                    }
                    break;
                case ')':
                    if(i == 0) {
                        printf("%d:%d - Terminal ) with no prior opening character\n", line, position);
                        return 1;
                    }
                    else if(stack[--i] != 2) {
                        printf("%d:%d - Unbalanced ), expected %c\n", line, position, stack_char_conv(stack[i], 1));
                        return 1;
                    }
                    break;
            }
            break;
        case 1:
            if(c == '\n')
                mode = 0;
            break;
        case 2:
            if(c == '*') {
                while((c=getchar()) == '*');
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

        position++;
        if(c == '\n') {
            line++;
            position = 1;
        }
    }

    if(i == 0)
        printf("No syntax errors found\n");
    else {
        printf("Program ended with non-empty stack. Unterminated stack: ");
        print_stack(stack, i-1);
        putchar('\n');
        return 1;
    }

    return 0;
}
