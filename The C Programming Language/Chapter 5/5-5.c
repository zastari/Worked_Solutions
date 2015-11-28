/* KR 5-5: Write versions of the library functions strncpy, strncat, and
 *  strncmp, which operate on at most the first n characters of their argument
 *  strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 */
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100

void mystrncpy(char *s, char *t, int n);
void mystrncat(char *s, char *t, int n);
int mystrncmp(char *s, char *t, int n);


void mystrncpy(char *s, char *t, int n)
{
    int i = 0;
    while(*t != '\0' && i < n) {
        *s++ = *t++;
        i++;
    }
    *s = '\0';
}


void mystrncat(char *s, char *t, int n)
{
    int i = 0;
    while(*s) {
        s++;
        i++;
    }
    while(*t != '\0' && i < n) {
        *s++ = *t++;
        i++;
    }
    *s = '\0';
}


int mystrncmp(char *s, char *t, int n)
{
    int i = 0;
    while(*s == *t && i < n) {
        if(*s == '\0') {
            return 0;
        }
        s++, t++, i++;
    }

    if(i == n) {
        return 0;
    } else {
        return *s - *t;
    }
}


int main(void)
{
    char s[MAXSIZE] = "abc";
    char t[MAXSIZE] = "abracadabra";
    mystrncpy(s, t, 6);
    printf("%s\n", s);

    strncpy(t, "", MAXSIZE);
    mystrncpy(s, t, 6);
    printf("%s\n", s);

    strncpy(s, "foo", MAXSIZE);
    strncpy(t, "bar", MAXSIZE);
    mystrncat(s, t, 5);
    printf("%s\n", s);

    strncpy(s, "foobar", MAXSIZE);
    strncpy(t, "foobar", MAXSIZE);
    printf("%d\n", mystrncmp(s, t, 10));
    printf("%d\n", mystrncmp(s, t, 4));

    strncpy(t, "fooby", MAXSIZE);
    printf("%d\n", mystrncmp(s, t, 10));
    printf("%d\n", mystrncmp(s, t, 4));
    printf("%d\n", mystrncmp(s, t, 5));
    return 0;
}
