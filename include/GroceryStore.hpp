#ifndef GROCERYSTORE_GUARD
#define GROCERYSTORE_GUARD

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "ShoppingList.hpp"

struct Edge {
    float weight;
    std::string name;

    bool operator==(const Edge a) const { //overwriting == so that it can compare two edges together
        return (a.weight == weight && a.name == name);
    }
};

//Singleton design pattern, only one instance of GroceryStore can exist at a time
class GroceryStore {
    public: 
        static GroceryStore& getInstance(){
            static GroceryStore instance;
            return instance;
	    }
        GroceryStore(GroceryStore const& ) = delete; // copy constructor;
        GroceryStore& operator=(GroceryStore const&) = delete; // copy assignment
        GroceryStore(GroceryStore &&) = delete; // move constructor
        GroceryStore& operator = (GroceryStore &&) = delete; // move assignment
        ~GroceryStore();
        void addItem(ShoppingList& list);
        void addAisle();
        void addEdge(std::string in, Edge newedge);
        void addNode(std::string newnode);
        void deleteNode(std::string out);
        void deleteEdge(std::string out, Edge edgeout);
        void printMap();
        void printShortestPath(std::vector<Edge> shortest);
        std::map<std::string, std::vector<Edge>> getMap();
        void deleteMap();
        int printNodes();
        void getEdge();
        void addEdgeMenu();
        void deleteNodeMenu();
        std::string returnNodeName(int node);
    private:
        std::map<std::string, std::vector<Edge>> adjacencyList;
        /*this adjacency list is a map, where it takes in the name of the node and the edge connected to it. It basically works
        as a directed graph, where each edge only points to the node it is connecting to. As our grocery store does not have one
        way aisles, we will need to basically add the edges twice (an edge for each direction)*/
        GroceryStore(){}; 
};
//This function will use the singleton grocery store to add the nodes/edges needed for the search
void setupGroceryStore();

#endif