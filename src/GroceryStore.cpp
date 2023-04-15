// Singleton
// Create the adjacency List
// Stores the items
#include <iostream>
#include <map>
#include <vector>

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
    private:
        std::map<std::string, std::vector<Edge>> adjacencyList;
        GroceryStore(){}; 
}