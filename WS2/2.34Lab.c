/**
 * Description: This program prints a welcome message.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/9/23
 * Creation date: 2/9/23
 **/

#include <stdio.h>

/**
 * This function prints a welcome message based on input name.
 * Assumption: user enters a string.
 * Input parameters: void
 * Returns: void
**/
int main(void) {
   char userName[50];

   scanf("%s", userName);

   printf("Hello %s, and welcome to CS Online!\n", userName);

   return 0;
}
