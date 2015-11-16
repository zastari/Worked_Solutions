#define NUMBER '0'
/* KR 4-4: Add support for peek, clear, swap */
#define PEEK 'p'
#define CLEAR 'c'
#define REPLACE 'r'
/* KR 4-5: Add support for sin, exp, pow */
#define SIN 's'
#define EXP 'e'
#define POW 'n'
/* KR 4-6: Add support for handling variables */
#define VAR_GET ':'

int getop(char []);

int getch(void);
void ungetch(int);
void ungets(char []);

void push(double);
double pop(void);
void clear(void);
