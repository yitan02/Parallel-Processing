#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Read the names listed in a file and print out the frequency of each name
 * assumptions: file has only one name per line; file only has names
 * input: file of names
 * output: list of all names and number of occurrences of each
**/

//int name_count(){}
int main(int argc, char *argv[])
{
    //if user passes either only 1 argument or more than 2 arguments, print stderror and exit as 2
    if (argc == 1 || argc > 2) {
        fprintf(stderr, "Error! Expected Format: ./abc <filename> \n");
        exit(2);
    }

    FILE* names_file  = fopen(argv[1], "r"); //open file mentioned in command line

    //if file doesn't exist, print error message and exit as 1
    if (names_file == NULL){
        printf("Error, file not found!\n");
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

    char names[100][30] = {0}; //declare array to hold names
    int names_count[100] = {}; //declare array to hold count of names and initialize each cell as 0
    int empty_line_tracker[100] = {}; //declare array to track empty lines and initialize each cell as 0
    char current_line[30]; //declare array to hold contents of current line in buffer
    bool name_found = 0; //0 for false; 1 for true
    int line_count = 0; // keeps track of line
    int j = 0; // names array tracker

    //read file and update name array and counter array accordingly
    while (fgets(current_line, 30, names_file) != NULL && line_count <= 99){
        //check if current name is found or not
        for (int i = 0; i < 100; i++){
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
                empty_line_tracker[line_count] = 1;
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

    int k = 0; //counter for names and empty line tracker

    //read the arrays and display the names and their count while both names and empty line array are not empty
    while(k < 100){
        // if line was not empty and had a name, print name and count
       if(names_count[k] != 0){
            //print out name
           int n = 0;
           while(names[k][n] != '\n'){
               printf("%c", names[k][n]);
               n++;
           }
           printf(": %d\n", names_count[k]);
       }
//        if (empty_line_tracker[k] != 0){
//            fprintf(stderr, "Warning - Line %d is empty.\n", k + 1);
//        }
       k++;
    }

    for (int i = 0; i < 100; i++){
      if (empty_line_tracker[i] != 0){
           fprintf(stderr, "Warning - Line %d is empty.\n", i + 1);
       }
    }

    //close file
    fclose(names_file);

    //exit as 0
    exit(0);
}
