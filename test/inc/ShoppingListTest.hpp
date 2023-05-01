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
        }
        void TearDown() override {
            delete list;
        }
};

#endif