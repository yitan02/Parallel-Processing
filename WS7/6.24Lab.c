/**
 * Description: This program swaps variables.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/12/23
 * Creation date: 3/12/23
 **/
#include <stdio.h>

/**
 * Swaps first value with second value and third value with the fourth value
 * Assumptions: user inputs 4 integers
 * Input: 4 integer pointers
 * Output: void
 **/
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4){
  int temp;

  //swap first value with second value
  temp = *userVal1;
  *userVal1 = *userVal2;
  *userVal2 = temp;

  //swap third value with fourth value
  temp = *userVal3;
  *userVal3 = *userVal4;
  *userVal4 = temp;
}

/**
 * Get user inputs and call SwapValues function
 * Assumptions: user inputs 4 integers
 * Input: void
 * Output: int
 **/
int main(void) {
   //initialize and scan to each respective variables
   int num1;
   scanf("%d", &num1);
   int num2;
   scanf("%d", &num2);
   int num3 = 0;
   scanf("%d", &num3);
   int num4 = 0;
   scanf("%d", &num4);

   //call swap function
   SwapValues(&num1, &num2, &num3, &num4);

   //print result
   printf("%d %d %d %d\n", num1, num2, num3, num4);

   return 0;
}
