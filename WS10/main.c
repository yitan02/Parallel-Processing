/**
 * Description: This program asks user for items and prints the total cost of the items.
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/9/23
 * Creation date: 4/8/23
 **/

#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

// prompts user for two items, outputs cost of each item, and the total cost of two items.
int main(void) {

   // declare two objects of the struct
   ItemToPurchase item1;
   ItemToPurchase item2;

   /** prompt for item 1 **/
   printf("Item 1\n");

   printf("Enter the item name:\n");
   gets(item1.itemName, 50, stdin);

   printf("Enter the item price:\n");
   scanf("%d", &item1.itemPrice);

   printf("Enter the item quantity:\n\n");
   scanf("%d", &item1.itemQuantity);

   /** code to allow user to input a new string **/
   char c = getchar();
   while(c != '\n' && c != EOF) {
       c = getchar();
   }

   /** prompt for item 2 **/
   printf("Item 2\n");

   printf("Enter the item name:\n");
   gets(item2.itemName, 50, stdin);

   printf("Enter the item price:\n");
   scanf("%d", &item2.itemPrice);

   printf("Enter the item quantity:\n\n");
   scanf("%d", &item2.itemQuantity);

   /** print total cost **/
   printf("TOTAL COST\n");
   int total1 = PrintItemCost(item1);
   int total2 = PrintItemCost(item2);

   printf("\nTotal: $%d\n", total1 + total2);
   return 0;
}
