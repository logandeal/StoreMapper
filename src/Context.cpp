#include "../include/Context.hpp"

void Context::setStrategy(Strategy* strat_)  { 
    strat = strat_;
}

void Context::strategy(std::vector<ItemNode> &ShoppingList) {
    if (strat) strat->search(ShoppingList); 
}     