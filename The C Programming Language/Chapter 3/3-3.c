/* KR 3-3: Write a function expand(s1,s2) that expands shorthand notations
 * like a-z in the string s1 into the equivalent complete list abc..xyz in
 * s2. Allow for letters of either case and digits, and be prepared to handle
 * cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is
 * taken literally.
 *
 * Notes: valid ranges are a-z, A-Z, 0-9 and any subsets of these ranges.
 * Any hyphen that does not complete a valid range will be taken literally.
 * Both ascending and descending ranges are valid. Ranges of the form a-a
 * will be returned literally.
 */
#include <stdio.h>
#include <ctype.h>
void expand(char s1[], char s2[]);

void expand(char s1[], char s2[])
{
    int i, j, k;
    i = j = 0;
    s2[j++] = s1[i++];  /* Always treat first character literally */

    while(s1[i] != '\0') {
        if(s1[i] == '-' && ( (isdigit(s1[i-1])&&isdigit(s1[i+1])) || (isupper(s1[i-1])&&isupper(s1[i+1])) || (islower(s1[i-1])&&islower(s1[i+1])) )) {
            if(s1[i-1] < s1[i+1]) {
                for(k = s1[i-1]+1; k < s1[i+1]; k++) {
                    s2[j++] = k;
                }
                ++i;
            }
            else if(s1[i-1] > s1[i+1]) {
                for(k = s1[i-1]-1; k > s1[i+1]; k--) {
                    s2[j++] = k;
                }
                ++i;
            }
        }

        s2[j++] = s1[i++];
    }

    s2[j] = '\0';
}


int main()
{
    char s1[] = "-abcA-Zd-o1-8a-Fzyxa-aF-aF-A8-3-";
    char s2[26*(sizeof(s1)/sizeof(char))/3]; /* Worst case: every block of 3 chars expands into 26 outputs */

    expand(s1,s2);
    printf("Original String: %s\n", s1);
    printf("Expanded String: %s\n", s2);
    return 0;
}
