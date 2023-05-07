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
    // create path
    std::vector<Edge> path;

    // number of items
    const int n = shoppingList.getList().size();
    if (n == 0) return path;

    // run nearest neighbor algorithm
    NearestNeighborStrategy nearestNeighbor;
    path = nearestNeighbor.search(shoppingList);

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




TwoOptStrategy::~TwoOptStrategy() {};