/**
 * Description: Program to count input length without spaces, periods, exclamation points, or commas.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/2/23
 * Creation date: 3/2/23
 **/
#include <stdio.h>
#include <string.h>

/**
 * Calculates the length of string input excluding spaces, periods, exclamation points, or commas.
 * Assumption: user inputs a string of no more than 50 characters.
 * Input: void
 * Return: int
 **/
int main(void) {
   char string[51] = {}; //array to hold input string
   int count = 0; //variable to hold count

   //read the input string to the array
   for (int i = 0; i < 50; i++){
      scanf("%c", &string[i]);
   }

   //compute length of string excluding spaces, periods, exclamations marks, and commas.
   for (int i = 0; string[i] != '\0'; i++){
       if(string[i] != ' ' && string[i] != '.' && string[i] != '!' && string[i] != ','){
          count++;
       }
   }

   //print the count
   printf("%d\n", count);

   return 0;
}
