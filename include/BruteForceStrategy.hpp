#ifndef BRUTEFORCE
#define BRUTEFORCE

#include "SearchStrategy.hpp"

class BruteForceStrategy : public SearchStrategy {
public:
    virtual std::vector<Edge> search(ShoppingList &shoppingList) override;
    virtual ~BruteForceStrategy() override;
};

#endif