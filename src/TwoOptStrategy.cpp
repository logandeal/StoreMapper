// Good for small - medium n

#include "../include/TwoOptStrategy.hpp"
#include "../include/NearestNeighborStrategy.hpp"

std::vector<Edge> TwoOptStrategy::search(ShoppingList &shoppingList) {
    // get shopping list
    std::vector<ItemNode*> shopList = shoppingList.getList();

    // path to return
    std::vector<Edge> path;

    // number of items
    const int n = shoppingList.getList().size();

    // get the adjacency list
    std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getTSPMap();

    // initialize the items array with the names of the items
    std::vector<std::string> items(n); // names of items
    for (int i = 0; i < n; i++) {
        items[i] = shopList[i]->getName();
    }

    // initialize the path with nearest neighbor
    NearestNeighborStrategy nnStrategy;
    path = nnStrategy.search(shoppingList);


    // perform 2-Opt
    bool improvement = true;
    while (improvement) {
        improvement = false;
        for (int i = 1; i < n-2; i++) {
            for (int j = i+1; j < n-1; j++) {
                // get the edges
                Edge e1 = path[i-1];
                Edge e2 = path[i];
                Edge e3 = path[j];
                Edge e4 = path[j+1];
                // calculate the new distances
                int d1 = e1.weight + e2.weight;
                int d2 = e3.weight + e4.weight;
                int d3 = e1.weight + e3.weight;
                int d4 = e2.weight + e4.weight;
                // check if a swap would result in a shorter path
                if (d1 + d2 > d3 + d4) {
                    // perform the swap
                    std::reverse(path.begin() + i, path.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }

    return path;
}

TwoOptStrategy::~TwoOptStrategy() {};