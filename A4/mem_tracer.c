
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
/**
 *Checklist:
 *  -insert A3 code
 *  -use malloc to create a dynamic array of 10 char * pointers
 *  -implement realloc to expand the dynamic array size
 *  -figure out how to store line and index in linked list node
 *  -create recursive function printNodes that prints contents of printNodes
 *  +create function for allocating(done), reallocating(done), and freeing memory (done)
 *  -create memory consumption tracing function that implements the three functions above
 *  -memory consumption tracing function should be ran on dynamic array and array linked list (using stack given)
 *  -write all memory tracing messages to file name memtrace.out using dup2
 *  -take input and store in char ** array and linked list
 *  -run valgrind to check for memory leak
 *
**/

/**
*TRACE_NODE_STRUCT is a linked list of
*pointers to function identifiers
*TRACE_TOP is the head of the list is the top of the stack
**/
struct TRACE_NODE_STRUCT {
    char* functionid; // ptr to function identifier (a function name)
    struct TRACE_NODE_STRUCT* next; // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL; // ptr to the top of the stack

/* --------------------------------*/
/* function PUSH_TRACE */
/*
* The purpose of this stack is to trace the sequence of function calls,
* just like the stack in your computer would do.
* The "global" string denotes the start of the function call trace.
* The char *p parameter is the name of the new function that is added to the call
trace.
* See the examples of calling PUSH_TRACE and POP_TRACE below
* in the main, make_extend_array, add_column functions.
**/
void PUSH_TRACE(char* p) // push p on the stack
{
    TRACE_NODE* tnode;
    static char glob[]="global";

        if (TRACE_TOP==NULL) {
            // initialize the stack with "global" identifier
            TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));
            // no recovery needed if allocation failed, this is only
            // used in debugging, not in production
            if (TRACE_TOP==NULL) {
                printf("PUSH_TRACE: memory allocation error\n");
                exit(1);
            }

        TRACE_TOP->functionid = glob;
        TRACE_TOP->next=NULL;
        }//if

// create the node for p
tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

// no recovery needed if allocation failed, this is only
// used in debugging, not in production
    if (tnode==NULL) {
        printf("PUSH_TRACE: memory allocation error\n");
        exit(1);
    }//if

    tnode->functionid=p;
    tnode->next = TRACE_TOP; // insert fnode as the first in the list
    TRACE_TOP=tnode; // point TRACE_TOP to the first node
}/*end PUSH_TRACE*/

/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */
void POP_TRACE() // remove the op of the stack
{
    TRACE_NODE* tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);
}/*end POP_TRACE*/

/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the
stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok:
funcC:funcB:funcA:global */
char* PRINT_TRACE()
{
    int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
    int i, length, j;
    TRACE_NODE* tnode;
    static char buf[100];

    if (TRACE_TOP==NULL) { // stack not initialized yet, so we are
        strcpy(buf,"global"); // still in the `global' area
        return buf;
    }

    /* peek at the depth(50) top entries on the stack, but do not
    go over 100 chars and do not go over the bottom of the
    stack */
    sprintf(buf,"%s",TRACE_TOP->functionid);
    length = strlen(buf); // length of the string so far
    for(i=1, tnode=TRACE_TOP->next;tnode!=NULL && i < depth;i++,tnode=tnode->next) {
        j = strlen(tnode->functionid); // length of what we want to add
        if (length+j+1 < 100) { // total length is ok
            sprintf(buf+length,":%s",tnode->functionid);
            length += j+1;
        }else // it would be too long
            break;
    }
    return buf;
} /*end PRINT_TRACE*/

// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p,int t,char* file,int line)
{
    p = realloc(p,t);
    printf("File mem_trace.c, line %d, function %s reallocated the memory segment at address %s to a new size %d", line, PRINT_TRACE, file, t);
    return p;
}

// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t,char* file,int line)
{
    void* p;
    p = malloc(t);
    printf("File mem_trace.c, line %d, function %s reallocated the memory segment at address %s to a new size %d", line, PRINT_TRACE, file, t);
    return p;
}

// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p,char* file,int line)
{
    free(p);
    printf("File mem_trace.c, line %d, function %s reallocated the memory segment at address %s", line, PRINT_TRACE, file);
    //%s might be %u
}
#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)
// -----------------------------------------
// function add_column will add an extra column to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
// Returns the number of new columns (updated)
int add_column(int** array,int rows,int columns)
{
    PUSH_TRACE("add_column");
    int i;

    for(i=0; i<rows; i++) {
        array[i]=(int*) realloc(array[i],sizeof(int)*(columns+1));
        array[i][columns]=10*i+columns;
    }//for
    POP_TRACE();
    return (columns+1);
}// end add_column

// ------------------------------------------
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
void make_extend_array()
{
    PUSH_TRACE("make_extend_array");
    int i, j;
    int **array;
    int ROW = 4;
    int COL = 3;

    //make array
    array = (int**) malloc(sizeof(int*)*4); // 4 rows
    for(i=0; i<ROW; i++) {
        array[i]=(int*) malloc(sizeof(int)*3); // 3 columns
    for(j=0; j<COL; j++)
        array[i][j]=10*i+j;
    }//for

    //display array
    for(i=0; i<ROW; i++)
        for(j=0; j<COL; j++)
            printf("array[%d][%d]=%d\n",i,j,array[i][j]);

    // and a new column
    int NEWCOL = add_column(array,ROW,COL);

    // now display the array again
    for(i=0; i<ROW; i++)
        for(j=0; j<NEWCOL; j++)
            printf("array[%d][%d]=%d\n",i,j,array[i][j]);

    //now deallocate it
    for(i=0; i<ROW; i++)
        free((void*)array[i]);
    free((void*)array);

    POP_TRACE();
    return;
}//end make_extend_array

// ----------------------------------------------
// function main
#define MAX_CHAR 100
#define MAX_LEN 30

int main()
{
    PUSH_TRACE("main");
    make_extend_array();
    POP_TRACE();
    //printNodes();

    /**-------------A3 code-------------**/
    int status; //declare status
    pid_t child; //declare child pid

    char current_line[MAX_LEN]; //array to store current line read
    //int line_count = 0; //counter for line count
    int cmd_count = 0; //counter for the amount of commands

    //while loop reads from stdin/terminal input
    while(fgets(current_line, MAX_LEN, stdin)){
        //convert to C string
        if (current_line[strlen(current_line) - 1] == '\n'){
            current_line[strlen(current_line) - 1] = '\0';
        }

        cmd_count++;

        //spawn a child
        child = fork();

        //exit if child process did not spawn
        if(child < 0){
            fprintf(stderr, "Fork failed");
            exit(1);
        }
        //child process
        //to do: malloc outside child process?
        //       initialize dynamic array outside child
        //       initialize linked list
        //       if statement for if dynamic array memory runs out, and implement realloc
        //       free in parent or child? (maybe parent)
        //       figure out where to implement memory tracing stack, called in child or parent?
        else if (child == 0){
            //split current line into parts by words
            char *argument[MAX_LEN + 1] = {0}; //to do: change to dynamic array
            char *word = strtok(current_line, " ");
            int counter = 0;

            //separate each word based on space
            while(word != NULL && counter < MAX_LEN - 1){
                argument[counter] = word;
                counter++;
                word = strtok(NULL, " ");
            }
            argument[counter++] = NULL; //set end of array to NULL

            char output_file[MAX_LEN]; // array to hold stdout, to do: change to dynamic size
            //char error_file[MAX_LEN]; // array to hold stderr

            //push the logs to their respective files
            sprintf(output_file, "mem_trace.out");
            //sprintf(error_file, "%d.err", (int) getpid());

            //open log files
            int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            //int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            //send fd_1 to PID.out file and fd_2 to PID.err for the PID
            dup2(fd_1, 1);
            //dup2(fd_2, 2);

            //fprintf(stdout,"Starting command %d: child %d pid of parent %d\n", cmd_count, getpid(), getppid());

            fflush(stdout); //clear output buffer

            //check if execvp ran properly
            if(execvp(argument[0], argument) == -1){
                perror(argument[0]);
                exit(2);
            }
        }
    }

    //parent process
    while((child = wait(&status)) > 0){
        char output_file[MAX_LEN] = {0}; // array to hold stdout
        //char error_file[MAX_LEN] = {0}; // array to hold stderr

        //push the logs to their respective files
        sprintf(output_file, "%d.out", child);
        //sprintf(error_file, "%d.err", child);

        //open output file and send fd_1 to PID.out file
        int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fd_1, 1);

        fflush(stdout); //clear output buffer

        //open err file and send fd_2 to PID.err file
        //int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        //dup2(fd_2, 2);

        //if process exited normally
        if (WIFEXITED(status)) {
            fprintf(stdout, "Finished child %d pid of parent %d\n", child, (int) getpid());
            fflush(stdout); //clear stdout
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }
        //if process killed
        else if (WIFSIGNALED(status)) {
                fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        }
    }

    //to do: printNodes

    //line_count++; //increase line count
    /**-------------A3 code-------------**/

    return(0);
}// end main

