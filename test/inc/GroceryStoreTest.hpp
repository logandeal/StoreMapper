#ifndef GROCERYSTORETEST_GUARD
#define GROCERYSTORETEST_GUARD
#include "gtest/gtest.h"
#include "../../include/GroceryStore.hpp"
#include "../../include/ShoppingList.hpp"

class GroceryStoreTest : public ::testing::Test {
    protected:
        ShoppingList* list;
        void SetUp() override {
            list = new ShoppingList();
            setupGroceryStore();
        }
        void TearDown() override {
            delete list;
            GroceryStore::getInstance().deleteMap();
        }
};


#endif