#ifndef CONTEXT
#define CONTEXT

#include "SearchStrategy.hpp"
#include <memory>
class Context {
    std::unique_ptr<SearchStrategy> strat{};                    
public:                                               
    void setStrategy(std::unique_ptr<SearchStrategy> strat_);
    std::vector<Edge> strategy(ShoppingList &shoppingList);
};

#endif