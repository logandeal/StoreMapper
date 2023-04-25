#include "../include/Context.hpp"

void Context::setStrategy(SearchStrategy* strat_)  { 
    strat = strat_;
}

void Context::strategy(ShoppingList &shoppingList) {
    if (strat) strat->search(shoppingList); 
}     