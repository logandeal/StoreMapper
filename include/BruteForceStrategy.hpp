#ifndef BRUTEFORCE
#define BRUTEFORCE

#include "SearchStrategy.hpp"

class BruteForceStrategy : public SearchStrategy {
public:
    virtual void search(ShoppingList &shoppingList) override;
    virtual ~BruteForceStrategy() override;
};

#endif