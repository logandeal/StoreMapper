// Singleton
// Create the adjacency List
// Stores the items
#include "../include/GroceryStore.hpp"

void GroceryStore::addEdge(std::string in, Edge newedge){
    Edge e; //creating a new Edge that will be the counterpart to newedge 
    e.name = in;
    e.weight = newedge.weight;
    adjacencyList.at(in).push_back(newedge); //pushing both e and newedge onto the adjacency list (we need both directions)
    adjacencyList.at(newedge.name).push_back(e);
}
void GroceryStore::addNode(std::string newnode){
    std::vector<Edge> edges; //creating a blank vector of edges
    adjacencyList.insert({newnode, edges}); //inserting the node and the edges connected to it
}
void GroceryStore::deleteNode(std::string out){
    adjacencyList.erase(out); //deleting the Node
    for(auto& it : adjacencyList){ //looping through the entire adjacency list
        auto &vec = it.second;
        auto junk = std::remove_if(vec.begin(), vec.end(), [&](Edge const &e){ //we remove an edge iff it is pointing to the node we just deleted
            return e.name == out;
        });
        vec.erase(junk, vec.end()); //removing 
    }
}

void GroceryStore::deleteEdge(std::string out, Edge edgeout){
    //deleting both edge from both directions
    adjacencyList.at(out).erase(std::remove(adjacencyList.at(out).begin(), adjacencyList.at(out).end(), edgeout), adjacencyList.at(out).end());
    //first getting the vector associated with the node, then erasing that edge 
    std::string name2 = edgeout.name;
    edgeout.name = out;
    adjacencyList.at(name2).erase(std::remove(adjacencyList.at(name2).begin(), adjacencyList.at(name2).end(), edgeout), adjacencyList.at(name2).end());
}

void GroceryStore::printMap(){
    for(auto it = adjacencyList.cbegin(); it != adjacencyList.cend(); ++it) //looping through the adjacency list
    {
        std::cout << it->first << ":\n"; //printing the name of the node
        for(auto p : it->second){ //looping through the edge vectors
            std::cout << "  [";
            std::cout << p.name << ", ";
            std::cout << p.weight << "]"; //then printing each edge associated with the node
        }
        std::cout << "\n";
    }
}

//destructor
GroceryStore::~GroceryStore(){

}

std::map<std::string, std::vector<Edge>> GroceryStore::getMap(){
    return adjacencyList; //helper function that returns the adjacency list
};

void GroceryStore::printShortestPath(std::vector<Edge> shortest){
    std::cout << "Entrance --> "; //Will always start at entrance
    for(auto it = shortest.cbegin(); it != shortest.cend(); ++it){ //looping through the shortest path vector
        std::cout << it->name << ", Distance: " << it->weight << std::endl; //printing out the name of which the edge is connected to, same with the distance
        if(it != shortest.cend() - 1) //don't print out the next name if we are at the end
            std::cout << it->name << " --> "; //print the next name
    }
}
