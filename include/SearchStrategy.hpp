#ifndef SEARCH_STRATEGY
#define SEARCH_STRATEGY

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "ItemNode.hpp"
#include "GroceryStore.hpp"
#include "ShoppingList.hpp"

class SearchStrategy {
public:
    virtual void search(ShoppingList &shoppingList) = 0;   
    virtual ~SearchStrategy() {};
};

#endif