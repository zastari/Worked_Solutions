// KR 1-12: Write a program that prints its input one word per line.
#include <stdio.h>

int is_whitespace(int);

int is_whitespace(int c)
{
    if(c == ' ' || c == '\t' || c == '\n')
        return 1;
    return 0;
}

int main()
{
    int c, prevc;
    prevc = 0;

    while((c = getchar()) != EOF) {
        if(is_whitespace(c)) {
            if(!is_whitespace(prevc))
                putchar('\n');
        }
        else
            putchar(c);

        prevc = c;
    }

    return 0;
}
