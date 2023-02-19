/**
 * Description: This program finds the two smallest numbers.
 * Author name: Talia Syed, Yinglin Tan
 * Author email: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/18/23
 **/

#include <stdio.h>

/**
 * This function determines the two smallest numbers in a list inputted by the user.
 * Assumption: user enters integers.
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   int numInt;      //variable to hold the number of integers
   int list[20];    //array for list of integers
   int temp;        //used for swapping elements

   //first get the value that determines how many integers will be in the list
   scanf("%d", &numInt);

   //read the following integers into the array
   for(int i = 0; i < numInt; i++){
      scanf("%d", &list[i]);
   }

   //bubble sort the array in ascending order
   for (int m = 0; m < numInt; m++){
      for (int j = 0; j < numInt - 1; j++){
         //swap the elements if the next element is less than the current element
         if(list[j+1] < list[j]){
            temp = list[j];
            list[j] = list[j+1];
            list[j+1] = temp;
         }
      }
   }

   //print the smallest two integers
   printf("%d and %d\n", list[0], list[1]);

   return 0;
}
