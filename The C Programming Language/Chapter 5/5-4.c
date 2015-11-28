/* KR 5-4: Write the function strend(s,t), which returns 1 if the string t
 *   occurs at the right end of s and 0 otherwise.
 */
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100

int strend(char *, char*);


int strend(char *s, char *t)
{
    char *x = s, *y = t;

    /* Go to end of s and t */
    while(*x) {
        x++;
    }
    while(*y) {
        y++;
    }

    /* Compare them in reverse */
    while(x >= s && y >= t) {
        if(*x-- != *y--) {
            return 0;
        }
    }

    if(y > t) {     /* t was longer than s */
        return 0;
    }

    return 1;
}


int main(void)
{
    char s[100] = "foobar";
    char t[100] = "bar";
    printf("s = %s, t = %s, strend(s,t) = %d\n", s, t, strend(s,t));

    strncpy(s, "foobar", MAXSIZE);
    strncpy(t, "bazfoobar", MAXSIZE);
    printf("s = %s, t = %s, strend(s,t) = %d\n", s, t, strend(s,t));

    strncpy(s, "foo", MAXSIZE);
    strncpy(t, "bar", MAXSIZE);
    printf("s = %s, t = %s, strend(s,t) = %d\n", s, t, strend(s,t));

    strncpy(s, "foo", MAXSIZE);
    strncpy(t, "foo", MAXSIZE);
    printf("s = %s, t = %s, strend(s,t) = %d\n", s, t, strend(s,t));

    return 0;
}
