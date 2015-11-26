/* KR 4-12: Adapt the ideas of printd to write a recursive version of itoa;
 *   that is, convert an integer to a string by calling a recursive routine.
 */
#include <stdio.h>
#define MAXSIZE 100

void ritoa(int, char[]);


void ritoa(int num, char s[])
{
	static int i = -1;
	static int stack_depth = 0;

	stack_depth += 1;

	if(num < 0) {
		s[++i] = '-';
		num = -num;
	}

	if(num > 9) {
		ritoa(num / 10, s);
	}
	s[++i] = num % 10 + '0';

	stack_depth -= 1;
	if(stack_depth == 0) {
		s[++i] = '\0';
		i = -1;
	}
}


int main(void)
{
	int num;
	char s[MAXSIZE];

	num = 186207;
	ritoa(num, s);
	printf("%s\n", s);

	num = 388;
	ritoa(num, s);
	printf("%s\n", s);

	num = -123456789;
	ritoa(num, s);
	printf("%s\n", s);
	return 0;
}
