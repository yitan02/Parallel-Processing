/**
 * Description: This program counts the amount of unique names across multiple file.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/4/23
 * Creation date: 2/26/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Read the names listed in a child file, update parent file, and print out the frequency of each name
 * assumptions: file has only one name per line; file only has names
 * input: file of names
 * output: list of all names and number of occurrences of each and empty line warnings
**/
#define MAX_NAMES 100
#define MAX_LEN 30
typedef struct my_data {
  char name[30];
  int count;
} my_data;
my_data namecounts[100]={{{'\0', 0}}};
my_data temp_countnames[MAX_NAMES] = {{{'\0', 0}}};

int namecounts_counter = 0;

int main(int argc, char *argv[])
{
//     char name[MAX_NAMES[MAX_LEN];
//     int count[MAX_NAMES];

    //declare total namecounts
    //my_data namecounts[100]={{{'\0', 0}}};

    int pipe1[2]; //declare pipe
    //int pipe2[2];

    //if user passes only 1 argument, print stderror and exit as 2
    if (argc == 1) {
        fprintf(stderr, "Error! At least one file is needed\n");
        exit(2);
    }


    //spawn a child process for each file
    for(int i = 1; i < argc; i++)
    {
        // argv[i] is the argument at index i
        pid_t child;

        //checks if pipes failed to initialize
        if (pipe(pipe1) == -1){
             fprintf(stderr, "Pipe failed to initialize");
             exit(1);
        }

        //create child process
        child = fork();

        //exit if child process did not spawn
        if (child < 0){
          fprintf(stderr, "Fork failed");
          exit(1);
        }
        else if (child == 0){
            //close reading end of pipe1
            close(pipe1[0]);
            //close(pipe2[1]);

            //my_data child_namescount[MAX_NAMES] = {{{'\0', 0 }}};

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

            //char names[MAX_NAMES][MAX_LEN] = {0}; //declare array to hold names
            //int names_count[MAX_NAMES] = {}; //declare array to hold count of names and initialize each cell as 0
            //int empty_line_tracker[MAX_NAMES] = {}; //declare array to track empty lines and initialize each cell as 0
            char current_line[MAX_LEN]; //declare array to hold contents of current line in buffer
            bool name_found = 0; //0 for false; 1 for true
            int line_count = 0; // keeps track of line
            int j = 0; // names array tracker

            //read file and update name array and counter array accordingly
            while (fgets(current_line, MAX_LEN, names_file) != NULL){


                //check if current name is found or not
                for (int i = 0; i < MAX_NAMES; i++){
                    //case 1: name found
                    //if name found, increment the name count accordingly in the array
                    if (strcmp (current_line, temp_countnames[i].name) == 0){
                        temp_countnames[i].count++;
                        name_found = 1;
                    }
                }

                //if name is not found, either line is empty or has a new name
                if (name_found == 0){
                //case 1: line is empty; if line is empty, update line counter array
                    if(current_line[0] == '\n' || (current_line[0] == ' ' && current_line[1] == '\n')){
                        //empty_line_tracker[line_count] = 1;

                        printf("Warning -file %s line %d is empty.\n", argv[i], line_count + 1);
                    }
                // case 2 : name is not in array yet, so add into next empty spot in names array
                    else{
                        //replace newLine with null
                        if(current_line[strlen(current_line) - 1] == '\n'){
                            current_line[strlen(current_line) - 1] = '\0';
                        }
                        strcpy(temp_countnames[j].name, current_line);
                        temp_countnames[j].count++;
                        j++;
                    }
                }
                name_found = 0; //reset boolean to false
                line_count++; //increment line
            }

            //close file
            fclose(names_file);

            //write the names and names_count array to the pipe
            if(write(pipe1[1], temp_countnames, MAX_NAMES * sizeof(my_data)) < 0){
                fprintf(stderr, "failed to write names to pipe\n");
            }

//             if(write(pipe1[1], child_namescount.count, MAX_LEN) < 0){
//                 fprintf(stderr, "failed to write names_count to pipe\n");
//             }

            //close writing end
            close(pipe1[1]);
            //close(pipe2[1]);

            exit(0);
        }


    /* parent process */
    while(wait(NULL) > 0){
//            char temp_name[MAX_NAMES][MAX_LEN] = {0};
//            int temp_count[MAX_LEN] = {};
           bool temp_name_found = 0;

           close(pipe1[1]); // close the write-end of the pipe
           //close(pipe2[1]);
           read(pipe1[0], temp_countnames, MAX_NAMES * sizeof(my_data)); // write the content of argv[i] to the reader
           //read(pipe2[0], temp_count, MAX_LEN); // write to temp_count

           for(int a = 0; a < MAX_NAMES && temp_countnames[a].name[0] != '\0'; a++){
              for(int b = 0; b < MAX_NAMES; b++){

                //case 1: name found
                //if name found, increment the name count accordingly in the array
                if ((strcmp (temp_countnames[a].name, namecounts[b].name) == 0) && (namecounts[b].name[0] != '\0') && (temp_countnames[a].name[0] != '\0')){
                    namecounts[b].count++;
                    temp_name_found = 1;

                }
              }
              //if name is not found, either line is empty or has a new name
              if (temp_name_found == 0){
                // case 1 : name is not in array yet, so add into next empty spot in names array
                    strcpy(namecounts[namecounts_counter].name, temp_countnames[a].name);
                    namecounts[namecounts_counter].count++;
                    namecounts_counter++;
              }
              temp_name_found = 0; //reset boolean to false
            }

           close(pipe1[0]);
           //close(pipe2[0]);
        }

    }

    for(int z = 0; z < MAX_NAMES && namecounts[z].name[0] != '\0'; z++){
        printf("%s : %d\n", namecounts[z].name, namecounts[z].count);

    }

    //printf("%s and %d \n", namecounts[2].name, namecounts[2].count);

     //int k = 0; //counter for names and empty line tracker
    //read the arrays and display the names and their count while both names and empty line array are not empty
//     while(k < MAX_NAMES && namecounts[k].count != 0){
//         int d = 0; //variable to print the names
//         //print out the name character by character
//         while(namecounts[k].name[d] != '\n'){
//             printf("%c", namecounts[k].name[d]);
//             d++;
//         }
//         //print the occurences of the name
//         printf(": %d\n", namecounts[k].count);
//         k++;
//     }

    //exit as 0
    exit(0);
}
