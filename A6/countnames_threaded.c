/**
 * Description: This program executes counting names in files with threads
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 5/10/23
 * Creation date: 5/6/23
 **/

/*****************************************
//CS149 SP23
//Template for assignment 6
//San Jose State University
//originally prepared by Bill Andreopoulos
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

//thread mutex lock for access to the log index
//use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for critical sections of allocating THREADDATA
//use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for access to the name counts data structure
//use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT{
    pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;
THREADDATA* p=NULL;


//variable for indexing of messages by the logging function.
int log_index=0;
int *logip = &log_index;

//The name counts.
// You can use any data structure you like, here are 2 proposals: a linked list OR an array (up to 100 names).
//The linked list will be faster since you only need to lock one node, while for the array you need to lock the whole  array.
//You can use a linked list template from A5. You should also consider using a hash table, like in A5 (even faster).
struct NAME_STRUCT{
    char name[30];
    int count;
};
typedef struct NAME_STRUCT THREAD_NAME;

//array of 100 names
THREAD_NAME names_counts[100];

//node with name_info for a linked list
struct NAME_NODE{
    THREAD_NAME name_count;
    struct NAME_NODE *next;
};
typedef struct NAME_NODE NODE;
static NODE* HEAD_NODE = NULL;

/*
 * Function that free the nodes in the list
 * Assumption: none
 * Input: head node
 * Output: none
 */
void free_nodes(NODE* head){
    //while the current node is not empty, free node
    while (head != NULL){
            NODE* temp = head->next; //assign temp node to head's next node
            free(head); //free the node itself
            head = temp; //set the head to the temp
    }
    free(head); //free the current node
}

/*
 * Prints the nodes in the list
 * Assumption: none
 * Input: head node
 * Output: none
 */
void print_nodes(NODE* head){
    //set head to HEAD
    NODE* temp = head;

    //while the next node is not empty, print the name and the count
    while(temp != NULL){
        printf("%s: %d\n", temp->name_count.name, temp->name_count.count);
        temp = temp->next;
    }
    return;
}

/*
 * Prints the date and time
 * Assumption: none
 * Input: none
 * Output: none
 */
int timer(void){
    // variables to store date and time components
    int hours, minutes, seconds, day, month, year;

    // time_t is arithmetic time type
    time_t now;

    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);

    // localtime converts a time_t value to calendar time and
    // returns a pointer to a tm structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    hours = local->tm_hour; // get hours since midnight (0-23)
    minutes = local->tm_min; // get minutes passed after the hour (0-59)
    seconds = local->tm_sec; // get seconds passed after minute (0-59)
    day = local->tm_mday; // get day of month (1 to 31)
    month = local->tm_mon + 1; // get month of year (0 to 11)
    year = local->tm_year + 1900; // get year since 1900

    // print current date
    printf(" %02d/%02d/%d ", day, month, year);

    // print local time
    if (hours < 12) // before midday
        printf("%02d:%02d:%02d am ", hours, minutes, seconds);
    else // after midday
        printf("%02d:%02d:%02d pm ", hours - 12, minutes, seconds);

    return 0;
}

/*
 * Add name to the list if it is a new name and set its count to 1
 * Assumption: none
 * Input: head node, line read from the file
 * Output: none
 */
void add_node(NODE *head, char* line){
    // make a new node
    NODE* new_node = (NODE*) malloc(sizeof(NODE));

    strcpy(new_node->name_count.name, line); //copy current line to line
    new_node->name_count.count = 1; //set count to 1

    //set new node to head
    new_node->next = NULL;

    //set new node to head if head is null
    if(head == NULL){
        head = new_node;
    }
    //else find an empty node in the list and append it to the list
    else{
        NODE* temp = head; //temp node to traverse the list

        //traverse the linked list to find empty node
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
    }

    return;
}

#define MAX_LEN 30
#define MAX_NAMES 100
/*
 * Prints the necessary messages for terminal
 * Assumption: User passes in 2 name files to run
 * Input: Name files
 * Output: name counts
 */
int main(int argc, char *argv[]){
    //If exactly 2 files are not provided, print error
    if(argc != 3){
        fprintf(stderr, "Only two files are accepted\n");
        exit(2);
    }

    HEAD_NODE = (NODE*) calloc(1, sizeof(NODE)); //allocate memory for head node

    printf("===================== Log Messages =====================\n");

    printf("create first thread\n");
    pthread_create(&tid1,NULL,thread_runner,argv[1]); //assign first file to thread 1

    printf("create second thread\n");
    pthread_create(&tid2,NULL,thread_runner,argv[2]); //assign second file to thread 2

    printf("wait for first thread to exit\n");
    pthread_join(tid1,NULL);
    printf("first thread exited\n");

    printf("wait for second thread to exit\n");
    pthread_join(tid2,NULL);
    printf("second thread exited\n");

    printf("===================== Name Counts =====================\n");
    print_nodes(HEAD_NODE->next); //HEAD_NODE is NULL so start with next node

    free_nodes(HEAD_NODE); //free the nodes

    exit(0);
}//end main

/*
 * Run threads to read the input files and count the names
 * Assumption: threads are made
 * Input: a file
 * Output: none
 */
void* thread_runner(void* file)
{
    pthread_t me;
    me = pthread_self();

    //printf("This is thread %ld (p=%p)",me,p);

    pthread_mutex_lock(&tlock2); // critical section starts

    if (p==NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
        p->creator=me;
    }

    pthread_mutex_unlock(&tlock2); // critical section ends

    pthread_mutex_lock(&tlock1); //critical section starts for log index
    if (p!=NULL && p->creator==me) {
        log_index++;

        printf("Logindex %d, thread %ld, PID %d, ", log_index, me, (int) getpid());
        timer();
        printf(": This is thread %ld and I created THREADDATA %p\n", me, p);

    } else {
        log_index++;

        printf("Logindex %d, thread %ld, PID %d, ", log_index, me, (int) getpid());
        timer();
        printf(": This is thread %ld and I can access the THREADDATA %p\n",me,p);
    }
    pthread_mutex_unlock(&tlock1); //critical section ends for log index

    FILE* names_file  = fopen((char*) file, "r"); //open file mentioned in command line

    //if file doesn't exist, print error message and exit as 1
    if (names_file == NULL){
        pthread_mutex_lock(&tlock1);
        log_index++;

        fprintf(stderr, "Logindex %d, thread %ld, PID %d ", log_index, me, (int) getpid());
        fprintf(stderr, ": Error cannot open file %s.\n", (char*) file);

        pthread_mutex_unlock(&tlock1);

        exit(1);
    }

    else {
        pthread_mutex_lock(&tlock1); //critical section starts
        log_index++;

        printf("Logindex %d, thread %ld, PID %d, ", log_index,me, (int) getpid());
        timer();
        printf(": opened file %s\n", (char*) file);

        pthread_mutex_unlock(&tlock1); //critical section ends

        //go to end of file to check if it is empty; if not empty, go back to top
        fseek(names_file, 0, SEEK_END); //go to end of file
        //if file is empty, print message and exit as 0
        if (ftell(names_file) == 0){
            printf("%s is empty!\n", (char*) file);
            exit(0);
        }
        fseek(names_file, 0, SEEK_SET); //go back to top of file

        char current_line[MAX_LEN]; //declare array to hold contents of current line in buffer
        bool name_found = 0; //0 for false; 1 for true
        int line_count = 0; // keeps track of line
        int j = 0; // names list tracker
        bool empty_line_found = 0; // tracker for empty line found

        //read file and update name array and counter array accordingly
        while (fgets(current_line, MAX_LEN, names_file) != NULL){
            NODE* curr_node = HEAD_NODE;

            //if line is empty; print warning
            if(current_line[0] == '\n' || (current_line[0] == ' ' && current_line[1] == '\n')){
                    printf("Warning - file %s line %d is empty.\n", (char*) names_file, line_count + 1);
                    empty_line_found = 1;
            }

            //convert current line to proper string
            if (current_line[strlen(current_line) - 1] == '\n'){
                    current_line[strlen(current_line) - 1] = '\0';
            }

            pthread_mutex_lock(&tlock3); // critical section starts

            int i = 0; //variable for while loop

            //check if current name is found or not
            while(i < MAX_NAMES && (curr_node = curr_node->next) != NULL){
                //compare the strings
                if(strcmp(current_line, curr_node->name_count.name) == 0){
                    curr_node->name_count.count++; //increment count
                    name_found = 1; // set name found
                }
                i++;
            }

            pthread_mutex_unlock(&tlock3); // critical section ends

            //if name is not found and line not empty, add new name in list
            if (name_found == 0 && j < 100 && empty_line_found == 0){
                    pthread_mutex_lock(&tlock3); //critical section starts

                    add_node(HEAD_NODE, current_line); //add name

                    pthread_mutex_unlock(&tlock3); //critical section ends

                    j++;
            }
            empty_line_found = 0; //reset to false
            name_found = 0; //reset boolean to false
            line_count++; //increment line
        }

        //close file
        fclose(names_file);
    }

    pthread_mutex_lock(&tlock2); //critical section starts
    if (p!=NULL && p->creator==me) {
        pthread_mutex_unlock(&tlock2); //critical section ends

        pthread_mutex_lock(&tlock1); //critical section starts
        log_index++;

        printf("Logindex %d, thread %ld, PID %d, ", log_index,me, (int) getpid());
        timer();
        printf(": This is thread %ld and I delete THREADDATA\n", me);

        pthread_mutex_unlock(&tlock1); //critical section ends

        pthread_mutex_lock(&tlock2); //critical section starts

        free((void*) p); //free p
        p = NULL; //set p to null after freeing to prevent memory leak

        pthread_mutex_unlock(&tlock2); //critical section ends

    } else {
        pthread_mutex_unlock(&tlock2); //critical section ends
        pthread_mutex_lock(&tlock1); //critical section ends
        log_index++;

        printf("Logindex %d, thread %ld, PID %d, ", log_index,me, (int) getpid());
        timer();
        printf(": This is thread %ld and I can access the THREADDATA\n", me);

        pthread_mutex_unlock(&tlock1); //critical section ends

    }
    pthread_exit(NULL);

    return NULL;
}//end thread_runner




