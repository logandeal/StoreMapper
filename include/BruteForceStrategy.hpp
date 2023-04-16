#ifndef BRUTEFORCE
#define BRUTEFORCE

#include "SearchStrategy.hpp"

class BruteForceStrategy : public SearchStrategy {
public:
    virtual void search(std::vector<ItemNode> &ShoppingList) override;
    virtual ~BruteForceStrategy() override;
};

#endif