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

int GroceryStore::printNodes(){
    int i = 1;
    for(auto it = adjacencyList.cbegin(); it != adjacencyList.cend(); ++it){ //looping through the adjacency list
        std::cout << i << ") " << it->first << "\n";
        i++;
    }
    return i;
}

std::string GroceryStore::returnNodeName(int node){
    int i = 1;
    for(auto it = adjacencyList.cbegin(); it != adjacencyList.cend(); ++it){ //looping through the adjacency list
        if(i == node){
            return it->first;
        }
        i++;
    }
    return "Doesn't Exist";
}

void GroceryStore::getEdge(){
    std::cout << "Which node would you like to delete an edge from?\n";
    int i = 1;
    for(auto it = adjacencyList.cbegin(); it != adjacencyList.cend(); ++it){ //looping through the adjacency list
        std::cout << i << ") " << it->first << "\n";
        i++;
    }
    int check = 0;
    std::cin >> check;
    std::cin.clear();
    if(check < 1 || check > i){
        throw std::invalid_argument("Please enter a valid argument!");
    }
    std::string name = GroceryStore::getInstance().returnNodeName(check);
    int k = 1;
    for(auto it = adjacencyList.at(name).cbegin(); it != adjacencyList.at(name).cend(); ++it){
        std::cout << k << ") [" << it->name << ", " << it->weight << "]\n";
        k++;
    }
    int check2 = 0;
    std::cin >> check2;
    if(check2 < 1 || check2 > k){
        throw std::invalid_argument("Please enter a valid argument!");
    }
    Edge e;
    int counter = 1;
    for(auto it = adjacencyList.at(name).cbegin(); it != adjacencyList.at(name).cend(); ++it){ 
        if(counter == check2){
            e.name = it->name;
            e.weight = it->weight;
            GroceryStore::getInstance().deleteEdge(name, e);
            break;
        }  
        counter++;
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


void GroceryStore::deleteMap(){
    adjacencyList.clear();
}

void setupGroceryStore() {
    //we setup the grocery store map at this time as well by adding the same items to the grocery store, as well as the edges that connect them
    GroceryStore::getInstance().addNode("Soda");
    GroceryStore::getInstance().addNode("Cheese");
    GroceryStore::getInstance().addNode("Milk");
    GroceryStore::getInstance().addNode("Cookies");
    GroceryStore::getInstance().addNode("Chips");
    GroceryStore::getInstance().addNode("Juice");
    GroceryStore::getInstance().addNode("Yogurt");
    GroceryStore::getInstance().addNode("Eggs");

    GroceryStore::getInstance().addNode("Enter");
    GroceryStore::getInstance().addNode("A1Left");
    GroceryStore::getInstance().addNode("A1Right");
    GroceryStore::getInstance().addNode("A2Left");
    GroceryStore::getInstance().addNode("A2Right");
    GroceryStore::getInstance().addNode("A3Left");
    GroceryStore::getInstance().addNode("A3Right");
    GroceryStore::getInstance().addNode("Exit");
    //Adding the various edges to the grocery store
    Edge e;
    e.name = "A1Left";
    e.weight = 2;
    GroceryStore::getInstance().addEdge("Enter",e);
    e.name = "A1Right";
    e.weight = 6;
    GroceryStore::getInstance().addEdge("Enter",e);
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Cheese",e);
    e.name = "Cheese";
    e.weight = 5;
    GroceryStore::getInstance().addEdge("Milk",e);
    e.name = "Milk";
    e.weight = 4;
    GroceryStore::getInstance().addEdge("A1Left",e);
    e.name = "A2Left";
    e.weight = 3;
    GroceryStore::getInstance().addEdge("A1Left",e);
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Chips",e);
    e.name = "Cookies";
    e.weight = 4;
    GroceryStore::getInstance().addEdge("Chips",e);
    e.weight = 2;
    GroceryStore::getInstance().addEdge("Soda",e);
    e.name = "A2Right";
    e.weight = 3;
    GroceryStore::getInstance().addEdge("Soda",e);
    GroceryStore::getInstance().addEdge("A1Right",e);
    GroceryStore::getInstance().addEdge("A3Right",e);
    e.name = "Juice";
    e.weight = 5;
    GroceryStore::getInstance().addEdge("A3Right",e);
    e.name = "Yogurt";
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Juice",e);
    e.weight = 3;
    GroceryStore::getInstance().addEdge("Eggs",e);
    e.name = "A3Left";
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Eggs",e);
    e.weight = 3;
    GroceryStore::getInstance().addEdge("A2Left",e);
    e.name = "Exit";
    e.weight = 4;
    GroceryStore::getInstance().addEdge("A3Left",e);
    e.weight = 8;
    GroceryStore::getInstance().addEdge("A3Right",e);
}