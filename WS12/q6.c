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
 * 6. Create a program "q6.c" that allocates an array of integers (as above), frees them, and then tries to print the
 * value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?
 *      The program compiled without problem and printed out random value. Valgrind shows that all heap blocks are
 * freed but there's an error of invalid read size of 4.
 *
 */

/**
 * Main function creates an array of int, frees it, and print one of the elements.
 * Assumptions: n/a
 * Input parameters: n/a
 * Returns: int
**/
int main(){
    int *data = (int*) malloc(100 * sizeof(int)); //array of int of size 100
    free(data); //free array
    printf("%d\n", data[6]); //print one of the elements


    return 0;
}
