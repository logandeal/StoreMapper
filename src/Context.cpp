#include "../include/Context.hpp"

void Context::setStrategy(std::unique_ptr<SearchStrategy> strat_)  { 
    strat = std::move(strat_);
}

std::vector<Edge> Context::strategy(ShoppingList &shoppingList) {
    if (strat) return strat->search(shoppingList); 
    throw std::runtime_error("Strategy not set!");
}     