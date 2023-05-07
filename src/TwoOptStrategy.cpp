// Good for small - medium n

#include "../include/TwoOptStrategy.hpp"
#include "../include/NearestNeighborStrategy.hpp"

// helper function to get the weight of a path
int getWeight(const std::vector<Edge>& path) {
    int weight = 0;
    for (const Edge& edge : path) {
        weight += edge.weight;
    }
    return weight;
}

std::vector<Edge> TwoOptStrategy::search(ShoppingList& shoppingList) {
    // run nearest neighbor algorithm
    NearestNeighborStrategy nearestNeighbor;
    std::vector<Edge> path = nearestNeighbor.search(shoppingList);

    bool improvement = true;
    while (improvement) {
        improvement = false;
        int size = path.size();
        for (int i = 1; i < size - 2; i++) {
            for (int j = i + 1; j < size; j++) {
                // reverse the order of nodes between i and j
                std::vector<Edge> newPath(path.begin(), path.begin() + i);
                std::reverse_copy(path.begin() + i, path.begin() + j + 1, std::back_inserter(newPath));
                // reverse inner path too
                std::reverse_copy(path.begin() + i + 1, path.begin() + j, std::back_inserter(newPath));
                for (int k = i; k <= j; k++) {
                    if (!path[k].path.empty()) {
                        std::reverse(path[k].path.begin(), path[k].path.end());
                    }
                    
                }
                newPath.insert(newPath.end(), path.begin() + j + 1, path.end());
                
                // calculate the new total weight
                int newWeight = getWeight(newPath);
                
                // if the new path is shorter, update path and set improvement flag
                if (newWeight < getWeight(path)) {
                    path = newPath;
                    improvement = true;
                }
            }
        }
    }

    return path;
}

// std::vector<Edge> TwoOptStrategy::search(ShoppingList &shoppingList) {
//     // set timeout
//     // int timeoutMilliseconds = 10;

//     // get shopping list
//     std::vector<ItemNode*> shopList = shoppingList.getList();

//     // number of items
//     int n = shopList.size();

//     // path to return
//     std::vector<Edge> path;

//     // get the adjacency list
//     std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getTSPMap();

//     // initialize the items array with the names of the items
//     std::vector<std::string> items; // names of items
//     for (ItemNode* item : shopList) {
//         items.push_back(item->getName());
//     }

//     // initialize the path with nearest neighbor
//     NearestNeighborStrategy nnStrategy;
//     path = nnStrategy.search(shoppingList);

//     printPathInOrder(path);

//     // perform 2-Opt
//     bool improvement = true;
//     // auto start = std::chrono::steady_clock::now();
//     while (improvement) {
//         // auto now = std::chrono::steady_clock::now();
//         // auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
//         // if (elapsedMilliseconds > timeoutMilliseconds) {
//         //     break;
//         // }
//         improvement = false;
//         std::cout << "INSIDE" << std::endl;
//         for (int i = 1; i < n; i++) {
//             if (path.size() < i+1) {
//                 break;
//             }
//             for (int j = i+1; j < n-1; j++) {
//                 if (path.size() < j+1) {
//                     break;
//                 }
//                 // get the edges
//                 Edge e1 = path[i-1];
//                 Edge e2 = path[i];
//                 Edge e3 = path[j];
//                 Edge e4 = path[j+1];
//                 // calculate the new distances
//                 short d1 = static_cast<short>(e1.weight + e2.weight);
//                 short d2 = static_cast<short>(e3.weight + e4.weight);
//                 short d3 = static_cast<short>(e1.weight + e3.weight);
//                 short d4 = static_cast<short>(e2.weight + e4.weight);
//                 // check if a swap would result in a shorter path
//                 if (d1 + d2 > d3 + d4) {
//                     // perform the swap
//                     // if (path.size() >= i + j + 2) {
//                         std::reverse(path.begin() + i, path.begin() + j + 1);
//                         // reverse inner path too
//                         for (int k = i; k <= j; k++) {
//                             std::reverse(path[k].path.begin(), path[k].path.end());
//                         }
//                         improvement = true;
//                     // }
//                 }
//             }
//         }
//     }

//     printPathInOrder(path);

//     std::cout << "HELLO" << std::endl;

//     return path;
// }




TwoOptStrategy::~TwoOptStrategy() {};