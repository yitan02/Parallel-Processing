/**
 * Description: This program prints a house real estate summary.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/9/23
 * Creation date: 2/9/23
 **/
#include <stdio.h>

/**
 * This function takes the current price and previous price and prints a house real estate summary.
 * Assumption: user inputs integers.
 * Input parameters: void
 * Returns: void
**/
int main(void) {
   int currentPrice;
   int lastMonthsPrice;

   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);

   printf("This house is $%d. ", currentPrice);
   printf("The change is $%d since last month.\n", currentPrice - lastMonthsPrice);
   printf("The estimated monthly mortgage is $%lf.\n", (currentPrice * 0.051) / 12);

   return 0;
}
