#ifndef BRUTEFORCE
#define BRUTEFORCE

#include "SearchStrategy.hpp"

class BruteForceStrategy : public SearchStrategy {
public:
    virtual void search(std::vector<ItemNode> &ShoppingList, GroceryStore &Store) override;
    virtual ~BruteForceStrategy() override;
};

#endif