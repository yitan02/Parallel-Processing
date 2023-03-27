/**
 * Description: This program count how many times a letter appeared in a word
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/26/23
 * Creation date: 3/26/23
 **/

#include <stdio.h>
#include <string.h>

/**
 * Calculate how many times a letter appeared in a word
 * Assumptions: a string and char is passed
 * Input: a string of less than 50 char and a search char
 * Output: int
 **/
int CalcNumCharacters(char* userString, char userChar){
   int count = 0; //counter for userString

   //traverse userString to find if current character and key match
   while (*userString != '\0'){
      //if key character and string character match, incrment counter
      if(*userString == userChar){
         count++;
      }
      *userString++; //increment pointer
   }
   return count;
}

/**
 * Gets user input, calls CalcNumCharacters, and print out the result
 * Assumptions: user inputs a string less than 50 characters
 * Input: void
 * Output: int
 **/
int main(void) {
   char input[52] = {0}; //take input from stdin
   char input_char; // hold the input character
   char input_string[50] = {0}; // hold the input string
   int counter = 0; //counter for adding input to string array
   char *ptr = input_string; //pointer for string array

   fgets(input, sizeof(input), stdin); // take in entire input

   input_char = input[0]; //first character of input is comparison character

   //add the input from stdin to the string array
   for(int i = 2; input_string[i] != '\0'; i++){
      input_string[counter] = input[i];
      counter++;
   }

   int numCalc = CalcNumCharacters(ptr, input_char); // run funtion and put result into an integer variable

   //if the output is not one, then print in plural form
   if(numCalc != 1){
      printf("%d %c's\n", numCalc, input_char);
   }
   //if output is one, print in singular form
   else {
      printf("%d %c\n", numCalc, input_char);
   }

   return 0;
}
