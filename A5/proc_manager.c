/**
 * Description: This program executes multiple commands with timer.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/23/23
 * Creation date: 4/21/23
 **/

//note: ask about time and should it stop by itself?

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

/* table entry: */
struct nlist {
    struct nlist *next; /* next entry in chain */
    struct timespec start_time; //start time
    struct timespec finish_time; //finish time
    int index; // this is the line index in the input text file */
    int pid; // the process id. you can use the pid result of wait to lookup in the hashtable */
    char *command; // command. This is good to store for when you decide to restart a command */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* This is the hash function: form hash value for string s */
/* TODO change to: unsigned hash(int pid) */
/* TODO modify to hash by pid . */
/* You can use a simple hash function: pid % HASHSIZE */
unsigned hash(int pid) {
    return pid % HASHSIZE;
}

/* lookup: look for pid in hashtab */
/* TODO change to lookup by pid: struct nlist *lookup(int pid) */
/* TODO modify to search by pid, you won't need strcmp anymore */
/* This is traversing the linked list under a slot of the hash
table. The array position to look in is returned by the hash
function */
struct nlist *lookup(int pid) {
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->next){
        if (pid == np->pid){
            return np; /* found */
        }
    }
    return NULL; /* not found */
}

//char *strdup(char *);
/* insert: put (name, defn) in hashtab */
/* TODO: change this to insert in hash table the info for a new pid and its command */
/* TODO: change signature to: struct nlist *insert(char *command, int pid, int index). */
/* This insert returns a nlist node. Thus when you call insert in your main function */
/* you will save the returned nlist node in a variable (mynode).*/
/* Then you can set the starttime and finishtime from your main function: */
/* mynode->starttime = starttime; mynode->finishtime = finishtime; */
struct nlist *insert(char *command, int pid, int index) {
    struct nlist *np;
    unsigned hashval;

    //TODO change to lookup by pid. There are 2 cases:
    if ((np = lookup(pid)) == NULL) {
    /* case 1: the pid is not found, so you have to create it with malloc. Then you want to set
    the pid, command and index */
        np = (struct nlist *) malloc(sizeof(*np));

        //set the command
        if ((np->command = strdup(command)) == NULL){
            return NULL;
        }

        np->pid = pid; //set the pid
        np->index = index; //set the index

        hashval = hash(pid); //generate hash val with pid

        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }

    /* case 2: the pid is already there in the
    hashslot, i.e. lookup found the pid. In this case you can either
    do nothing, or you may want to set again the command and index
    (depends on your implementation). */
    else {
        //set the command
        if ((np->command = strdup(command)) == NULL){
            return NULL;
        }

        //set index
        np->index = index;
    }

    return np;
}

/** You might need to duplicate the command string to ensure you
don't overwrite the previous command each time a new line is read
from the input file. Or you might not need to duplicate it. It depends on your
implementation. **/
// char* strdup(char* s){ /* make a duplicate of s */
//     char *p;
//     p = (char *) malloc(strlen(s)+1); /* +1 for */
//     if (p != NULL){
//         strcpy(p, s);
//     }
//     return p;
// }

//#define MAX_CHAR 100
#define MAX_LEN 30

void execvp_func(char command[], bool restart, int cmd_count){
    //split current line into parts by words
    char *argument[MAX_LEN + 1] = {0};
    char *word = strtok(command, " ");
    int counter = 0;

    //separate each word based on space
    while(word != NULL && counter < MAX_LEN - 1){
        argument[counter] = word;
        counter++;
        word = strtok(NULL, " ");
    }
    argument[counter++] = NULL; //set end of array to NULL

    char output_file[MAX_LEN]; // array to hold stdout
    char error_file[MAX_LEN]; // array to hold stderr

    //push the logs to their respective files
    sprintf(output_file, "%d.out", (int) getpid());
    sprintf(error_file, "%d.err", (int) getpid());

    //open log files
    int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
    int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);

    //send fd_1 to PID.out file and fd_2 to PID.err for the PID
    dup2(fd_1, 1);
    dup2(fd_2, 2);

    // if restart is true, print RESTARTING to stdout and set cmd_count to 1
    if(restart){
        fprintf(stdout, "RESTARTING\n");
        fprintf(stderr, "RESTARTING\n");
        cmd_count = 1;
    }

    fprintf(stdout,"Starting command %d: child %d pid of parent %d\n", cmd_count, getpid(), getppid());

    fflush(stdout); //clear output buffer

    //check if execvp ran properly
    if(execvp(argument[0], argument) == -1){
        perror(argument[0]);
        exit(2);
    }
}


/**
 * Read from stdin and run the commands in parallel
 * assumptions: there is at least one line of command of 2 parameters
 * input: commands
 * output: command results in output and error file
**/
int main(int argc, char *argv[]){

    int status; //declare status
    pid_t child; //declare child pid

    char current_line[MAX_LEN]; //array to store current line read
    int line_count = 0; //counter for line count
    int cmd_count = 0; //counter for the amount of commands, acts as the index
    struct timespec start; //record starting time

    //while loop reads from stdin/terminal input
    // && line_count < MAX_CHAR
    while(fgets(current_line, MAX_LEN, stdin)){
        //convert to C string
        if (current_line[strlen(current_line) - 1] == '\n'){
            current_line[strlen(current_line) - 1] = '\0';
        }

        cmd_count++;

        //record the starting time
        clock_gettime(CLOCK_MONOTONIC, &start);

        //spawn a child
        child = fork();

        //exit if child process did not spawn
        if(child < 0){
            fprintf(stderr, "Fork failed");
            exit(1);
        }

        //child process
        else if (child == 0){
            //call the execvp_func
            execvp_func(current_line, false, cmd_count);

        }
        else if (child > 0){
            //add a new entry to hash table
            struct nlist* entry_new = insert(current_line, child, cmd_count);
            entry_new->start_time = start;
        }
    }

    struct timespec finish; //initialize to hold finished time
    double elasped_time; // variable to hold elapsed time
    struct nlist* entry; // used to find entry in hash table

    //parent process
    while((child = wait(&status)) > 0){
        //record finished time
        clock_gettime(CLOCK_MONOTONIC, &finish);

        //lookup entry
        entry = lookup(child);

        //store finished time
        entry->finish_time = finish;

        //calculate elasped time
        elasped_time = entry->finish_time.tv_sec - entry->start_time.tv_sec;

        char output_file[MAX_LEN] = {0}; // array to hold stdout
        char error_file[MAX_LEN] = {0}; // array to hold stderr

        //push the logs to their respective files
        sprintf(output_file, "%d.out", child);
        sprintf(error_file, "%d.err", child);

        //open output file and send fd_1 to PID.out file
        int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fd_1, 1);

        fflush(stdout); //clear output buffer

        //open err file and send fd_2 to PID.err file
        int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fd_2, 2);


        //if process exited normally
        if (WIFEXITED(status)) {
            fprintf(stdout, "Finished child %d pid of parent %d\n", child, (int) getpid());
            fprintf(stdout, "Finished at %ld, runtime duration %0.2f\n", entry->finish_time.tv_sec, elasped_time);
            fflush(stdout); //clear stdout
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));

            if(elasped_time <= 2){
                fprintf(stderr, "Spawning too fast\n");
            }
        }
        //if process killed
        else if (WIFSIGNALED(status)) {
                fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));

                if(elasped_time <= 2){
                    fprintf(stderr, "Spawning too fast\n");
                }
        }

        //decide if need to restart process
        while (elasped_time > 2){
            //record start time
            clock_gettime(CLOCK_MONOTONIC, &start);

            //spawn child
            child = fork();

            //exit if child process did not spawn
            if(child < 0){
                fprintf(stderr, "Fork failed");
                exit(1);
            }

            //child process
            else if(child == 0){
                //call execvp_func on the command that needs to restart
                execvp_func(entry->command, true, cmd_count);
            }

            //parent process
            else if (child > 0){
                //add new entry to hash table
                struct nlist* entry_new = insert(current_line, child, cmd_count);
                entry_new->start_time = start;
            }
        }
    }

    line_count++; //increase line count

    return 0;
}
