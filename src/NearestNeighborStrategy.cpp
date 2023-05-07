// Good for medium n

#include "../include/NearestNeighborStrategy.hpp"
// helper function to get the index of an item in the shopping list
int NearestNeighborStrategy::getIndex(const std::vector<ItemNode*>& shopList, const std::string& name) {
    for (int i = 0; i < (int) shopList.size(); i++) {
        if (shopList[i]->getName() == name) {
            return i;
        }
    }
    return -1;
}

// // print shopping list
// std::cout << "Shopping List: ";
// for (ItemNode* item : shopList) {
//     std::cout << item->getName() << " ";
// }
// std::cout << std::endl;

std::vector<Edge> NearestNeighborStrategy::search(ShoppingList& shoppingList) {
    // get the adjacency list
    std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getTSPMap();

    // get shopping list
    std::vector<ItemNode*> shopList = shoppingList.getList();

    std::cout << "Shopping List: ";
    for (ItemNode* item : shopList) {
        std::cout << item->getName() << " ";
    }
    std::cout << std::endl;

    // path to return
    std::vector<Edge> path;

    // set termination variable
    bool done = false;

    // stand on Enter as current vertex
    std::string current_node = shopList.front()->getName(); 

    while(!done) {
        // find the lightest edge connecting current vertex
        std::pair<std::string, int> lightest_edge("", INT_MAX);
        for (Edge neighbor : adjList[current_node]) {
            // if neighbor is in the shopping list and less than the current lightest edge 
            if (getIndex(shopList, neighbor.name) != -1 && neighbor.name != "Exit") {
                if (lightest_edge.first == "" || neighbor.weight < lightest_edge.second) {
                    lightest_edge.first = neighbor.name;
                    lightest_edge.second = neighbor.weight;
                }
            }
            else if (shopList.size() == 2 && neighbor.name == "Exit" && neighbor.weight < lightest_edge.second) {
                lightest_edge.first = neighbor.name;
                lightest_edge.second = neighbor.weight;
                done = true;
            }
        }
        std::string temp_current = current_node;
        current_node = lightest_edge.first; // move to the next node
        for (Edge path_edge : adjList[temp_current]) {
            if (path_edge.name == current_node) {
                path.push_back(path_edge);
                break;
            }
        }

        // print each edge name in the path in order
        for (Edge e : path) {
            std::cout << e.name << " ";
        }
        
        // delete temp_current from shopping list
        int shopListi = 0;
        for (ItemNode* item : shopList) {
            if (item->getName() == temp_current) break;
            shopListi++;
        }
        std::cout << "shopListi: " << shopListi << std::endl;
        shopList.erase(shopList.begin() + shopListi);
    }

    // print each edge name in the path in order
    for (Edge e : path) {
        std::cout << e.name << " ";
    }

    return path;
}

NearestNeighborStrategy::~NearestNeighborStrategy() {};