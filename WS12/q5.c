/**
 * Description: Program that creates an array of integers
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/23/23
 * Creation date: 4/23/23
**/

#include <stdio.h>
#include <stdlib.h>

/**
 * 5. Write a program "q5.c" that creates an array of integers called data of size 100 using malloc; then,
 * set data[100] to zero. What happens when you run this program? What happens when you run this program using
 * valgrind? Is the program correct?
 *      The program compiles without problem and nothing happened when we ran it. When running the program with valgrind,
 * valgrind shows that there's a memory leak of 400 bytes. Overall, the program is incorrect. By assigning zero to
 * data[100], we are overwriting whatever it was in that memory location and was not part of the memory allocated for data
 * array.
 *
 */

/**
 * Main function creates an array of int, allocate memory, and set index 100 to zero.
 * Assumptions: n/a
 * Input parameters: n/a
 * Returns: int
**/
int main(){
    int *data = (int*) malloc(100 * sizeof(int)); //array of int of size 100
    data[100] = 0;


    return 0;
}
