/**
 * Description: Program to remove all non-alphabetic characters
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/2/23
 * Creation date: 3/2/23
**/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Shows implementation of method RemoveNonAlpha
 * Assumption: user inputs a string of no more than 50 characters.
 * Input: userString[] and userStringAlphaOnly[]
 * Return: void
**/
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
   int j = 0; //tracker for userStringAlphaOnly

  //run through entire input string
   for(int i = 0; userString[i] != '\0'; i++){
      //add only characters into result string
      if((userString[i] >= 65 && userString[i] <= 90) || (userString[i] >= 97 && userString[i] <= 122) ) {
         userStringAlphaOnly[j] = userString[i];
         j++;
      }
   }

   printf("%s\n",userStringAlphaOnly);
}

/**
 * Shows implementation of method RemoveNonAlpha
 * Assumption: user inputs a string of no more than 50 characters.
 * Input: void
 * Return: int
**/
int main(void) {

   char string[51] = {}; //hold user input
   char result[51] = {}; //hold result string

   //read in input into character array
   for(int i = 0; i < 50 ; i++){
      scanf("%c", &string[i]);
   }

   //call to print the aplhapbet only string
   RemoveNonAlpha(string, result);

   return 0;
}
