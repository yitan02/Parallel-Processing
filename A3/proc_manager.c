/**
 * Description: This program executes multiple commands.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/10/23
 * Creation date: 3/10/23
 **/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_LEN 30


int main(int argc, char *argv[]){
    //If user does not give exactly 1 input, print warning and exit as 2
    if (argc != 2){
        printf("One input is needed.\n");
        exit(2);
    }

    //declare file pointer
    File* cmd_fp = fopen(argv[1], "r");

    //if file doesn't exist, print error message and exit as 1
    if (cmd_fp == NULL){
        printf("Error: cannot open file.\n");
        exit(1);
    }

    //go to end of file to check if it is empty; if not empty, go back to top
    if (cmd_fp != NULL) {
        fseek(cmd_fp, 0, SEEK_END); //go to end of file
        //if file is empty, print message and exit as 0
        if (ftell(cmd_fp) == 0){
            printf("File is empty!\n");
            exit(0);
        }
        fseek(cmd_fp, 0, SEEK_SET); //go back to top of file
    }

    char commands[MAX_CHAR][MAX_LEN]; //array to store commands
    char current_line[MAX_LEN]; //array to store current line read
    int line_count = 0; //counter for line count


    while(fgets(current_line, MAX_LEN, cmd_fp) != NULL){
        pid_t child; //declare child pid

        child = fork();

        //exit if child process did not spawn
        if(child < 0){
            fprintf(stderr, "Fork failed");
            exit(1);
        }
        //child process
        else if (child == 0){
            char output_file[30]; // array to hold stdout
            char error_file[30]; // array to hold stderr

            //push the logs to their respective files
            sprintf(output_file, "%d.out", (int) getpid());
            sprintf(error_file, "%d.err", (int) getpid());

            //open log files
            int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            //send fd_1 to PID.out file and fd_2 to PID.err for the PID
            dup2(fd_1, 1);
            dup2(fd_2, 2);

            execvp();
        }

        while((child = wait(&status)) > 0){
            char output_file[30]; // array to hold stdout
            char error_file[30]; // array to hold stderr

            //push the logs to their respective files
            sprintf(output_file, "%d.out", (int) getpid());
            sprintf(error_file, "%d.err", (int) getpid());

            //open log files
            int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            fprintf(stdout, "Finished child %d pid of parent %d\n", child, (int) getpid());
            //fflush(stdout);

            //if process exited normally
            if (WIFEXITED(status)) {
                fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
            }
            //if process killed
            else if (WIFSIGNALED(status)) {
                fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
            }

            //send fd_1 to PID.out file and fd_2 to PID.err for the PID
            dup2(fd_1, 1);
            dup2(fd_2, 2);
        }
    }



    //notes:
    //call execvp in child process
    //push results to output file and errors to error file
    //figure out what to do in parent process
    //how many parent processes are needed?
    //should we read in the entire input into array and then call child processes
    //or should we go line by line and call child processes for every line?
    //should we go line by line after while or inside the while?


    return 0;
}
