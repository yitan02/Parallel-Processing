/**
 * Description: This program takes input and prints it all out in reverse
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/18/23
**/

#include <stdio.h>

/**
 * This function takes input and prints it all out in reverse
 * Assumption: user enters integers
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers
   int size;  //number of integers
   int counter = 0; //counter for accepting input
   int i; //counter for iterating through array

   scanf("%d", &size);

   //take input into the array
   while(counter < size){
    scanf("%d", &userVals[counter] );
    counter++;
   }

   //print array starting from end and ending at start
   for(i = size - 1; i >= 0 ; i--){
    printf("%d,", userVals[i]);
   }

   printf("\n");
   return 0;
}
