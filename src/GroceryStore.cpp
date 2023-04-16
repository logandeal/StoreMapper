// Singleton
// Create the adjacency List
// Stores the items
#include "../include/GroceryStore.hpp"

void GroceryStore::addEdge(std::string in, Edge newedge){
    adjacencyList.at(in).push_back(newedge);
}
void GroceryStore::addNode(std::string newnode){
    std::vector<Edge> edges;
    adjacencyList.insert({newnode, edges});
}
void GroceryStore::deleteNode(std::string out){
    adjacencyList.erase(out);
}
void GroceryStore::deleteEdge(std::string out, Edge edgeout){
    adjacencyList.at(out).erase(std::remove(adjacencyList.at(out).begin(), adjacencyList.at(out).end(), edgeout));
}