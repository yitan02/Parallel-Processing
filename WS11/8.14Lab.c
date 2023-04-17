/**
 * Description: Program to create linkedlist implementation of a contact list
 * Author names: Talia Syed, Yinglin Tan
 * Author emails: talia.syed@sjsu.edu, yinglin.tan@sjsu.edu
 * Last modified date: 4/17/23
 * Creation date: 4/16/23
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

/**
 * Method to create linkedlist node
 * Assumptions: n/a
 * Input parameters: n/a
 * Returns: n/a
**/
typedef struct ContactNode_struct {
   char contactName[MAX_LEN];
   char contactPhoneNumber[MAX_LEN];
   struct ContactNode_struct* nextNodePtr;
} ContactNode;

/**
 * Method to initialize a node
 * Assumptions: the user inputs valid items
 * Input parameters: ContactNode*, char*, char*
 * Returns: void
**/
void InitializeContactNode(ContactNode* node, char* name, char* number){
   strcpy(node->contactName, name);
   strcpy(node->contactPhoneNumber, number);
}

/**
 * Method get contact name
 * Assumptions: valid contact name
 * Input parameters: ContactNode*
 * Returns: char*
**/
char* GetName(ContactNode* node){
   return node->contactName;
}

/**
 * Method to get contact number
 * Assumptions: valid phone number
 * Input parameters: ContactNode*
 * Returns: char*
**/
char* GetPhoneNumber(ContactNode* node){
   return node->contactPhoneNumber;
}

/**
 * Method to print nodes
 * Assumptions: n/a
 * Input parameters: ContactNode*
 * Returns: void
**/
void PrintContactNode(ContactNode* node){
   printf("\nName: %s\n", GetName(node));
   printf("Phone number: %s\n", GetPhoneNumber(node));
}

/**
 * Method to append new node to end
 * Assumptions: valid new node
 * Input parameters: ContactNode*, ContactNode*
 * Returns: void
**/
void InsertAfter(ContactNode* this_node, ContactNode* next_node){
   ContactNode* temp = NULL;

   temp = this_node->nextNodePtr;
   this_node->nextNodePtr = next_node;
   next_node->nextNodePtr = temp;
}

/**
 * Method to get node pointer
 * Assumptions: valid pointer
 * Input parameters: ContactNode*
 * Returns: ContactNode*
**/
ContactNode* GetNext(ContactNode* node){
   return node->nextNodePtr;
}

/**
 * Method to create linked list contact list and print out in correct format
 * Assumptions: valid nodes
 * Input parameters: void
 * Returns: int
**/
int main(void) {
   ContactNode* first_node = NULL;
   ContactNode* second_node = NULL;
   ContactNode* third_node = NULL;
   ContactNode* curr_node = NULL;
   char name_line[MAX_LEN];
   char num_line[MAX_LEN];

   /**setting up first node**/
   first_node = (ContactNode*)malloc(sizeof(ContactNode));
   fgets(name_line, sizeof(name_line), stdin);
   name_line[strlen(name_line) - 1] = '\0';

   fgets(num_line, sizeof(num_line), stdin);
   num_line[strlen(num_line) - 1] = '\0';

   InitializeContactNode(first_node, name_line, num_line);


   /**second node**/
   second_node = (ContactNode*)malloc(sizeof(ContactNode));
   fgets(name_line, sizeof(name_line), stdin);
   name_line[strlen(name_line) - 1] = '\0';

   fgets(num_line, sizeof(num_line), stdin);
   num_line[strlen(num_line) - 1] = '\0';

   InitializeContactNode(second_node, name_line, num_line);


   /**third node**/
   third_node = (ContactNode*)malloc(sizeof(ContactNode));
   fgets(name_line, sizeof(name_line), stdin);
   name_line[strlen(name_line) - 1] = '\0';

   fgets(num_line, sizeof(num_line), stdin);

   InitializeContactNode(third_node, name_line, num_line);

   /**Linking the nodes**/
   InsertAfter(first_node, second_node);
   InsertAfter(second_node, third_node);

   /**print each one out**/
   printf("Person 1: %s, %s\n", first_node->contactName, first_node->contactPhoneNumber);
   printf("Person 2: %s, %s\n", second_node->contactName, second_node->contactPhoneNumber);
   printf("Person 3: %s, %s\n", third_node->contactName, third_node->contactPhoneNumber);

   printf("CONTACT LIST");
   curr_node = first_node;
   while(curr_node != NULL){
      PrintContactNode(curr_node);
      curr_node = GetNext(curr_node);
   }

   return 0;
}
