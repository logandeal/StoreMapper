#ifndef NEARESTNEIGHBOR
#define NEARESTNEIGHBOR

#include "SearchStrategy.hpp"
#include <climits>
class NearestNeighborStrategy : public SearchStrategy {
public:
    virtual std::vector<Edge> search(ShoppingList &shoppingList) override;
    virtual ~NearestNeighborStrategy() override;
    int getIndex(const std::vector<ItemNode*>& shopList, const std::string& name);
};

#endif