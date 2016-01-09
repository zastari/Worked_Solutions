/* KR 6-3: Write a cross-references that prints a list of all words in a
 *     document, and, for each word, a list of the line numbers on which it
 *     occurs. Remove noise words like "the", "and", and so on.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define NKEYS (sizeof stopwords / sizeof(char *))

/* List taken from http://www.ranks.nl/stopwords */
char *stopwords[] = {
    "a", "about", "above", "after", "again", "against", "all", "am", "an",
    "and", "any", "are", "aren't", "as", "at", "be", "because", "been",
    "before", "being", "below", "between", "both", "but", "by", "can't",
    "cannot", "could", "couldn't", "did", "didn't", "do", "does", "doesn't",
    "doing", "don't", "down", "during", "each", "few", "for", "from",
    "further", "had", "hadn't", "has", "hasn't", "have", "haven't", "having",
    "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers", "herself",
    "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm", "i've",
    "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's",
    "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of",
    "off", "on", "once", "only", "or", "other", "ought", "our", "ours",
    "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd",
    "she'll", "she's", "should", "shouldn't", "so", "some", "such", "than",
    "that", "that's", "the", "their", "theirs", "them", "themselves", "then",
    "there", "there's", "these", "they", "they'd", "they'll", "they're",
    "they've", "this", "those", "through", "to", "too", "under", "until",
    "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're", "we've",
    "were", "weren't", "what", "what's", "when", "when's", "where", "where's",
    "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't",
    "would", "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your",
    "yours", "yourself", "yourselves"
};

/* Tree of all words that appear in a document */
struct tref {
    char *key;
    struct tlist *lines;
    struct tref *left;
    struct tref *right;
};

/* Tree of line occurrences of an individual word */
struct tlist {
    int key;
    struct tlist *left;
    struct tlist *right;
};

/* Regular: Not in any special mode
      Init: Start of line (a # will be a valid preprocessor directive)
     Slash: A '/' was found that could lead into a comment
      Star: A '*' was found that could terminate a block comment
     Scomm: In a single-line comment "//"
     Bcomm: In a block comment
    Squote: In a single-quoted value
    Dquote: In a double-quoted value
       Esc: In an escape sequence
   Preproc: In a preprocessor block
 */
enum { REGULAR, INIT, SLASH, STAR, SCOMM, BCOMM, SQUOTE, DQUOTE, ESC, PREPROC };

int getword(char *word, int maxlen);
int binsearch(char *word, char **words, int len);
struct tref *addref(struct tref *node, char *key, int linenumber);
struct tlist *addline(struct tlist *node, int linenumber);
void printtree(struct tref *node);
void printlines(struct tlist *node);


int main(int argc, char **argv)
{
    char word[MAXWORD];
    int linenumber;
    struct tref *root = NULL;

    while((linenumber = getword(word, MAXWORD)) != EOF) {
        if(binsearch(word, stopwords, NKEYS) < 0) {
            root = addref(root, word, linenumber);
        }
    }

    printtree(root);

    return 0;
}


struct tref *addref(struct tref *node, char *key, int linenumber)
{
    /* Add key to the node tree.
     *
     * If a key already exists in the node tree, add the line on which
     *     it occurs to the occurrences tree for the given key.
     *
     * Returns: pointer to the node which was passed as an input argument.
     */

    int cmp;

    if(!node) {
        node = (struct tref *)malloc(sizeof(struct tref));
        node->key = strdup(key);
        node->left = node->right = NULL;
        node->lines = NULL;
        node->lines = addline(node->lines, linenumber);
    }
    else if((cmp = strcmp(key, node->key)) < 0) {
        node->left = addref(node->left, key, linenumber);
    }
    else if(cmp > 0) {
        node->right = addref(node->right, key, linenumber);
    }
    else {
        addline(node->lines, linenumber);
    }

    return node;
}


struct tlist *addline(struct tlist *node, int linenumber)
{
    if(!node) {
        node = (struct tlist *)malloc(sizeof(struct tlist));
        node->key = linenumber;
        node->left = node->right = NULL;
    }
    else if(linenumber < node->key) {
        node->left = addline(node->left, linenumber);
    }
    else if(linenumber > node->key) {
        node->right = addline(node->right, linenumber);
    }
    /* if linenumber == node->key, do nothing since the line already shows up
     *     and we aren't keeping any sort of count.
     */

    return node;
}


void printtree(struct tref *node)
{
    /* Print word tree via inorder traversal */

    if(node) {
        printtree(node->left);
        printf("%s: ", node->key);
        printlines(node->lines);
        printf("\n");
        printtree(node->right);
    }
}


void printlines(struct tlist *node)
{
    /* Print matching lines for a word via inorder traversal */
    if(node) {
        printlines(node->left);
        printf("%d ", node->key);
        printlines(node->right);
    }
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
     * Returns: Line number of matching word. or EOF if EOF is reached.
     */
    static int linenumber = 1;
    static int c = '\0';

    do {
        if(c == EOF) {
            return EOF;
        }
        if(c == '\n') {
            linenumber++;
        }
    } while(!isalpha(c = getchar()));

    int i;
    for(i = 0; (isalpha(c) || c == '\'' || c == '-') && i < maxlen-1; i++) {
        *(word+i) = c;
        c = getchar();
    }
    *(word+i) = '\0';

    return linenumber;
}


int binsearch(char *word, char **words, int len)
{
    /* Perform a binary search.
     *
     * Returns: Index of the matching string in words if one exists, -1 if no
     *     no match is found.
     */

    int low = 0, high = len-1;
    int mid;
    int comp;

    while(low <= high) {
        mid = (high - low)/2 + low;
        comp = strcmp(word, words[mid]);

        if(comp == 0) {
            return mid;
        }
        else if(comp < 0) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return -1;
}
