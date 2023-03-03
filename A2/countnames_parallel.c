/**
 * Description: This program counts the amount of unique names across multiple file.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/2/23
 * Creation date: 2/26/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Checklist:
 * fix all compiler erors
 * figure out how to transfer array data from each individual child into total
 * figure out how pipes work
 * how to access struct array?
 * how to keep track of empty lines in a file
 */

/**
 * Read the names listed in a child file, update parent file, and print out the frequency of each name
 * assumptions: file has only one name per line; file only has names
 * input: file of names
 * output: list of all names and number of occurrences of each and empty line warnings
**/
#define MAX_NAMES 100
typedef struct my_data {
  char name[30];
  int count;
} my_data;


int main(int argc, char *argv[])
{
    //declare total namecounts
    my_data namecounts[100]={{{'\0', 0}}};

    //if user passes only 1 argument, print stderror and exit as 2
    if (argc == 1) {
        fprintf(stderr, "Error! At least one file is needed\n");
        exit(2);
    }


    //spawn a child process for each file
    for(int i = 0; i < argc; i++)
    {
        // argv[i] is the argument at index i
        int pipe1[2];
        int pipe2[2];
        pid_t child;

        //checks if pipes failed to initialize
        if ((pipe(pipe1) == -1) || (pipe(pipe2) == -1)){
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
            //close writing end of pipe1
            close(pipe1[1]);

            // read while EOF
//             while (read(pipe1[0], &buf, 1) > 0){
//                 write(1, &buf, 1);
//             }
//             write(1, "\n", 1);

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

            char names[MAX_NAMES][30] = {0}; //declare array to hold names
            int names_count[MAX_NAMES] = {}; //declare array to hold count of names and initialize each cell as 0
            int empty_line_tracker[MAX_NAMES] = {}; //declare array to track empty lines and initialize each cell as 0
            char current_line[30]; //declare array to hold contents of current line in buffer
            bool name_found = 0; //0 for false; 1 for true
            int line_count = 0; // keeps track of line
            int j = 0; // names array tracker

            //read file and update name array and counter array accordingly
            while (fgets(current_line, 30, names_file) != NULL){
                //check if current name is found or not
                for (int i = 0; i < MAX_NAMES; i++){
                    //case 1: name found
                    //if name found, increment the name count accordingly in the array
                    if (strcmp (current_line, names[i]) == 0){
                        names_count[i]++;
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
                        strcpy(names[j], current_line);
                        names_count[j]++;
                        j++;
                    }
                }
                name_found = 0; //reset boolean to false
                line_count++; //increment line
            }

            //print out the warnings for empty lines in the file
            for (int i = 0; i < MAX_NAMES; i++){
                //prints only if the value of the element in the empty_line_tracker array is not 0
                if (empty_line_tracker[i] != 0){
                    fprintf(stderr, "Warning - Line %d is empty.\n", i + 1);
                }
            }

            //close file
            fclose(names_file);

            //close reading ends of the pipes
            close(pipe1[0]);
            close(pipe2[0]);

            exit(0);
        }
        //figure out how to copy data from child to parent

        else{ /* parent process */
           my_data temp_namecounts[MAX_NAMES]={0};

           close(pipe1[0]); // close the read-end of the pipe
           write(pipe1[1], namecounts, MAX_NAMES*sizeof(my_data)); // write the content of argv[1] to the reader
           close(pipe1[1]); // close the write-end of the pipe
           wait(NULL); // wait for the child process to exit
           close(pipe2[1]);
           read(pipe2[0], &temp_namecounts, MAX_NAMES*sizeof(my_data));
           //add occurrences of names to total count
           close(pipe2[0]);
           exit(0);
        }


    }
    int k = 0; //counter for names and empty line tracker
    //read the arrays and display the names and their count while both names and empty line array are not empty
    while(k < MAX_NAMES){
        // if line was not empty and had a name, print name and count
            if(namecounts[k].count != 0){
                int n = 0; //variable to print the names
                //print out the name character by character
                    while(namecounts[k].name[n] != '\n'){
                        printf("%c", namecounts[k].name[n]);
                        n++;
                    }
                //print the occurences of the name
                printf(": %d\n", namecounts[k].count);
                }
                k++;
    }
    //exit as 0
    exit(0);
}
