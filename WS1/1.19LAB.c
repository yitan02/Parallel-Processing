/**
 * Description: This lab is an exercise on performing mathematical operations based on input values.
 * Author name: Yinglin Tan
 * Author email: yinglin.tan@sjsu.edu
 * Last modified date: 2/4/2023
 * Creation date: 2/4/2023
 **/

#include <stdio.h>

int main(void) {
   int userNum;
   int userNum2;

   printf("Enter integer:\n");
   scanf("%d", &userNum);
   /* Type your code here. */

   //Prints what the user inputted
   printf("You entered: %d\n", userNum);

   //Prints the squared number of first input
   printf("%d squared is %d\n", userNum, userNum * userNum);

   //Prints the cubed number of first input
   printf("And %d cubed is %d!!\n", userNum, userNum * userNum * userNum);

   //Asks user for second input
   printf("Enter another integer:\n");
   scanf("%d", &userNum2);

   //Prints the sum of first and second input
   printf("%d + %d is %d\n", userNum, userNum2, userNum + userNum2);

   //Prints the product of the first and second input
   printf("%d * %d is %d\n", userNum, userNum2, userNum * userNum2);

   return 0;
}
