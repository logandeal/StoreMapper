#ifndef CONTEXT
#define CONTEXT

#include "SearchStrategy.hpp"

class Context {
    SearchStrategy* strat;                    
public:                                                   
    void setStrategy(SearchStrategy* strat_);
    std::vector<Edge> strategy(ShoppingList &shoppingList);
};

#endif