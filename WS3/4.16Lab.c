/**
 * Description: Program to find max value and average from many non-negative inputs of varied value
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/16/23
**/

#include <stdio.h>

/**
 * Method to find max value and average from many non-negative inputs of varied value
 * Assumptions: the user inputs integers
 * Input parameters: void
 * Returns: int
**/

int main(void) {

   int num_array[100] = {}; //int array to hold input integer
   int neg_track = 1; // to keep track of if input should stop
   int temp = 0; // variable to input individual integer
   int total_num = 0; // tracker to find number of inputs
   int j; // counter for loop to calculate sum
   int m = 0; // first pointer for number array
   int n = 1; // second pointer for number array
   double sum = 0; //hold sum
   double average = 0; // hold average
   int max = 0; // hold max of all inputs

   //scan values and input into array as long as negative integer is not input
   while(neg_track > 0){
      scanf("%d", &temp);
      //checking fornegative number
      if(temp < 0){
         neg_track = -1;
      }
      else {
         num_array[total_num] = temp;
         total_num++;
      }
   }

   //find max number from input integers
   while (m < total_num && n <= total_num) {
      //compares two values and finds which one is the max
      if(num_array[m] > num_array[n]){
         max = num_array[m];
         n++;
      }
      else if(num_array[m] < num_array[n]){
       max = num_array[n];
       m++;
      }
      else{
       m++;
       n++;
      }
   }

   //find average from input integers
   for(j = 0; j < total_num; j++){
      sum = sum + num_array[j];
   }
   average = sum / total_num;

   //prints max and average
   printf("%d %0.2lf\n", max, average);

   return 0;
}
