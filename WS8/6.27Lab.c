/**
 * Description: This program count how many times a character appeared in a word
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/26/23
 * Creation date: 3/26/23
 **/

#include <stdio.h>
#include <string.h>

/**
 * Calculate how many times a character appeared in a word
 * Assumptions: a string and char is passed
 * Input: a string of less than 50 char and a search char
 * Output: int
 **/
int CalcNumCharacters(char* userString, char userChar){
   int counter = 0;

   //for loop checks if userString contains userChar
   for(int j = 0; j < strlen(userString); j++){
         //increase counter if userChar found
         if(userString[j] == userChar){
            counter++;
         }
   }

   //return counter
   return counter;
}

/**
 * Gets user input, calls CalcNumCharacters, and print out the result
 * Assumptions: user inputs a string less than 52 characters (including first character and space)
 * Input: void
 * Output: int
 **/
int main(void) {
   const int string_size = 50; //size of string
   const int input_size = 52; //size of input including the searchChar and space
   char input_string[input_size];  //array to hold the entire line of input
   char search_string[string_size]; //array to hold the string after searchChar

   //scan input to input_string
   fgets(input_string, input_size, stdin);

   //set searchChar to the first letter of input_String
   char searchChar = input_string[0];

   //put the string after the searchChar to search_string
   int index = 0;
   for(int i = 2; i < strlen(input_string); i++){
         search_string[index] = input_string[i];
         index++;
   }

   //call function and assign returned int to the variable return
   int result = CalcNumCharacters(search_string, searchChar);

   //print plural form if result is not equal to 1
   if(result != 1){
      printf("%d %c's\n", result, searchChar);
   }
   //print singular form if equal to 1
   else{
      printf("%d %c\n", result, searchChar);
   }
   return 0;
}
