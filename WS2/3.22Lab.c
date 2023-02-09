/**
 * Description: This program finds the smallest number.
 * Author name: Talia Syed, Yinglin Tan
 * Author email: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/9/23
 * Creation date: 2/9/23
 **/
#include <stdio.h>

/**
 * This function calculates the smallest of three integers and prints it.
 * Assumption: user enters three integers.
 * Input parameters: void
 * Returns: void
**/
int main(void) {
   int x;
   int y;
   int z;

  scanf("%d", &x);
  scanf("%d", &y);
  scanf("%d", &z);

  //This if statement compares all inputs to find the smallest integer.
  if (x < y && x < z)
  {
      printf("%d\n", x);
  }
  else if (y < z)
  {
      printf("%d\n", y);
  }
  else
  {
   printf("%d\n", z);
  }

   return 0;
}
