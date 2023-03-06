/**
 * Description: This program counts the amount of unique names across multiple file.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/5/23
 * Creation date: 2/26/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NAMES 100
#define MAX_LEN 30

/**
 * Structure to hold name and count
 * assumptions: there is only a string of name, and only integer given for count
 * input: name and count
 * output: none
**/
typedef struct my_data {
  char name[MAX_LEN];
  int count;
} my_data;
my_data namecounts[100]={{{'\0', 0}}}; //declare empty struct

int namecounts_counter = 0; //counter for namecounts

/**
 * Read the names listed in a child file, update parent file, and print out the frequency of each name
 * assumptions: file has only one name per line; file only has names
 * input: file of names
 * output: list of all names and number of occurrences of each and empty line warnings
**/
int main(int argc, char *argv[]){
    int pipe1[2]; //declare pipe

    //if user passes only 1 argument, print stderror and exit as 2
    if (argc == 1) {
        fprintf(stderr, "Error! At least one file is needed\n");
        exit(2);
    }

    //spawn a child process for each file
    for(int i = 1; i < argc; i++){
        my_data temp_countnames[MAX_NAMES] = {{{'\0', 0}}}; //declare empty temp struct

        pid_t child; //declare child pid

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
        //child process
        else if (child == 0){
            //close reading end of pipe1
            close(pipe1[0]);

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
        }

        //parent process
        while(wait(NULL) > 0){
           bool temp_name_found = 0; //keeps track if name is found

           close(pipe1[1]); // close the write end of the pipe
           read(pipe1[0], temp_countnames, MAX_NAMES * sizeof(my_data)); // write the content of argv[i] to the reader

           //update namecounts struct with names found from child process
           for(int a = 0; a < MAX_NAMES && temp_countnames[a].name[0] != '\0' && namecounts_counter < MAX_NAMES ; a++){
              //find repeating names and update count
              for(int b = 0; b < MAX_NAMES; b++){
                //if name found, increment the name count accordingly in the array
                if ((strcmp (temp_countnames[a].name, namecounts[b].name) == 0) ){
                    namecounts[b].count += temp_countnames[a].count;
                    temp_name_found = 1;
                }
              }
              //if name is not found, add new name to struct
              if (temp_name_found == 0){
                    strcpy(namecounts[namecounts_counter].name, temp_countnames[a].name);
                    namecounts[namecounts_counter].count = temp_countnames[a].count;
                    namecounts_counter++;
              }
              temp_name_found = 0; //reset boolean to false
            }
        }
        close(pipe1[0]); //close read end of pipe
    }

    //print the names found and their frequency
    for(int z = 0; z < MAX_NAMES && namecounts[z].name[0] != '\0'; z++){
        printf("%s: %d\n", namecounts[z].name, namecounts[z].count);
    }

    //exit as 0
    exit(0);
}
