/**
 * Description: This program finds integer elements in a range.
 * Author name: Talia Syed, Yinglin Tan
 * Author email: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/18/23
 **/

#include <stdio.h>

/**
 * This function determines the integers in a list that is in the range indicated.
 * Assumption: user enters integers.
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   int lowerBound;    //holds lower bound value
   int upperBound;    //holds upper bound value
   int list[20];      //array to hold list of integers
   int numInt;        //variable to hold the amount of integers

   //first scan the integer indicating the number of integers that follow
   scanf("%d", &numInt);

   //scan the following integers in the array
   for (int i = 0; i < numInt; i++){
      scanf("%d", &list[i]);
   }

   //get the lower bound and upper bound
   scanf("%d", &lowerBound);
   scanf("%d", &upperBound);

   //prints the numbers that are in the range of lower and upper bound
   for (int j = 0; j < numInt; j++){
       //checks if the number is in the range
      if (list[j] >= lowerBound && list[j] <= upperBound){
         printf("%d,", list[j]);
      }
   }

   //print newLine
   printf("\n");

   return 0;
}
