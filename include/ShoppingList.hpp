#ifndef SHOPPINGLIST_GUARD
#define SHOPPINGLIST_GUARD
#include <iostream>
#include <vector>
#include "ItemNode.hpp"
#include <string>
class ShoppingList {
    public:
        void addItem();
        void removeItem();
        void viewCurrentList();
        ShoppingList();
        ~ShoppingList();
        std::vector<ItemNode*> getList();
    private:
        std::vector<ItemNode*> list;
        std::vector<ItemNode*> possiblechoices;
};

#endif