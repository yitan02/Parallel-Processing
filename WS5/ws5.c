/**
 * Description: Program to use fork to print out statement 4 times.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/2/23
 * Creation date: 3/2/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Use fork to print the current PIDs 4 times.
 * Assumption: none
 * Input: void
 * Return: int
 **/
int main(void){
    pid_t child; //initialize pid

    //fork two times using for loop
    for(int i = 0; i < 2; i++){
        child = fork();

        //check if fork did not work
        if (child < 0){
            //exit if child PID is less than 0.
            fprintf(stderr, "fork failed\n");
            exit(1);
        }

        //child process
        else if (child == 0){
            printf("hello world from PID %d!\n", (int) getpid());
            exit(0);
        }
        //parent process
        else{
            wait(NULL);
            printf("hello world from PID %d!\n", (int) getpid());
        }
    }

    exit(0);
}
