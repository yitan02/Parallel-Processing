/**
 * Description: This program outputs values below an amount.
 * Author name: Talia Syed, Yinglin Tan
 * Author email: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/18/23
 **/

#include <stdio.h>

/**
 * This function finds values that are less than the last value and prints it.
 * Assumption: user enters integers
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   const int NUM_ELEMENTS = 20;     //constant to set how many elements the array can hold
   int userValues[NUM_ELEMENTS];    //set of data specified by the user
   int numOfElements = 0;           //variable to hold user input

   //first get the integer that indicates how many integers will follow
   scanf("%d", &numOfElements);

   //add the values after the first value into the array
   for (int a = 0; a < numOfElements + 1; a++){
      scanf("%d", &userValues[a]);
   }

   //initialize threshold value to be the last value in the array
   int threshold = userValues[numOfElements];

   //find values that are less than the threshold
   for (int b = 0; b < numOfElements + 1; b++){
      //if the value at current index in the array is less than threshold, print it
      if (userValues[b] < threshold){
         printf("%d,", userValues[b]);
      }
   }

   //print newLine
   printf("\n");

   return 0;
}
