#ifndef SHOPPINGLIST_GUARD
#define SHOPPINGLIST_GUARD
#include <iostream>
#include <vector>
#include "ItemNode.hpp"
#include <string>
#include <iomanip>
#include "GroceryStore.hpp"
class ShoppingList {
    public:
        void addItem();
        void removeItem();
        void viewCurrentList();
        ShoppingList();
        ~ShoppingList();
        std::vector<ItemNode*> getList();
        void setupForSearch();
        void addToPossibleChoices(ItemNode* item);
    private:
        std::vector<ItemNode*> list;
        std::vector<ItemNode*> possiblechoices;
};
bool hasCharacters(std::string);
#endif