// KR 1-8: Write a program to count blanks, tabs, and newlines.
# include <stdio.h>

int main()
{
    int c, nb, nt, nl;
    nb = nt = nl = 0;

    while((c = getchar()) != EOF) {
        if(c == ' ')
            nb++;
        else if(c == '\t')
            nt++;
        else if(c == '\n')
            nl++;
    }

    printf("Blanks: %d\nTabs: %d\nNewlines: %d\n", nb, nt, nl);

    return 0;
}
