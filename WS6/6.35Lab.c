/**
 * Description: This program sorts an array.
 * Author name: Talia Syed, Yinglin Tan
 * Author email: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/5/23
 * Creation date: 3/5/23
 **/
#include <stdio.h>

/**
 * This function sorts the array in descending order using bubble sort.
 * Assumption: list contains integers
 * Input parameters: list of integers and a integer for number of values
 * Returns: void
**/
void SortArray(int sortingList[], int numVals){
   int temp; //variable for swapping

   //bubble sort the array in descending order
   for(int j = 0; j < numVals; j++){
      for(int k = 0; k < numVals - 1; k++){
         //swap elements if the next element is greater than current element
         if(sortingList[k+1] > sortingList[k]){
            temp = sortingList[k];
            sortingList[k] = sortingList[k+1];
            sortingList[k + 1] = temp;

         }
      }
   }

   //loop through the sorted list and print it
   for(int m = 0; m < numVals; m++){
     printf("%d,", sortingList[m]);
   }

   //newline
   printf("\n");
}

/**
 * Main function gets user input and calls SortArray function.
 * Assumption: user enters an integer indicating how many elements followed by the correct amount of integers.
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   int count; //variable to hold number of elements
   int list[20]; //empty list that holds less than 20 numbers

   //first get how many elements there will be
   scanf("%d", &count);

   //read the following integers into the list
   for(int i = 0; i < count; i++){
      scanf("%d", &list[i]);
   }

   //call SortArray function
   SortArray(list, count);

   return 0;
}
