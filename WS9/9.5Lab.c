/**
 * Description: This program parse the input to determine if they are two comma separated words.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/3/23
 * Creation date: 4/2/23
 **/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Prompt user for input and determine if the given input can be parsed.
 * Assumptions: two names are passed or q to finish inputting.
 * Input: a string of less than 50 char.
 * Output: int
 **/

int main(void) {
   char input[50] = {'\0'};
   int has_comma = 0;
   char first_word[50];
   char second_word[50];
   bool input_done = false;

   //while loop runs till user inputs "exit"
   while(!input_done){
      has_comma = 0; //reset has_comma

      printf("Enter input string:\n");

      fgets(input, sizeof(input), stdin); //scan user input

      //check if input contains comma
      for(int i = 0; i < strlen(input); i++){
         if(input[i] == ','){
            has_comma = 1;
            input[i] = ' ';
         }
      }

      //stop while loop if user inputs exit
      if(input[0] == 'q' && input[1] == '\n'){
         input_done = true;
      }

      //if comma found, parse input to first_word and second_word, and print it
      else if(has_comma == 1){
         sscanf(input,"%49s %49s", first_word, second_word);

         printf("First word: %s\n", first_word);
         printf("Second word: %s\n\n", second_word);
      }
      //if there's no comma found, then print the error
      else{
         printf("Error: No comma in string.\n\n");
      }

   }

   return 0;
}
