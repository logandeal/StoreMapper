#include "../include/BruteForceStrategy.hpp"

BruteForceStrategy::search(std::vector<ItemNode> &ShoppingList, GroceryStore &Store) {
    const int n = ShoppingList.size(); // Number of items

    std::map<std::string, std::vector<Edge>> adjList = Store->getInstance();

    // Initialize the items array with the indices of the items
    std::vector<int> items(n);
    for (int i = 0; i < m; i++) {
        items[i] = shoppingList[i].index;
    }


    int ans = INT_MAX;
    do {
        // Calculate the distance of the current permutation
        int curDist = 0;
        // Loop through all the items in current permutation
        for (int i = 1; i < n; i++) {
            // compare the current and next item
            int u = items[i-1], v = items[i];
            // Find the edge weight between the current and next item
            int w = 0;
            for (auto neighbor : adjList[u]) {
                if (neighbor.first == v) {
                    w = neighbor.second;
                    break;
                }
            }
            curDist += w;
        }
        int u = items[m-1], v = items[0];
        // Find the edge weight between the last and first cities
        int w = 0;
        for (auto neighbor : items[u]) {
            if (neighbor.first == v) {
                w = neighbor.second;
                break;
            }
        }
        curDist += w;
        ans = min(ans, curDist);
    } while (next_permutation(items.begin(), items.end()));
};

BruteForceStrategy::~BruteForceStrategy() {};