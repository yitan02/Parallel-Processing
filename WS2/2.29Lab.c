/**
 * Description: This program uses multiple math functions.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/9/23
 * Creation date: 2/9/23
 **/

#include <stdio.h>
#include <math.h>

/**
 * This function prints multiple math operations.
 * Assumption: user input integers or floating point values.
 * Input parameters: void
 * Returns: void
**/
int main(void) {
   //Initialize three variables
   double x;
   double y;
   double z;

   //Scan the user inputs
   scanf("%lf", &x);
   scanf("%lf", &y);
   scanf("%lf", &z);

   //Print the math operations
   printf("%0.2lf ", pow(x, z));
   printf("%0.2lf ", pow(x, pow(y,2)));
   printf("%0.2lf ", fabs(y));
   printf("%0.2lf\n", sqrt(pow(x * y, z)));

   return 0;
}
