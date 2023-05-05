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

void setupGroceryStoreNodes() {
    //we setup the grocery store map at this time by adding the same items to the grocery store that we created in the shopping list, as well as the edges that connect them
    std::ifstream node_file;
    try
    {
        //open up the node setup file
        node_file.open("storenodesetup.txt");
        if(!node_file) {
            throw std::ios_base::failure("Cannot open file!");       
        }
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    std::string data = "";
    //parse through the file until we reach the end
    while(getline(node_file,data)) {
        //Add nodes to the singleton grocery store with the given string from the file
        GroceryStore::getInstance().addNode(data);
        //Since the data is pushed back on data for each line, we reset data to make sure that each line is being read
        //by itself
        data = "";
    }
    //Close the file when we are done to avoid memory leaks
    node_file.close();
}
void setupGroceryStoreEdges() {
    //Adding the various edges to the grocery store
    std::ifstream edge_file;
    try
    {
        //open up the edge setup file
        edge_file.open("storeedgesetup.csv");
        if(!edge_file) {
            throw std::ios_base::failure("Cannot open file!");       
        }
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    Edge e;
    std::string edge_string = "";
    //getting each line of the csv which holds one edge, represented by the two nodes connecting it and weight
    while(getline(edge_file,edge_string)) {
        //Using a stringstream to parse each line of the CSV
        std::istringstream s(edge_string);
        //Variables that will hold the edge statistics
        std::string node1 = "";
        std::string node2 = "";
        std::string weight = "";
        //Get each edge variable, separated by a comma delimeter
        getline(s,node1, ',');
        getline(s,weight,',');
        getline(s,node2,',');
        e.name = node1;
        e.weight = std::stof(weight);
        //create the edge in the singleton grocery store
        GroceryStore::getInstance().addEdge(node2,e);
    }
}