/**
 * Description: Program for allocating memory without freeing
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/22/23
 * Creation date: 4/22/23
**/

#include <stdio.h>
#include <stdlib.h>

/**
 * 4. Write a simple program "q4.c" that allocates memory using malloc() but forgets to free it before exiting.
 * What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (with the
 * --leak-check=yes flag)?
 *
 *      The program compiles but would have a memory leak because the allocated memory is not freed after using it.
 * Valgrind also indicates that there is a memory leak in the leak summary.
 */

/**
 * Main function allocates memory but forgets to free before exiting
 * Assumptions: n/a
 * Input parameters: n/a
 * Returns: int
**/
int main(){
    int *ptr = (int*) malloc(sizeof(int));
    *ptr = 1;

    return 0;
}

