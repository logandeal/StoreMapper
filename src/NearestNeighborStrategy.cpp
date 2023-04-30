// Good for medium n

#include "../include/NearestNeighborStrategy.hpp"
// helper function to get the index of an item in the shopping list
int NearestNeighborStrategy::getIndex(const std::vector<ItemNode*>& shopList, const std::string& name) {
    for (int i = 0; i < shopList.size(); i++) {
        if (shopList[i]->getName() == name) {
            return i;
        }
    }
    return -1;
}

std::vector<Edge> NearestNeighborStrategy::search(ShoppingList &shoppingList) {
    // get shopping list
    std::vector<ItemNode*> shopList = shoppingList.getList();

    // path to return
    std::vector<Edge> path;

    // number of items
    const int n = shoppingList.getList().size();

    // get the adjacency list
    std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getMap();

    // initialize the items array with the names of the items
    std::vector<std::string> items(n); // names of items
    for (int i = 0; i < n; i++) {
        items[i] = shopList[i]->getName();
    }

    // start with a random item as the current item
    std::string current = items[0];
    std::vector<std::string> visited; // keep track of visited items
    visited.push_back(current); 

    while (visited.size() < n) { // while there are still items to visit
        int minDist = INT_MAX;
        std::string nextItem;
        // loop through all the neighboring items and find the one with the shortest distance
        for (Edge neighbor : adjList[current]) {
            if (std::find(visited.begin(), visited.end(), neighbor.name) == visited.end()) {
                if (neighbor.weight < minDist) {
                    minDist = neighbor.weight;
                    nextItem = neighbor.name;
                }
            }
        }
        // add the edge to the path and mark the item as visited
        for (Edge neighbor : adjList[current]) {
            if (neighbor.name == nextItem) {
                path.push_back(neighbor);
                break;
            }
        }
        visited.push_back(nextItem);
        current = nextItem;
    }
    // // add the last edge to complete the cycle
    // std::string name_u = visited[n-1], name_v = visited[0];
    // for (Edge neighbor : adjList[name_u]) {
    //     if (neighbor.name == name_v) {
    //         path.push_back(neighbor);
    //         break;
    //     }
    // }
    return path;
};

NearestNeighborStrategy::~NearestNeighborStrategy() {};