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

    // get the adjacency list
    std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getMap();

    // initialize the items array with the names of the items
    std::vector<std::string> items(n); // names of items
    for (int i = 0; i < n; i++) {
        items[i] = shopList[i]->getName();
    }

    int ans = INT_MAX; // start total distance at max int
    do {
        // calculate the distance of the current permutation
        int curDist = 0;
        std::vector<Edge> currentPath;
        // loop through all the items in current permutation
        for (int i = 1; i < n; i++) {
            // compare the current and next item
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
        // std::string name_u = items[n-1], name_v = items[0];
        // // find the edge weight between the last and first items
        // int w = 0;
        // for (Edge neighbor : adjList[name_u]) {
        //     if (neighbor.name == name_v) {
        //         w = neighbor.weight;
        //         break;
        //     }
        // }
        // curDist += w;
        if (curDist < ans) {
            path.clear();
            path.insert(path.begin(), currentPath.begin(), currentPath.end());
            ans = curDist;
        }
        // ans = std::min(ans, curDist);
    } while (next_permutation(items.begin(), items.end()));

    return path;
};

BruteForceStrategy::~BruteForceStrategy() {};