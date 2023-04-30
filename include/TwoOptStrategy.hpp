#ifndef TWOOPT
#define TWOOPT

#include "SearchStrategy.hpp"

class TwoOptStrategy : public SearchStrategy {
public:
    virtual std::vector<Edge> search(ShoppingList &shoppingList) override;
    virtual ~TwoOptStrategy() override;
};

#endif