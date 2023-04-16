#include <iostream>
#include <map>
#include <vector>
#include <algorithm>


struct Edge {
    float weight;
    std::string name;
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
    private:
        std::map<std::string, std::vector<Edge>> adjacencyList;
        GroceryStore(){}; 
};