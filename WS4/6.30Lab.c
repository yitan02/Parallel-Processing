/**
 * Description: Program to find max value and min value of four inputs
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/20/23
**/

#include <stdio.h>

/**
 * Method to find max value from four inputs
 * Assumptions: the user inputs four integers
 * Input parameters: four integer values
 * Returns: max integer value
**/
int MaxNumber(int num1, int num2, int num3, int num4){
   int num_array[] = {num1, num2, num3, num4}; //array of integers
   int max = num_array[0]; //declare max as first element in the array
   int temp; //temporary holder for max value

   //loop through array to find max number
   for(int i = 0; i < 3; i++){
      //if current pointer of i is larger then declare as the max value
     if(num_array[i] > num_array[i+1]){
        temp = num_array[i];
        //compare temp with max and replace with whichever is larger
        if(temp > max){
           max = temp;
        }
     }
      //if current pointer of i+1 is larger then declare as the max value
     else if (num_array[i] < num_array[i+1]){
        temp = num_array[i+1];
        //compare temp with max and replace with whichever is larger
        if(temp > max){
           max = temp;
        }
     }
   }

   return max;
}

/**
 * Method to find min value from four inputs
 * Assumptions: the user inputs four integers
 * Input parameters: four integer values
 * Returns: min integer value
**/
int MinNumber(int num1, int num2, int num3, int num4){
   int num_array[] = {num1, num2, num3, num4}; //array of integers
   int min = num_array[0]; //declare min as first element in the array
   int temp; //temporary holder for min value

   //loop through array to find min number
   for(int i = 0; i < 3; i++){
      //if current pointer of i is smaller then declare as the min value
     if(num_array[i] < num_array[i+1]){
        temp = num_array[i];
        //compare temp with min and replace with whichever is smaller
        if(temp < min){
           min = temp;
        }
     }
     //if current pointer of i+1 is smaller then declare as the min value
     else if (num_array[i] > num_array[i+1]){
        temp = num_array[i+1];
        //compare temp with min and replace with whichever is smaller
        if(temp < min){
           min = temp;
        }
     }
   }

   return min;
}

/**
 * Method to print max and min integers from four integers
 * Assumptions: the user inputs four integers
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   //variables to hold user input
   int num1;
   int num2;
   int num3;
   int num4;

   //scan all user inputs
   scanf("%d", &num1);
   scanf("%d", &num2);
   scanf("%d", &num3);
   scanf("%d", &num4);

   printf("Maximum is %d\n", MaxNumber(num1, num2, num3, num4));
   printf("Minimum is %d\n", MinNumber(num1, num2, num3, num4));

   return 0;
}
