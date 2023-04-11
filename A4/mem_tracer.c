/**
 * Description: This program executes multiple commands.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/10/23
 * Creation date: 3/29/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>

/**
*TRACE_NODE_STRUCT is a linked list of
*pointers to function identifiers
*TRACE_TOP is the head of the list is the top of the stack
**/
struct TRACE_NODE_STRUCT {
    char* functionid; // ptr to function identifier (a function name)
    struct TRACE_NODE_STRUCT* next; // ptr to next frama
    int index; // index of linked list
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL; // ptr to the top of the stack

/**
*NODE_STRUCT is a linked list of
*pointers to function identifiers
*HEAD is the head of the list is the top of the stack
**/
struct NODE_STRUCT {
    char* line; // ptr to line
    struct  NODE_STRUCT* next; // ptr to next
    int index; // index of linked list
    int length; //size of the list
};
typedef struct NODE_STRUCT NODE;
static NODE* HEAD = NULL; // ptr to the head of the list

/**
*DYNAMIC_ARRAY_STRUCT is an array of
*pointers to function identifiers
**/
struct DYNAMIC_ARRAY_STRUCT {
    char** line; // ptr to line
    int length; // size of the list
    int index; // index of the list
};
typedef struct DYNAMIC_ARRAY_STRUCT DYNAMIC_ARRAY;


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
    printf("File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, PRINT_TRACE(), p, t);
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
    printf("File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, PRINT_TRACE(), p, t);
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
    printf("File %s, line %d, function %s reallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), p);

}
#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)

/**
 * Print the nodes recursively in the linked list
 * assumption: starts at head node
 * input: a starting node that is the head
 * output: none
**/
void print_nodes(NODE* head){
    PUSH_TRACE("print_nodes");

    //set head to HEAD
    head = HEAD;

    //if the next node is not empty, print the index and the line
    //recursively call the function to continue printing
    if(head->next != NULL){
        printf("Linked List Index: %d, Line: %s", head->index, head->line);
        print_nodes(head->next);
    }

    POP_TRACE();
    return;
}

/* Delete the nodes in linked list until the end
 * assumption: starts at head node
 * input: a node
 * output: none
 */
void free_nodes(NODE* head){
    PUSH_TRACE("free_nodes");

    //while the current node is not empty, free node
    while (head != NULL){
            NODE* temp = head->next; //assign temp node to head's next node
            free(head->line); //free the line
            free(head); //free the node itself
            head = temp; //set the head to the temp
    }
    free(head); //free the current node

    POP_TRACE();
    return;

}

/* Free the node in the linked list
 * assumption: none
 * input: a command line and index
 * output: none
 */
void add_node(char* cmd_line, int index){
    PUSH_TRACE("add_node");

    // make a new node
    NODE* new_node = (NODE*) malloc(sizeof(NODE));

    //allocate memory for line
    new_node->line = (char*) malloc (sizeof(char) * strlen(cmd_line) + sizeof(char));

    //copy command line to line
    strcpy(new_node->line, cmd_line);

    //set new node's index to index
    new_node->index = index;

    //set new node's next node to HEAD
    new_node->next = HEAD;

    //set HEAD to the new node
    HEAD = new_node;

    POP_TRACE();
    return;

}

/* Free the memory allocated for the dynamic array
 * assumption: memory was properly allocated
 * input: array
 * output: none
 */
void free_array(DYNAMIC_ARRAY* array){
        PUSH_TRACE("free_array");

        //loop through the array to free each one
        for(int i = 0; i < array->index; i++){
                free(array->line[i]);
        }

        free(array->line); //free the line
        free(array); //free the array itself

        POP_TRACE();
        return;
}

/* Print the contents of the array
 * assumption: none
 * input: array
 * output: none
 */
void print_array(DYNAMIC_ARRAY* array){
        PUSH_TRACE("print_array");

        //loop through the array to print each item
        for(int i = 0; i < array->length; i++){
            printf("Index %d: %s\n", i, array->line[i]);
        }

        POP_TRACE();
        return;
}

/* Add command to the dynamic array
 * assumption: realloc works properly
 * input: array and command line
 * output: none
 */
void add_cmd(DYNAMIC_ARRAY* array, char* cmd_line){
        PUSH_TRACE("add_cmd");

        //if array index and array length are the same, extend the array
        if(array->index == array->length){
           array->length = array->length * 2; //extend array length by 2
           array->line = (char**)realloc(array->line, sizeof(char*) * array->length); //realloc for line
        }

        array->line[array->index] = (char*) malloc(strlen(cmd_line) * sizeof(char) + 1); //allocate memory for line of index
        strcpy(array->line[array->index], cmd_line); // copy command line to line of index
        array->index = array->index + 1; //increment array index

        POP_TRACE();
        return;
}

/* Create an array
 * assumption: none
 * input: none
 * output: none
 */
DYNAMIC_ARRAY* create_array(){
        PUSH_TRACE("create_array");

        //initialize a new array
        DYNAMIC_ARRAY* new_array = (DYNAMIC_ARRAY*) malloc(sizeof(DYNAMIC_ARRAY));

        //set length to 10
        new_array->length = 10;

        //allocate memory for line
        new_array->line = (char**)malloc(sizeof(char) * new_array->length);

        //set index to 0
        new_array->index = 0;

        POP_TRACE();
        return new_array;

}

/* Print to memtracer.c
 * assumption: none
 * input: none
 * output: 0 if succeess
 */
int print_to_mem_trace(){
        PUSH_TRACE("print_to_mem_trace");

        //char output_file[100] = {0}; // array to hold stdout
        char* file = "memtrace.out";

        //push the logs to their respective files
        //sprintf(output_file, "memtrace.out");

        //open output file and send fd_1 to mem_trace.out file
        int fd_1 = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fd_1, 1);

        //fflush(stdout); //clear output buffer

        close(fd_1);

        POP_TRACE();
        return 0;
}

// ------------------------------------------
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
// void make_extend_array()
// {
//     PUSH_TRACE("make_extend_array");
//     int i, j;
//     int **array;
//     int ROW = 4;
//     int COL = 3;
//
//     //make array
//     array = (int**) malloc(sizeof(int*)*4); // 4 rows
//     for(i=0; i<ROW; i++) {
//         array[i]=(int*) malloc(sizeof(int)*3); // 3 columns
//     for(j=0; j<COL; j++)
//         array[i][j]=10*i+j;
//     }//for
//
//     //display array
//     for(i=0; i<ROW; i++)
//         for(j=0; j<COL; j++)
//             printf("array[%d][%d]=%d\n",i,j,array[i][j]);
//
//     // and a new column
//     int NEWCOL = add_column(array,ROW,COL);
//
//     // now display the array again
//     for(i=0; i<ROW; i++)
//         for(j=0; j<NEWCOL; j++)
//             printf("array[%d][%d]=%d\n",i,j,array[i][j]);
//
//     //now deallocate it
//     for(i=0; i<ROW; i++)
//         free((void*)array[i]);
//     free((void*)array);
//
//     POP_TRACE();
//     return;
// }//end make_extend_array

#define MAX_LEN 100
// ----------------------------------------------
// function main
int main()
{
    PUSH_TRACE("main");

    //declare an array
    DYNAMIC_ARRAY* dynamic_array = create_array();

    char current_line[MAX_LEN]; //declare current line
    int index = 0; //declare index to 0
    print_to_mem_trace(); //call function to print trace

    //read from stdin
    while(fgets(current_line, MAX_LEN, stdin) != NULL){

        //change input to proper C string
        if (current_line[strlen(current_line) - 1] == '\n'){
                current_line[strlen(current_line) - 1] = '\0';
        }

        //add node to linked list
        add_node(current_line, index);

        //add command to array
        add_cmd(dynamic_array, current_line);

        index++;
    }
    print_nodes(HEAD); //print the nodes

    free_nodes(HEAD); //free the nodes

    free_array(dynamic_array); //free the array

    POP_TRACE(); //pop twice because there's things left in the stack
    POP_TRACE();

    return(0);
}// end main

