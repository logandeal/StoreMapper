#ifndef DIJKSTRA2D
#define DIJKSTRA2D

#include "SearchStrategy.hpp"
#include <climits>
#include <math.h>

class Dijkstra2DStrategy : public SearchStrategy {
public:
    virtual std::vector<Edge> search(ShoppingList &shoppingList) override;
    virtual ~Dijkstra2DStrategy() override;
};

#endif