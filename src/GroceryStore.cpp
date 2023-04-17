// Singleton
// Create the adjacency List
// Stores the items
#include "../include/GroceryStore.hpp"

void GroceryStore::addEdge(std::string in, Edge newedge){
    Edge e;
    e.name = in;
    e.weight = newedge.weight;
    adjacencyList.at(in).push_back(newedge);
    adjacencyList.at(newedge.name).push_back(e);
}
void GroceryStore::addNode(std::string newnode){
    std::vector<Edge> edges;
    adjacencyList.insert({newnode, edges});
}
void GroceryStore::deleteNode(std::string out){
    adjacencyList.erase(out);
}

// void GroceryStore::deleteEdge(std::string out, Edge edgeout){
//     adjacencyList.at(out).erase(std::remove(adjacencyList.at(out).begin(), adjacencyList.at(out).end(), edgeout));
// }

void GroceryStore::printMap(){
    for(auto it = adjacencyList.cbegin(); it != adjacencyList.cend(); ++it)
    {
        std::cout << it->first << ":\n";
        for(auto p : it->second){
            std::cout << "  [";
            std::cout << p.name << ", ";
            std::cout << p.weight << "]";
        }
        std::cout << "\n";
    }
}


GroceryStore::~GroceryStore(){

}