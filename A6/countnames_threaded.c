/**
 * Description: This program executes count names with threads
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 5/6/23
 * Creation date: 5/6/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

//thread mutex lock for access to the log index
//TODO you need to use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for critical sections of allocating THREADDATA
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for access to the name counts data structure
//TODO you need to use this mutexlock for mutual exclusion
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
int logindex=0;
int *logip = &logindex;

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

void free_nodes(NODE* head){

    //while the current node is not empty, free node
    while (head != NULL){
            NODE* temp = head->next; //assign temp node to head's next node
            free(head->line); //free the line
            free(head); //free the node itself
            head = temp; //set the head to the temp
    }
    free(head); //free the current node
}

void print_nodes(NODE* head){
    //set head to HEAD
    head = HEAD;

    //if the next node is not empty, print the index and the line
    //recursively call the function to continue printing
    if(head->next != NULL){
        printf("%s: %d\n", head->name_count.name, head->name_count.count);
        print_nodes(head->next);
    }
    return;
}

// Print current date and time in C
int timer(void){
    // variables to store date and time components
    int hours, minutes, seconds, day, month, year;

    // time_t is arithmetic time type
    time_t now;

    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);

    // Convert to local time format and print to stdout
    printf("Today is : %s", ctime(&now));

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

    // print local time
    if (hours < 12) // before midday
        printf("Time is : %02d:%02d:%02d am\n", hours, minutes, seconds);
    else // after midday
        printf("Time is : %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);

    // print current date
    printf("Date is : %02d/%02d/%d\n", day, month, year);

    return 0;
}

/*********************************************************
// function main
*********************************************************/
int main(){

    //TODO similar interface as A2: give as command-line arguments three filenames of numbers (the numbers in the files are newline-separated).
    printf("create first thread");
    pthread_create(&tid1,NULL,thread_runner,NULL);

    printf("create second thread");
    pthread_create(&tid2,NULL,thread_runner,NULL);

    printf("wait for first thread to exit");
    pthread_join(tid1,NULL);
    printf("first thread exited");

    printf("wait for second thread to exit");
    pthread_join(tid2,NULL);
    printf("second thread exited");

    print_nodes(HEAD_NODE);

    //TODO print out the sum variable with the sum of all the numbers

    FILE* names_file  = fopen(argv[i], "r"); //open file mentioned in command line

    //if file doesn't exist, print error message and exit as 1
    if (names_file == NULL){
        printf("Error: cannot open file.\n");
        exit(1);
    }

    //go to end of file to check if it is empty; if not empty, go back to top
    if (names_file != NULL) {
        fseek(names_file, 0, SEEK_END); //go to end of file
        //if file is empty, print message and exit as 0
        if (ftell(names_file) == 0){
            printf("File is empty!\n");
            exit(0);
        }
        fseek(names_file, 0, SEEK_SET); //go back to top of file
    }

    char current_line[MAX_LEN]; //declare array to hold contents of current line in buffer
    bool name_found = 0; //0 for false; 1 for true
    int line_count = 0; // keeps track of line
    int j = 0; // names array tracker
    bool empty_line_found = 0; // tracker for empty line found

    //read file and update name array and counter array accordingly
    while (fgets(current_line, MAX_LEN, names_file) != NULL){
            //if line is empty; print warning
            if(current_line[0] == '\n' || (current_line[0] == ' ' && current_line[1] == '\n')){
                    printf("Warning - file %s line %d is empty.\n", argv[i], line_count + 1);
                    empty_line_found = 1;
            }

            //convert current line to proper string
            if (current_line[strlen(current_line) - 1] == '\n'){
                    current_line[strlen(current_line) - 1] = '\0';
            }

            //check if current name is found or not
            for (int i = 0; i < MAX_NAMES; i++){
                //if name found, increment the name count accordingly in the array
                if (strcmp (current_line, temp_countnames[i].name) == 0 && empty_line_found == 0){
                    temp_countnames[i].count++;
                    name_found = 1;
                }
            }

            //if name is not found and line not empty, add new name in array
            if (name_found == 0 && j < 100 && empty_line_found == 0){
                    strcpy(temp_countnames[j].name, current_line);
                    temp_countnames[j].count++;
                    j++;
            }
            empty_line_found = 0; //reset to false
            name_found = 0; //reset boolean to false
            line_count++; //increment line
    }

        //close file
        fclose(names_file);

        //write the names and names_count array to the pipe
        if(write(pipe1[1], temp_countnames, MAX_NAMES * sizeof(my_data)) < 0){
            fprintf(stderr, "failed to write names to pipe\n");
        }

        //close writing end of pipe
        close(pipe1[1]);

    exit(0);
}//end main
/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void* thread_runner(void* x)
{
    pthread_t me;
    me = pthread_self();

    printf("This is thread %ld (p=%p)",me,p);

    pthread_mutex_lock(&tlock2); // critical section starts

    if (p==NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
        p->creator=me;
    }

    pthread_mutex_unlock(&tlock2); // critical section ends

    if (p!=NULL && p->creator==me) {
        printf("This is thread %ld and I created THREADDATA %p",me,p);

    } else {
        printf("This is thread %ld and I can access the THREADDATA %p",me,p);
    }

    /**
    * //TODO implement any thread name counting functionality you need.
    * Assign one file per thread. Hint: you can either pass each argv filename as a thread_runner argument from main.
    * Or use the logindex to index argv, since every thread will increment the logindex anyway
    * when it opens a file to print a log message (e.g. logindex could also index argv)....
    * //Make sure to use any mutex locks appropriately
    */

    // TODO use mutex to make this a start of a critical section
    pthread_mutex_lock(&tlock3); // critical section starts

    if (p!=NULL && p->creator==me) {
        printf("This is thread %ld and I delete THREADDATA",me);
    /**
    * TODO Free the THREADATA object.
    * Freeing should be done by the same thread that created it.
    * See how the THREADDATA was created for an example of how this is done.
    */
    } else {
        printf("This is thread %ld and I can access the THREADDATA",me);
    }

    // TODO critical section ends
    pthread_mutex_unlock(&tlock3);

    pthread_exit(NULL);

    //return NULL;
}//end thread_runner




