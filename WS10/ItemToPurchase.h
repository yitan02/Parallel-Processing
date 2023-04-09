#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

// struct for ItemToPurchase
typedef struct ItemToPurchase{
   char itemName[50];
   int itemPrice;
   int itemQuantity;
} ItemToPurchase;

// related-functions
void MakeItemBlank(ItemToPurchase* item);
int PrintItemCost(ItemToPurchase item);

#endif
