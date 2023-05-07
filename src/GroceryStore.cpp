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
    //looping through the whole list
    for(auto it = adjacencyList.cbegin(); it != adjacencyList.cend(); ++it){ //looping through the adjacency list
        std::cout << i << ") " << it->first << "\n";
        i++;
    }
    int check = 0;
    std::cin >> check;
    std::cin.clear();
    //checking for valid argument
    if(check < 1 || check > i){
        throw std::invalid_argument("Please enter a valid argument!");
    }
    //getting the node name
    std::string name = GroceryStore::getInstance().returnNodeName(check);
    int k = 1;
    //looping through again for the other node
    for(auto it = adjacencyList.at(name).cbegin(); it != adjacencyList.at(name).cend(); ++it){
        std::cout << k << ") [" << it->name << ", " << it->weight << "]\n";
        k++;
    }
    int check2 = 0;
    std::cin >> check2;
    //checking for valid argument
    if(check2 < 1 || check2 > k){
        throw std::invalid_argument("Please enter a valid argument!");
    }
    //creating a new edge to store the one we want to delete
    Edge e;
    int counter = 1;
    //looping through the first nodes connected edges
    for(auto it = adjacencyList.at(name).cbegin(); it != adjacencyList.at(name).cend(); ++it){ 
        if(counter == check2){ //checking for the given edge
            e.name = it->name;
            e.weight = it->weight;
            GroceryStore::getInstance().deleteEdge(name, e); //deleting the edge
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

std::map<std::string, std::vector<Edge>> GroceryStore::getTSPMap() {
    if (TSPadjacencyList.size() == 0) updateTSPMap();
    return TSPadjacencyList; //helper function that returns the TSP adjacency list
}

void GroceryStore::printShortestPath(std::vector<Edge> shortest){
    //std::cout << "Entrance --> "; //Will always start at entrance
    for(auto it = shortest.cbegin(); it != shortest.cend(); ++it){ //looping through the shortest path vector
        for(auto i = it->path.cbegin(); i != it->path.cend(); ++i){
            std::cout << *i << "\n";
            std::cout << *i << " --> ";
        }
        // if(it != shortest.cend() - 1) //don't print out the next name if we are at the end
        //     std::cout << it->name << " --> "; //print the next name
    }
    std::cout << "Exit\n";
}


void GroceryStore::deleteMap(){ 
    //deleting whole map for debug purposes
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

void GroceryStore::addItem(ShoppingList& list) {
    float price;
    bool coupon;
    std::string item;
    //getting name of item
    std::cout << "What item would you like to add?\n";
    std::cin >> item;
    //getting price of item
    std::cout << "What is the price of your item? (Must be a number)\n";
    std::cin >> price;
    //getting coupon bool
    std::cout << "Is there a coupon for this item? 1) Yes 0) No)\n";
    std::cin >> coupon;
    ItemNode* node = new ItemNode(item,price,coupon);
    //creating new itemnode
    list.addToPossibleChoices(node);
    //adding to list
    GroceryStore::getInstance().addNode(item);
    //adding to grocery store
}

void GroceryStore::addAisle(){
    std::string name; //getting the name
    std::cout << "What is the name of your aisle?\n";
    std::cin >> name;
    //storing that node
    GroceryStore::getInstance().addNode(name);
}

void GroceryStore::addEdgeMenu(){
    int node;
    int node2;
    std::cout << "Which node would you like connect first?\n";
    //getting first node
    int i = GroceryStore::getInstance().printNodes();
    std::cin >> node;
    if(node < 1 || node > i){
        throw std::invalid_argument("Please enter a valid argument!");
    }
    //getting the name of that node
    std::string nodename = GroceryStore::getInstance().returnNodeName(node);
    std::cout << "Which node would you like to connect to the first node?\n";
    GroceryStore::getInstance().printNodes();
    std::cin >> node2;
    //doing the same for node 2
    if(node2 < 1 || node2 > i){
        throw std::invalid_argument("Please enter a valid argument!");
    }
    else if(node == node2){
        throw std::invalid_argument("Cannot connect the node to itself!"); //we don't want self recurring loops
    }
    //getting node2s name
    std::string nodename2 = GroceryStore::getInstance().returnNodeName(node2);
    float weight; //getting the weight of the edge
    std::cout << "How far apart are they (in steps)?\n";
    std::cin >> weight;
    Edge e;
    e.name = nodename2;
    e.weight = weight; //creating the edge
    GroceryStore::getInstance().addEdge(nodename, e); //adding the edge
}

void GroceryStore::deleteNodeMenu(){
    std::cout << "Which node would you like to delete?\n";
    int node; //getting the node
    int i = GroceryStore::getInstance().printNodes();
    std::cin >> node;
    if(node < 1 || node > i){
        throw std::invalid_argument("Please enter a valid argument!");
    }
    //finding the node name
    std::string nodename = GroceryStore::getInstance().returnNodeName(node);
    //deleting the node
    GroceryStore::getInstance().deleteNode(nodename);
}

struct QueueNode {
    std::string name;
    int distance;
    std::string prev;
};

bool compareQueueNodes(const QueueNode& lhs, const QueueNode& rhs) {
    return lhs.distance > rhs.distance;
}

// FIGURE OUT WHY THE DISTANCES AREN'T CORRECT
void GroceryStore::updateTSPMap() {
    // If TSP adjacency list has already been initialized, then return it.
    // if (TSPadjacencyList.size() > 0) return TSPadjacencyList;

    // Create a map to store the shortest paths from each node to every other node.
    std::map<std::string, std::vector<Edge>> TSP_map;

    // Create a priority queue to store the nodes that have not yet been processed.
    std::priority_queue<QueueNode, std::vector<QueueNode>, decltype(&compareQueueNodes)> pq(&compareQueueNodes);
    // and ones for checking which nodes are still in pq
    std::priority_queue<QueueNode, std::vector<QueueNode>, decltype(&compareQueueNodes)> pq_check(&compareQueueNodes);
    std::priority_queue<QueueNode, std::vector<QueueNode>, decltype(&compareQueueNodes)> pq_check2(&compareQueueNodes);

    // SOURCES LOOP
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it) {
        if (it->first != "A1Left" && it->first != "A1Right" && it->first != "A2Left" && it->first != "A2Right" && it->first != "A3Left" && it->first != "A3Right") {
            std::cout << "SOURCE it->first: " << it->first << "\n";
            // Reset pq for each iteration
            pq = std::priority_queue<QueueNode, std::vector<QueueNode>, decltype(&compareQueueNodes)>(&compareQueueNodes);

            // Initialize distances and prev
            std::map<std::string, int> distance;
            std::map<std::string, std::string> prev;

            // Iterate over all of the nodes in the graph to set up the priority queue.
            for (auto it2 = adjacencyList.begin(); it2 != adjacencyList.end(); ++it2) {
                std::cout << "TO it2->first: " << it2->first << "\n";
                std::string node = it2->first;
                // If the node is not one of the excluded nodes, then add it to the priority queue.
                //if (node != "A1Left" && node != "A1Right" && node != "A2Left" && node != "A2Right" && node != "A3Left" && node != "A3Right") {
                QueueNode qn;
                qn.name = node;
                qn.prev = "";
                if (node == it->first) {
                    qn.distance = 0;
                    distance[node] = 0;
                }
                else {
                    // SOMETHINGS WRONG
                    qn.distance = INT_MAX;
                    distance[node] = INT_MAX;
                }
                prev[node] = "";
                pq.push(qn); // PROBLEM?
            }
            std::cout << "DONE WITH TO"<< "\n";

            // While the priority queue is not empty, do the following:
            while (!pq.empty()) {
                // Pop the node with the lowest distance from the priority queue.
                QueueNode current_node = pq.top();
                pq.pop();
                std::cout << "current node: " << current_node.name << "\n";

                // If the node has already been processed, then skip it.
                // if (TSP_map.find(current_node.name) != TSP_map.end()) continue;

                // // Create a vector to store the shortest paths from the current node to all other nodes.
                // std::vector<Edge> shortest_paths;

                // Iterate over all of the edges in the graph.
                // PROBLEM WITH PQS
                for (Edge edge : adjacencyList[current_node.name]) {
                    std::cout << "edge: " << edge.name << "\n";
                    pq_check = std::priority_queue<QueueNode, std::vector<QueueNode>, decltype(&compareQueueNodes)>(&compareQueueNodes);
                    bool neighborStilInPQ = false;
                    while (!pq.empty()) {
                        if (pq.top().name == edge.name) {
                            neighborStilInPQ = true;
                            break;
                        }
                        pq_check.push(pq.top());
                        pq.pop();
                    }

                    while (!pq_check.empty()) {
                        pq.push(pq_check.top());
                        pq_check.pop();
                    }

                    if (!neighborStilInPQ) continue;

                    // PROBLEM, wrapping back around
                    int alt_distance = current_node.distance + edge.weight;
                    if (alt_distance < distance[edge.name]) {
                        distance[edge.name] = alt_distance;
                        prev[edge.name] = current_node.name;
                        pq_check2 = std::priority_queue<QueueNode, std::vector<QueueNode>, decltype(&compareQueueNodes)>(&compareQueueNodes);
                        while (!pq.empty()) {
                            if (pq.top().name == edge.name) {
                                QueueNode match_node = pq.top();
                                pq.pop();
                                match_node.distance = alt_distance;
                                match_node.prev = current_node.name;
                                pq.push(match_node);
                                break;
                            }
                            pq_check2.push(pq.top());
                            pq.pop();
                        }

                        while (!pq_check2.empty()) {
                            pq.push(pq_check2.top());
                            pq_check2.pop();
                        }
                    }
                }
            }
        
            // insert into TSP_map
            // PROBLEM WITH PATHS?
            for (auto path_it = adjacencyList.begin(); path_it != adjacencyList.end(); ++path_it) {
                std::string node = path_it->first;
                if (node != it->first && node != "A1Left" && node != "A1Right" && node != "A2Left" && node != "A2Right" && node != "A3Left" && node != "A3Right") {
                    int path_distance = distance[node];
                    std::vector<std::string> path;
                    while (prev[node].length() > 0) {
                        node = prev[node];
                        path.insert(path.begin(), node);
                    }
                    Edge path_edge;
                    path_edge.weight = path_distance;
                    path_edge.name = path_it->first;
                    path_edge.path = path;
                    TSP_map[it->first].push_back(path_edge);
                }
            }
        }
    }

    // For each shortest path in TSP map node, get the paths both ways.
    for (auto it = TSP_map.begin(); it != TSP_map.end(); ++it) {
        std::string node = it->first;
        for (Edge edge : it->second) {
            std::vector<std::string> path = edge.path;
            std::reverse(path.begin(), path.end());
            Edge path_edge;
            path_edge.weight = edge.weight;
            path_edge.name = node;
            path_edge.path = path;
            TSP_map[edge.name].push_back(path_edge);
        }
    }

    // Print all paths
    for (auto it = TSP_map.begin(); it != TSP_map.end(); ++it) { 
        std::cout << it->first << ":\n"; 
        for (auto p : it->second) {
            std::cout << "  [";
            std::cout << p.name << ": ";
            std::cout << p.weight << ", ";
            std::cout << it->first << ", ";
            for (std::string node : p.path) {
                std::cout << node << ", ";
            }
            std::cout << p.name;
            std::cout << "]\n";
        }
        std::cout << "\n";
    }

    // Store TSP map in grocery store.
    TSPadjacencyList = TSP_map;

    // Return the TSP map.
    // return TSP_map;
}