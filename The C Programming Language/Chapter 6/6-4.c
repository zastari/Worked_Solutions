/* KR 6-4: Write a program that prints the distinct words in its input sorted
 *     into decreasing order of frequency and occurrence. Precede each word by
 *     its count.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

/* Tree of all words that appear in a document */
struct tword {
    char *key;
    int count;
    struct tlist *lines;
    struct tword *left;
    struct tword *right;
};


int getword(char *word, int maxlen);
struct tword *addword(struct tword *node, char *key, int *treesize);
void makelist(struct tword **twords, struct tword *node, int *i);
void qsort_twords(struct tword **twords, int left, int right);
void swap_twords(struct tword **twords, int a, int b);


int main(int argc, char **argv)
{
    char word[MAXWORD];
    struct tword *root = NULL;
    int treesize = 0;

    while(getword(word, MAXWORD) != EOF) {
        root = addword(root, word, &treesize);
    }

    struct tword *twords[treesize];
    int i = 0;
    makelist(twords, root, &i);

    qsort_twords(twords, 0, treesize-1);

    for(i = 0; i < treesize; i++) {
        printf("%4d %s\n", twords[i]->count, twords[i]->key);
    }

    return 0;
}


void qsort_twords(struct tword **twords, int left, int right)
{
    int i, pivot;

    if(left >= right) {
        return;
    }

    /* Choose middle of list as pivot */
    swap_twords(twords, (right - left)/2 + left, left);

    pivot = left;
    for(i = left+1; i <= right; i++) {
        if(twords[i]->count >= twords[left]->count) {
            swap_twords(twords, ++pivot, i);
        }
    }

    /* Since the pivot we selected is maximal in the list, move it to the end
     *     and we won't need to sort it */
    swap_twords(twords, left, pivot);

    qsort_twords(twords, left, pivot-1);
    qsort_twords(twords, pivot+1, right);
}


void swap_twords(struct tword **twords, int a, int b)
{
    struct tword *temp = twords[a];
    twords[a] = twords[b];
    twords[b] = temp;
}


void makelist(struct tword **twords, struct tword *node, int *i)
{
    if(node) {
        makelist(twords, node->left, i);
        twords[(*i)++] = node;
        makelist(twords, node->right, i);
    }
}


struct tword *addword(struct tword *node, char *key, int *treesize)
{
    /* Add word to a tword tree.
     *
     * Returns: pointer to the node which was passed as an input argument.
     */

    int cmp;

    if(!node) {
        node = (struct tword *)malloc(sizeof(struct tword));
        (*treesize)++;
        node->key = strdup(key);
        node->left = node->right = NULL;
        node->count = 1;
    }
    else if((cmp = strcmp(key, node->key)) < 0) {
        node->left = addword(node->left, key, treesize);
    }
    else if(cmp > 0) {
        node->right = addword(node->right, key, treesize);
    }
    else {
        node->count++;
    }

    return node;
}


int getword(char *word, int maxlen)
{
    /* Retrieve the next word from the input stream
     *
     * In this implementation, a word is defined as beginning with an
     * alpha character an subsequently containing only alpha characters,
     * hyphens, or apostrophes
     *
     * Mutates: word: Assigns matching word that was found.
     *
     * Returns: Word length.
     */
    static int c = '\0';

    do {
        if(c == EOF) {
            return EOF;
        }
    } while(!isalpha(c = getchar()));

    int i;
    for(i = 0; (isalpha(c) || c == '\'' || c == '-') && i < maxlen-1; i++) {
        *(word+i) = c;
        c = getchar();
    }

    /* While - and ' are allowed word characters, they can't be terminal */
    if(word[i-1] == '-' || word[i-1] == '\'') {
        word[i-1] = '\0';
        return i-1;
    } else {
        *(word+i) = '\0';
        return i;
    }
}
