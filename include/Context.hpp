#ifndef CONTEXT
#define CONTEXT

#include "SearchStrategy.hpp"

class Context {
    SearchStrategy* strat;                    
public:                                                   
    void setStrategy(SearchStrategy* strat_);
    void strategy(ShoppingList &shoppingList);
};

#endif