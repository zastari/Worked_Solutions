/* KR 4-13: Write a recursive version of the function reverse(s),
 *   which reverses the string s in place.
 */
#include <stdio.h>
#define MAXSIZE 100

void rreverse(char*);


void rreverse(char* s)
{
	static int i = 0, j = 0;
	char c;

	c = s[i];
	if(s[++i] != '\0') {
		rreverse(s);
	}
	s[j++] = c;
	i--;

	if(i == 0) {
		s[j] = '\0';
		j = 0;
	}
}


int main()
{
	char s[MAXSIZE] = "abcdefghijklmnopqrstuvwxyz";
	rreverse(s);
	printf("%s\n", s);

	return 0;
}
