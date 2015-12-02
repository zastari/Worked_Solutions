#define TABSTOP_ARRAY_LENGTH 100
void get_tabstops(int *tabstops, char *tablist);
int *next_tabstop(int *tabstops, int col);
int compare(const void *a, const void *b);
