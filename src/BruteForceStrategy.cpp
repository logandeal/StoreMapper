// Good for small n
#include "../include/BruteForceStrategy.hpp"
#include <climits>
std::vector<Edge> BruteForceStrategy::search(ShoppingList &shoppingList) {
    // get shopping list
    std::vector<ItemNode*> shopList = shoppingList.getList();

    // path to return
    std::vector<Edge> path;

    // number of items
    const int n = shoppingList.getList().size();
    if (n == 0) return path;

    // get the adjacency list
    std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getTSPMap();

    // initialize the items array with the names of the items
    std::vector<std::string> items(n + 1); // names of items, include start and end
    items[0] = shopList[0]->getName(); // first item
    for (int i = 1; i < n; i++) {
        items[i] = shopList[i]->getName();
    }
    items[n] = shopList[n-1]->getName(); // last item

    int ans = INT_MAX; // start total distance at max int
    do {
        // calculate the distance of the current permutation
        int curDist = 0;
        std::vector<Edge> currentPath;
        // loop through all the items in current permutation
        for (int i = 1; i <= n; i++) {
            std::string name_u = items[i-1], name_v = items[i]; // compare two items 
            // find the edge weight between the current and next item
            int w = 0;
            for (Edge neighbor : adjList[name_u]) {
                if (neighbor.name == name_v) {
                    w = neighbor.weight;
                    // add edge to path
                    currentPath.push_back(neighbor);
                    break;
                }
            }
            // add distance
            curDist += w;
        }
        if (curDist < ans) {
            path.clear();
            path.insert(path.begin(), currentPath.begin(), currentPath.end());
            ans = curDist;
        }
    } while (next_permutation(items.begin() + 1, items.end() - 1)); // exclude start and end items from permutation

    return path;
};


BruteForceStrategy::~BruteForceStrategy() {};