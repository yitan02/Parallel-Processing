#include <stdio.h>
#include <stdlib.h>

/**
 * count function
 * assumptions: file has only one name per line; file only has names
 * input: file of names
 * output: list of all names and number of occurrences of each
 * how to take in file in input
**/

//int name_count(){}
int main(int argc, char *argv[])
{
    //if user passes either only 1 argument or more than 2 arguments, print stderror and exit as 2
    if (argc == 1 || argc > 2) {
        fprintf(stderr, "Error, enter one file name.\n");
        exit(2);
    }

    //open file
    FILE* names_file  = fopen("names.txt", "r");

    //if file doesn't exist, print error message and exit as 1
    if (names_file == NULL)
    {
        printf("Error, file not found!\n");
        exit(1);
    }

    //backup for checking if file is empty
   /**
    * int c = fgetc(fp);
    * if (c == EOF) {
    * // file empty, error handling
    * } else {
    *  ungetc(c, fp);}
    **/


    //go to end of file to check if it is empty; if not empty, go back to top
    if (names_file != NULL) {
        fseek (names_file, 0, SEEK_END); //go to end of file

        //if file is empty, print message and exit as 0
        if (ftell(names_file) == 0){
            printf("File is empty!\n");
            exit(0);
        }

        fseek(names_file, 0, SEEK_SET); //go back to top of file
    }


    char names[100][30]; //declare array to hold names
    int name_count[100]; //declare array to hold count of names
    int empty_line_tracker[100]; //declare array to track empty lines
    char current_line[30]; //declare array to hold contents of current line in buffer
    size_t count = 0; // counter for line
    char temp[30]; //temporary array too hold current name


   // int i = 0; // tracker for current line number

    //read file and update name array and counter array accordingly
    while (fgets(current_line, sizeof current_line, name_file) != NULL ){

        bool name_found = 0; // 0 for name not found; 1 for name found

          //case 0: if line is empty, update line counter array
          if(current_line[0] == '\n' || (current_line[0] == ' ' && current_line[1] == '\n')){
            empty_line_tracker[count] = 1;
            continue;
          }

          //case1: name found in array
          //read current name into temp array
          for (int i = 0; i < 30 ; i++) {
              sscanf(current_line, "%c", &temp[count][i]);
          }

          //compare current name with names already in the array
          while(!(names_count[i] == 0 && empty_line_tracker[i] == 0)) {
              int name_check_counter = 0; //counter for comparison of names
              int k = 0 ; //tracker for names_count names

            //
            for (int i = 0; i < 30; i++){
                //
                if(names[count][i] == temp[i]) {
                    name_check_counter++;
                }
            }
            //if name is found, increment name counter array
            if(name_check_counter == 30){
                names_count[count]++;
                name_found = 1;
            }
          }

          //case 2: if current name is not in name array or if array is empty, add to next spot in name array
          if( name_found == 0) {
            //add name into next open spot
            for (int i = 0; i < 30 ; i++){
              sscanf(current_line, "%c", &name[count][i]);
            }
            names_count[count]++; //increment name count
          }

          count++;
    }

    int j = 0; //counter for names and empty line tracker

    //read the arrays and display the names and their count while both names and empty line array are not empty
    while(!(names_count[j] == 0 && empty_line_tracker[j] == 0)){
        // if line was not empty and had a name, print name and count
        if(names_count[j] != 0 && empty_line_tracker[j] == 0){
            //only print out until end of name from name array!!!!
            printf( "%s: %d \n", names[j] , names_count[j]);
        }
        // if line is empty, print message to stderror
        else if (names_count[j] == 0 && empty_line_tracker[j] != 0) {
            fprintf(stderr, "Warning - Line %d is empty!\n", empty_line_tracker[j]);
        }
        j++;
    }

    //close file
    fclose(fp);

    //exit as 0
    exit(0);
}
