/**
 * Description: Program to convert a positive integer to its reverse binary
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/16/23
 **/

#include <stdio.h>

/**
 * Method to convert a positive integer to a reverse binary
 * Assumptions: the user inputs an integer who's binary value will not exceed the array limit
 * Input parameters: void
 * Returns: int
**/
int main(void) {

   int num;  // input value
   int binary_arr[10]; // array to hold binary value of input
   int i, j; // counters for iterating the binary array

   scanf("%d", &num);

   //divide the integer by two until it reaches 0
   for(i = 0; num > 0; i++){
      binary_arr[i] = num%2;
      num = num / 2;
   }

   //for reverse, print the binary from the beginnign of the array
   for(j = 0; j < i; j++){
      printf("%d", binary_arr[j]);
   }
   printf("\n");

   return 0;
}
