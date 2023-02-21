/**
 * Description: Program to convert laps to miles.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/20/23
 **/

#include <stdio.h>

/**
 * This function converts the number of laps to miles.
 * Assumption: user inputs a double value when calling the function.
 * Input: a double value of laps
 * Return: a double value of miles
 **/
double LapsToMiles(double userLaps){
   return userLaps * 0.25;
}

/**
 * This function gets user input and calls the LapsToMiles function.
 * Assumption: user inputs a double value when calling the function.
 * Input: void
 * Return: int
 **/
int main(void) {
   double laps; //hold user input for number of laps

   //get number of laps from user
   scanf("%lf", &laps);

   //call LapsToMiles function with laps as input and output the result
   printf("%0.2lf\n", LapsToMiles(laps));

   return 0;
}
