#ifndef CONTEXT
#define CONTEXT

#include "SearchStrategy.hpp"

class Context {
    SearchStrategy* strat;                    
public:                                                   
    void setStrategy(SearchStrategy* strat_);
    void strategy(std::vector<ItemNode> &ShoppingList);
};

#endif