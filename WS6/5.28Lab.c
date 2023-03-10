/**
 * Description: This program finds if a strong is a palindrome
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 3/9/23
 * Creation date: 3/5/23
 **/
#include <stdio.h>
#include <string.h>

/**
 * This program finds if a strong is a palindrome
 * Assumptions: user inputs readable characters
 * Input: void
 * Output: int
 **/
int main(void) {

   char string[51] = {};
   char string2[51] = {};
   int is_palindrome = 1;
   int str_len = 0;
   int counter = 0;

   //read the input string to the array
   for (int i = 0; i < 50; i++){
      scanf("%c", &string[i]);
   }

   str_len = strlen(string);

   //transfer data from input string to new string without spaces
   for (int i = 0; i < str_len; i++){
      if(string[i] != ' '){
         string2[counter] = string[i];
         counter++;
      }
   }

   str_len = strlen(string2);

   //compare both strings to see if they match completely
   for (int i = 0; i < str_len; i++){
      if (string2[str_len - i - 1] != string2[i]){
         is_palindrome = 0;
      }
   }

   //if palindrome, print as correct
   if (is_palindrome){
      printf("palindrome: %s\n", string);
   }
   //if not palidrome, print false
   else {
       printf("not a palindrome: %s\n", string);
   }

   return 0;
}
