/* KR 3-2: Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n \t as it copies the
 * string t to s. Use a switch. Write a function for the other direction as well,
 * converting escape sequences into the real characters.
 */
#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);


void escape(char s[], char t[])
{
    int i,j;
    for(i = 0, j = 0; t[i] != '\0'; i++) {
        switch(t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}


void unescape(char s[], char t[])
{
    int i, j;
    for(i = 0, j = 0; t[i] != '\0'; i++) {
        if(t[i] == '\\') {
            switch(t[++i]) {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                default:
                    s[j++] = '\\';
                    s[j++] = t[i];
            }
        }
        else {
            s[j++] = t[i];
        }
    }
    s[j] = '\0';
}


int main()
{
    char t[] = "Test\nline\tone";
    char s[2*sizeof(t)/sizeof(char)]; /* 2 multiplier since every char is esc char in worst case */

    escape(s,t);
    printf("%s\n", s);

    char r[sizeof(s)/sizeof(char)];
    unescape(r, s);
    printf("%s\n", r);

    return 0;
}
