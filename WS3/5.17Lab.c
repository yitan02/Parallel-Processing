/**
 * Description: This program takes in a sorted list and returns the middle number
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/18/23
**/

#include <stdio.h>

/**
 * This program takes in a sorted list and returns the middle number.
 * Assumption: user enters integers
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   const int NUM_ELEMENTS = 9;      //fixed size for array
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int counter = 0;  //keep track of array size
   int temp = 0;  //temporarily hold scaanned input
   int neg_check = 0; // 0 for false, 1 for true

  //scan in all values into array
  while (neg_check == 0){
      scanf("%d", &temp);
      //if input is positive, enter into next spot in array
      if (temp > 0 ) {
         userValues[counter] = temp;
          counter++;
      }
      //if input is negtive, exit loop
      else{
         neg_check = 1;
      }
  }

   //if array has 9 or less values, print middle array value
   if (counter <= 9) {
      counter = counter / 2;
      printf("Middle item: %d\n", userValues[counter]);
   }
   //if array exceeds 9 values, print error message
   else {
      printf("Too many numbers\n");
   }

   return 0;
}
