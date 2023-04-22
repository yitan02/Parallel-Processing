/**
 * Description: This program executes multiple commands with timer.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/21/23
 * Creation date: 4/21/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* table entry: */
struct nlist {
    struct nlist *next; /* next entry in chain */
    struct timespec start_time;
    struct timespec finish_time;
    int index; // this is the line index in the input text file */
    int pid; // the process id. you can use the pid result of wait to lookup in the hashtable */
    char *command; // command. This is good to store for when you decide to restart a command */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
/* This is the hash function: form hash value for string s */
/* TODO change to: unsigned hash(int pid) */
/* TODO modify to hash by pid . /*
/* You can use a simple hash function: pid % HASHSIZE */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}
/* lookup: look for s in hashtab */
/* TODO change to lookup by pid: struct nlist *lookup(int pid) */
/* TODO modify to search by pid, you won't need strcmp anymore */
/* This is traversing the linked list under a slot of the hash
table. The array position to look in is returned by the hash
function */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next){
        if (strcmp(s, np->name) == 0){
            return np; /* found */
        }
    }
    return NULL; /* not found */
}
char *strdup(char *);
/* insert: put (name, defn) in hashtab */
/* TODO: change this to insert in hash table the info for a new pid and its command */
/* TODO: change signature to: struct nlist *insert(char *command, int pid, int index). */
/* This insert returns a nlist node. Thus when you call insert in your main function */
/* you will save the returned nlist node in a variable (mynode).*/
/* Then you can set the starttime and finishtime from your main function: */
/* mynode->starttime = starttime; mynode->finishtime = finishtime; */
struct nlist *insert(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    //TODO change to lookup by pid. There are 2 cases:
    if ((np = lookup(name)) == NULL) {
    /* case 1: the pid is not
    found, so you have to create it with malloc. Then you want to set
    the pid, command and index */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL){
            return NULL;
        }
        hashval = hash(name);

        if ((np->defn = strdup(defn)) == NULL){
            return NULL;
        }
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else { } /* case 2: the pid is already there in the
    hashslot, i.e. lookup found the pid. In this case you can either
    do nothing, or you may want to set again the command and index
    (depends on your implementation). */
    //free((void *) np->defn); /*free previous defn */
    return np;
}

/** You might need to duplicate the command string to ensure you
don't overwrite the previous command each time a new line is read
from the input file. Or you might not need to duplicate it. It depends on your
implementation. **/
char *strdup(char *s){ /* make a duplicate of s */
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for */
    if (p != NULL){
        strcpy(p, s);
    }
    return p;
}
