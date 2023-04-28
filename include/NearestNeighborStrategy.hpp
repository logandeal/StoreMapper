#ifndef NEARESTNEIGHBOR
#define NEARESTNEIGHBOR

#include "SearchStrategy.hpp"

class NearestNeighborStrategy : public SearchStrategy {
public:
    virtual void search(ShoppingList &shoppingList) override;
    virtual ~NearestNeighborStrategy() override;
};

#endif