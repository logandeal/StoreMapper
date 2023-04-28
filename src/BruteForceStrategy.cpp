// Good for small n

#include "../include/BruteForceStrategy.hpp"

void BruteForceStrategy::search(ShoppingList &shoppingList) {
    // get shopping list
    std::vector<ItemNode*> shopList = shoppingList.getList();

    // number of items
    const int n = shoppingList.getList().size();

    // get the adjacency list
    std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getMap();

    // initialize the items array with the names of the items
    std::vector<std::string> items(n);
    for (int i = 0; i < n; i++) {
        items[i] = shopList[i]->getName();
    }

    int ans = INT_MAX;
    do {
        // calculate the distance of the current permutation
        int curDist = 0;
        // loop through all the items in current permutation
        for (int i = 1; i < n; i++) {
            // compare the current and next item
            std::string name_u = items[i-1], name_v = items[i];
            // find the edge weight between the current and next item
            int w = 0;
            for (Edge neighbor : adjList[name_u]) {
                if (neighbor.name == name_v) {
                    w = neighbor.weight;
                    // add to path
                    break;
                }
            }
            curDist += w;
        }
        std::string name_u = items[n-1], name_v = items[0];
        // find the edge weight between the last and first items
        int w = 0;
        for (Edge neighbor : adjList[name_u]) {
            if (neighbor.name == name_v) {
                w = neighbor.weight;
                break;
            }
        }
        curDist += w;
        ans = std::min(ans, curDist);
        // if it's ans then get rid of the curDist nodes from 
    } while (next_permutation(items.begin(), items.end()));

    // return std::vector<Edge> path in order;
};

BruteForceStrategy::~BruteForceStrategy() {};