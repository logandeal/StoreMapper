#ifndef GROCERYSTORE_GUARD
#define GROCERYSTORE_GUARD

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>


struct Edge {
    float weight;
    std::string name;

    bool operator==(const Edge a) const {
        return (a.weight == weight && a.name == name);
    }
};

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
        void addEdge(std::string in, Edge newedge);
        void addNode(std::string newnode);
        void deleteNode(std::string out);
        void deleteEdge(std::string out, Edge edgeout);
        void printMap();
        std::map<std::string, std::vector<Edge>> getMap();
    private:
        std::map<std::string, std::vector<Edge>> adjacencyList;
        GroceryStore(){}; 
};

#endif