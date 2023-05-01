#ifndef BRUTEFORCE
#define BRUTEFORCE

#include "SearchStrategy.hpp"
#include <climits>
class BruteForceStrategy : public SearchStrategy {
public:
    std::vector<Edge> search(ShoppingList &shoppingList) override;
    ~BruteForceStrategy() override;
};

#endif