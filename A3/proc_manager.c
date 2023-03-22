/**
 * Description: This program executes multiple commands.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/22/23
 * Creation date: 3/10/23
 **/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_CHAR 100
#define MAX_LEN 30

/**
 * Read from stdin and run the commands in parallel
 * assumptions: there is at least one line of command
 * input: commands
 * output: command results in output and error file
**/
int main(int argc, char *argv[]){

    int status; //declare status
    pid_t child; //declare child pid

    char current_line[MAX_LEN]; //array to store current line read
    int line_count = 0; //counter for line count
    int cmd_count = 0; //counter for the amount of commands

    //while loop reads from stdin/terminal input
    while(fgets(current_line, MAX_LEN, stdin) && line_count < MAX_CHAR){
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
        else if (child == 0){
            //split current line into parts by words
            char *argument[MAX_LEN + 1] = {0};
            char *word = strtok(current_line, " ");
            int counter = 0;

            //separate each word based on space
            while(word != NULL && counter < MAX_LEN - 1){
                argument[counter] = word;
                counter++;
                word = strtok(NULL, " ");
            }
            argument[counter++] = NULL; //set end of array to NULL

            char output_file[MAX_LEN]; // array to hold stdout
            char error_file[MAX_LEN]; // array to hold stderr

            //push the logs to their respective files
            sprintf(output_file, "%d.out", (int) getpid());
            sprintf(error_file, "%d.err", (int) getpid());

            //open log files
            int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            //send fd_1 to PID.out file and fd_2 to PID.err for the PID
            dup2(fd_1, 1);
            dup2(fd_2, 2);

            fprintf(stdout,"Starting command %d: child %d pid of parent %d\n", cmd_count, getpid(), getppid());

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
        char error_file[MAX_LEN] = {0}; // array to hold stderr

        //push the logs to their respective files
        sprintf(output_file, "%d.out", child);
        sprintf(error_file, "%d.err", child);

        //open output file and send fd_1 to PID.out file
        int fd_1 = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fd_1, 1);

        fflush(stdout); //clear output buffer

        //open err file and send fd_2 to PID.err file
        int fd_2 = open(error_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fd_2, 2);

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

    line_count++; //increase line count

    return 0;
}
