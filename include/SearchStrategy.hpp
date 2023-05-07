#ifndef SEARCH_STRATEGY
#define SEARCH_STRATEGY

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <queue>

#include "ItemNode.hpp"
#include "GroceryStore.hpp"
#include "ShoppingList.hpp"

class SearchStrategy {
public:
    virtual std::vector<Edge> search(ShoppingList &shoppingList) = 0;   
    virtual ~SearchStrategy() {};
    void printPathInOrder(const std::vector<Edge> path);
};

#endif