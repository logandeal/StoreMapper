#ifndef TWOOPT
#define TWOOPT

#include "SearchStrategy.hpp"

class TwoOptStrategy : public SearchStrategy {
public:
    std::vector<Edge> search(ShoppingList &shoppingList) override;
    ~TwoOptStrategy() override;
};

#endif