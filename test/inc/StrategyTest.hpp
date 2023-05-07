#ifndef STRATEGYTEST_GUARD
#define STRATEGYTEST_GUARD
#include "gtest/gtest.h"
#include "../../include/ShoppingList.hpp"
#include "../../include/GroceryStore.hpp"
#include "../../include/Context.hpp"
#include "../../include/SearchStrategy.hpp"
#include "../../include/BruteForceStrategy.hpp"
#include "../../include/NearestNeighborStrategy.hpp"
#include "../../include/TwoOptStrategy.hpp"

class StrategyTest : public ::testing::Test {
    protected:
        ShoppingList* list;
        Context k;
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