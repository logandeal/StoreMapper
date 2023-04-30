#include "../include/Context.hpp"

void Context::setStrategy(SearchStrategy* strat_)  { 
    strat = strat_;
}

std::vector<Edge> Context::strategy(ShoppingList &shoppingList) {
    if (strat) return strat->search(shoppingList); 
}     