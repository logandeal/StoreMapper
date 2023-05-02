#include "../include/Context.hpp"

//update the strategy by moving the smart pointer to the new strategy
void Context::setStrategy(std::unique_ptr<SearchStrategy> strat_)  { 
    strat = std::move(strat_);
}

//if the pointer is set, then execute the given search on the shopping list
std::vector<Edge> Context::strategy(ShoppingList &shoppingList) {
    if (strat) return strat->search(shoppingList); 
    throw std::runtime_error("Strategy not set!");
}     