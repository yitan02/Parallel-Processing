/**
 * Description: This program finds words in the list that contains a character at least once.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/18/23
 **/

#include <stdio.h>
#include <string.h>

/**
 * This function finds words in a list that contain the search character.
 * Assumption: user enters an integer followed by words and then a search character.
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   int numWords;           //user input for the number of words
   char wordList[20][10];  //array to hold characters; each word has less than 10 characters
   char searchChar;        //variable to hold search character

   //first get the integer indicating the number of words that the user will enter
   scanf("%d", &numWords);

   //reads the list of words into the array
   for (int i = 0; i < numWords; i++){
         scanf("%s", wordList[i]);
   }

   //get the search character from the user
   scanf(" %c", &searchChar);

   //outer loop goes through each word in the list
   for (int j = 0; j < numWords; j++){
      //inner loop compare each character in the word to find if it contains the search character
      for(int k = 0; k < 10; k++){
         //if search character is found in the word, print the word and move on to the next word.
         if(wordList[j][k] == searchChar){
            printf("%s,", wordList[j]);
            break;
         }
      }
   }

   //print newLine for formatting
   printf("\n");

   return 0;
}
