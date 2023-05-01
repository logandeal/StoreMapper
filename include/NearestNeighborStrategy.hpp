#ifndef NEARESTNEIGHBOR
#define NEARESTNEIGHBOR

#include "SearchStrategy.hpp"
#include <climits>
class NearestNeighborStrategy : public SearchStrategy {
public:
    std::vector<Edge> search(ShoppingList &shoppingList) override;
    ~NearestNeighborStrategy() override;
    int getIndex(const std::vector<ItemNode*>& shopList, const std::string& name);
};

#endif