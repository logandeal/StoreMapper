#ifndef GROCERYSTORETEST_GUARD
#define GROCERYSTORETEST_GUARD
#include "gtest/gtest.h"
#include "../../include/GroceryStore.hpp"

class GroceryStoreTest : public ::testing::Test {
    protected:
        void SetUp() override {
            GroceryStore::getInstance().printMap();
        }
        void TearDown() override {  
        }
};


#endif