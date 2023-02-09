/**
 * Description: This program gets integers userNum and x from the user and divide it by three times.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/9/23
 * Creation date: 2/9/23
 **/

#include <stdio.h>

/**
 * This function divides userNum by x three times.
 * Assumption: user enters two integers
 * Input parameters: void
 * Returns: void
**/
int main(void) {
   //Initialized variables for this function
   int userNum;
   int x;
   int output;

   //Scans the user's inputs
   scanf("%d", &userNum);
   scanf("%d", &x);

   //Performs the division 3 times
   output = userNum / x;
   printf("%d ", output);
   output = output / x;
   printf("%d ", output);
   output = output / x;
   printf("%d\n", output);

   return 0;
}
