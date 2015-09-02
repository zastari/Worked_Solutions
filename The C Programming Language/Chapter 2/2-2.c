/* KR 2-2: Write a loop equivalent to the for loop without using && or ||:
 *      for(i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 *          s[i] = c;
 */
#include <stdio.h>

#define LIMIT 20

int main()
{
    char s[LIMIT];
    int lim = LIMIT;
    int i, exit, c;
    exit = 0;
    for(i = 0; exit == 0; ++i) {
        if(i >= lim-1)
            exit = 1;
        else if((c=getchar()) == '\n')
            exit = 1;
        else if(c == EOF)
            exit = 1;
        else
            s[i] = c;
    }
    s[i+1] = '\0';

    printf("%s\n", s);

    return 0;
}
