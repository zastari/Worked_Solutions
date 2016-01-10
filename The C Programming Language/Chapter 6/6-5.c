/* KR 6-5: Write a function undef that will remove a name and definition from
 *     the table maintained by lookup and install.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 4

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *install(char *name, char *defn);
int uninstall(char *name);
struct nlist **lookup(char *defn);

unsigned hash(char *s)
{
    unsigned hashval;
    for(hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}


struct nlist **lookup(char *name)
{
    struct nlist **pp;
    pp = &hashtab[hash(name)];

    while(*pp) {
        if(strcmp((*pp)->name, name) == 0) {
            return pp;
        }
        pp = &(*pp)->next;
    }

    return NULL;
}


struct nlist *install(char *name, char *defn)
{
    struct nlist *np, **pp;
    unsigned hashval;

    pp = lookup(name);
    if(pp) {
        np = *pp;
        free(np->defn);
    }
    else {
        if(!(np = malloc(sizeof(*np))))
            return NULL;
        if(!(np->name = strdup(name)))
            return NULL;

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }

    if(!(np->defn = strdup(defn))) {
        return NULL;
    }

    return np;
}


int uninstall(char *name)
{
    /* Uninstall a module
     *
     * Returns: -1 if a module is not found, 0 if it is removed successfully.
     */
    struct nlist **pp, **temp;

    if(!(pp = lookup(name)))
        return -1;

    free((*pp)->name);
    free((*pp)->defn);

    temp = pp;
    (*pp) = (*pp)->next;
    free(temp);

    return 0;
}


int main(void)
{
    return 0;
}
