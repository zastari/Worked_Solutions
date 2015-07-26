// KR 1-6: Verify that getchar() != EOF is either 0 or 1
#include <stdio.h>

int main() {
    int c;
    int status;

    c = getchar();
    while( (status = ((c = getchar()) != EOF)) ) {
        printf("Value of getchar() != EOF: %d\n", status);
    }

    printf("Value of getchar() != EOF: %d\n", status);

    return 0;
}
