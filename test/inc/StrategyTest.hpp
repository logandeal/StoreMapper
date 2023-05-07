#ifndef SHOPPINGLISTTEST_GUARD
#define SHOPPINGLISTTEST_GUARD
#include "gtest/gtest.h"
#include "../../include/ShoppingList.hpp"
#include "../../include/GroceryStore.hpp"

class ShoppingListTest : public ::testing::Test {
    protected:
        ShoppingList* list;
        void SetUp() override {
            list = new ShoppingList();
            setupGroceryStoreNodes();
            setupGroceryStoreEdges();
            GroceryStore::getInstance().updateTSPMap();
        }
        void TearDown() override {
            delete list;
            GroceryStore::getInstance().deleteMap();
        }
};

#endif