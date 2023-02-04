/**
 * Description: This lab is an exercise on printing an arrow based on input values.
 * Author name: Yinglin Tan
 * Author email: yinglin.tan@sjsu.edu
 * Last modified date: 2/4/2023
 * Creation date: 2/4/2023
 **/

#include <stdio.h>

int main(void) {
   //There will be two variables: one for the base of the arrow and one for head of the arrow.
   int baseInt;
   int headInt;

   scanf("%d", &baseInt); //Get the input from the keyboard and assign it to baseInt.
   scanf("%d", &headInt); //Get the input from the keyboard and assign it to headInt.

   //Print format for the right arrow.
   printf("    %d\n", headInt);
   printf("    %d%d\n", headInt, headInt);
   printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
   printf("%d%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt, headInt);
   printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
   printf("    %d%d\n", headInt, headInt);
   printf("    %d\n", headInt);

   return 0;
}
