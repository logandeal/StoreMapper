// Good for small n

#include "../include/Dijkstra2DStrategy.hpp"

// struct QueueNode {
//     std::string name;
//     int bitmask;
//     int weight;
//     bool operator > (const QueueNode& other) const {
//         return weight > other.weight;
//     }
// };

// int getNodeIndex(const std::string& name, std::map<std::string, int>& nodeMap) {
//     auto it = nodeMap.find(name);
//     if (it == nodeMap.end()) {
//         nodeMap[name] = nodeMap.size();
//         return nodeMap[name] - 1;
//     } else {
//         return it->second;
//     }
// }

// std::string getNodeName(int nodeIndex, const std::map<std::string, int>& nodeMap) {
//     for (const auto& p : nodeMap) {
//         if (p.second == nodeIndex) {
//             return p.first;
//         }
//     }
//     return ""; // return an empty string if the index is out of bounds
// }

// std::vector<Edge> Dijkstra2DStrategy::search(ShoppingList &shoppingList) {
//     // get shopping list
//     std::vector<ItemNode*> shopListItemNodes = shoppingList.getList();
//     // get shopping list names
//     std::vector<std::string> shopList;
//     for (ItemNode* itemNodePtr : shopListItemNodes) {
//         shopList.push_back(itemNodePtr->getName());
//     }
//     // path to return
//     std::vector<Edge> path;
//     // number of items
//     int m = std::min((int)shopList.size(), 10);
//     std::cout << "m = " << m << std::endl;
//     for (int i = 0; i < m; i++) {
//         std::cout << shopList[i] << std::endl;
//     }
//     // size of grocery store
//     // int MAXN = GroceryStore::getInstance().getMap().size();
//     // std::cout << "MAXN = " << MAXN << std::endl;

//     // get the adjacency list
//     std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getMap();

//     // distance and parent and conversion map
//     std::map<std::string, int> nodeMap;
//     int MAXN = 0;
//     for (const auto& p : adjList) {
//         std::string u = p.first;
//         getNodeIndex(u, nodeMap);
//         for (const auto& e : p.second) {
//             std::string v = e.name;
//             getNodeIndex(v, nodeMap);
//         }
//     }
//     MAXN = nodeMap.size();

//     int distance[MAXN][1 << m];
//     int parent[MAXN][1 << m];


//     // define enter and exit names
//     std::string enter_name = shopList.front();
//     std::string exit_name = shopList.back();

//     // remove enter and exit from shopList
//     // shopList.erase(shopList.begin());
//     // shopList.pop_back();

//     memset(distance, 0x3f, sizeof(distance));
//     memset(parent, -1, sizeof(parent));
//     std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<QueueNode>> Q;

//     int enter = getNodeIndex(enter_name, nodeMap);
//     int exit = getNodeIndex(exit_name, nodeMap);
//     nodeMap[enter_name] = enter;
//     nodeMap[exit_name] = exit;

//     distance[enter][0] = 0;
//     Q.push({enter_name, 0, 0});

//     while (!Q.empty()) {
//         QueueNode u = Q.top();
//         Q.pop();

//         if (u.weight > distance[getNodeIndex(u.name, nodeMap)][u.bitmask]) {
//             continue;
//         }

//         for (Edge neighbor : adjList[u.name]) {
//             std::string v = neighbor.name;
//             int newBitmask = u.bitmask | (1 << getNodeIndex(v, nodeMap));
//             getNodeIndex(v, nodeMap); // update nodeMap with the new node

//             int newWeight = u.weight + neighbor.weight;
//             // if a shorter path to v is found, update distance[v][newBitmask] and parent[v][newBitmask]
//             if (newWeight < distance[getNodeIndex(v, nodeMap)][newBitmask]) {
//                 distance[getNodeIndex(v, nodeMap)][newBitmask] = newWeight;
//                 parent[getNodeIndex(v, nodeMap)][newBitmask] = getNodeIndex(u.name, nodeMap);

//                 if (v == exit_name) {
//                     break;
//                 }
//             }
//         }
//     }

//     // if there is no path from the enter_name to the exit_name, return an empty path
//     if (distance[getNodeIndex(exit_name, nodeMap)][(1 << m) - 1] == 0x3f) {
//         std::cout << "No path found" << std::endl;
//         return path;
//     }

//     // reconstruct the path from the exit_name to the enter_name
//     int currentNode = exit;
//     int currentBitmask = (1 << m) - 1;

//     std::map<std::string, int> nodeMapCopy = std::move(nodeMap);

//     while (currentNode != enter) {
//         int parentNode = parent[currentNode][currentBitmask];
//         Edge e;
//         e.name = getNodeName(parentNode, nodeMapCopy);
//         e.weight = distance[parentNode][currentBitmask] - distance[currentNode][currentBitmask];
//         path.insert(path.begin(), e);
//         currentBitmask ^= (1 << getNodeIndex(getNodeName(currentNode, nodeMapCopy), nodeMapCopy));
//         currentNode = parentNode;
//         if (currentBitmask < 0 || currentBitmask >= (1 << m)) {
//             std::cerr << "Error: currentBitmask out of bounds: " << currentBitmask << std::endl;
//             std::exit(1);
//         }
//     }

//     std::cout << "length of path = " << path.size() << std::endl;

//     // reverse the path so that it starts at the enter_name
//     std::reverse(path.begin(), path.end());

//     // return the path
//     return path;
// }


Dijkstra2DStrategy::~Dijkstra2DStrategy() {};
//

// std::vector<Edge> BruteForceStrategy::search(ShoppingList &shoppingList) {
//     // get shopping list
//     std::vector<ItemNode*> shopList = shoppingList.getList();

//     // path to return
//     std::vector<Edge> path;

//     // number of items
//     const int n = shoppingList.getList().size();

//     // get the adjacency list
//     std::map<std::string, std::vector<Edge>> adjList = GroceryStore::getInstance().getMap();
    
//     int distance = INT_MAX;
//     std::priority_queue<QueueNode> q;

//     QueueNode enter;
//     enter.name = "Enter";
//     enter.bitmask = 0;
//     enter.cost = 0;

//     q.push(enter);a

//     // initialize the items array with the names of the items
//     std::vector<std::string> items(n); // names of items
//     for (int i = 0; i < n; i++) {
//         items[i] = shopList[i]->getName(); // includes start and end
//     }

//     int ans = INT_MAX; // start total distance at max int
//     do {
//         // calculate the distance of the current permutation
//         int curDist = 0;
//         std::vector<Edge> currentPath;
//         // loop through all the items in current permutation
//         for (int i = 1; i < n; i++) {
//             // compare the current and next item
//             // ONLY DO THIS FOR THE NON FIRST AND LAST ITEMS
//             // ADD ISLE EDGES!
//             // USE GROCERY STORE NODES
//             // REFORMAT ALGORITHM, bc if you add cookies it's messed up
//             // SHORTEST PATH AND THEN COMPARE
//             std::string name_u = items[i-1], name_v = items[i]; // compare two items 
//             // find the edge weight between the current and next item
//             int w = 0;
//             for (Edge neighbor : adjList[name_u]) {
//                 if (neighbor.name == name_v) {
//                     w = neighbor.weight;
//                     // add edge to path
//                     currentPath.push_back(neighbor);
//                     break;
//                 }
//             }
//             // add distance
//             curDist += w;
//         }
//         // std::string name_u = items[n-1], name_v = items[0];
//         // // find the edge weight between the last and first items
//         // int w = 0;
//         // for (Edge neighbor : adjList[name_u]) {
//         //     if (neighbor.name == name_v) {
//         //         w = neighbor.weight;
//         //         break;
//         //     }
//         // }
//         // curDist += w;
//         if (curDist < ans) {
//             path.clear();
//             path.insert(path.begin(), currentPath.begin(), currentPath.end());
//             ans = curDist;
//         }
//         // ans = std::min(ans, curDist);
//     } while (next_permutation(items.begin(), items.end()));

//     return path;
// };

// // find the shortest path that visits all the nodes in mustVisitNodes using 2D Dijkstra's algorithm
// int findShortestPath(adj_list adjList, int start, int end, set<int> mustVisitNodes) {
//     // initialize the distances and the queue
//     int n = adjList->size();
//     int distance[MAX_NODES][1 << n];
//     fill_n(&distance[0][0], MAX_NODES * (1 << n), numeric_limits<int>::max());
//     distance[start][0] = 0;
//     priority_queue<node> q;
//     q.push(createNode(start, 0, 0));

//     // Dijkstra's algorithm
//     while (!q.empty()) {
//         node u = q.top();
//         q.pop();
//         if (u.id == end && u.bitmask == (1 << mustVisitNodes.size()) - 1) {
//             return distance[u.id][u.bitmask];
//         }
//         if (u.distance != distance[u.id][u.bitmask]) {
//             continue;
//         }
//         for (pair<int, int> v : adjList[u.id]) {
//             int vid = v.first;
//             int newBitmask = u.bitmask;
//             if (mustVisitNodes.find(vid) != mustVisitNodes.end()) {
//                 newBitmask |= (1 << distance(mustVisitNodes.begin(), mustVisitNodes.find(vid)));
//             }
//             int newDistance = u.distance + v.second;
//             if (newDistance < distance[vid][newBitmask]) {
//                 distance[vid][newBitmask] = newDistance;
//                 q.push(createNode(vid, newBitmask, newDistance));
//             }
//         }
//     }

//     // if we reach this point, there is no path that satisfies the constraints
//     return -1;
// }

// std::vector<Edge> findShortestPath(std::map<std::string, std::vector<Edge>> adjList, std::string start, std::string end, std::set<std::string> mustVisitNodes) {
//     // initialize the distances and the queue
//     int n = mustVisitNodes.size() + 2;
//     int distance[MAX_NODES][1 << n];
//     fill_n(&distance[0][0], MAX_NODES * (1 << n), numeric_limits<int>::max());
//     distance[start][0] = 0;
//     priority_queue<node> q;
//     q.push(createNode(start, 0, 0));

//     // Dijkstra's algorithm
//     while (!q.empty()) {
//         node u = q.top();
//         q.pop();
//         if (u.id == end && u.bitmask == (1 << mustVisitNodes.size()) - 1) {
//             std::vector<Edge> path;
//             while (u.previous != NULL) {
//                 path.push_back(u.edge);
//                 u = *u.previous;
//             }
//             reverse(path.begin(), path.end());
//             return path;
//         }
//         if (u.distance != distance[u.id][u.bitmask]) {
//             continue;
//         }
//         for (Edge v : adjList[u.id]) {
//             std::string vid = v.name;
//             int newBitmask = u.bitmask;
//             if (mustVisitNodes.find(vid) != mustVisitNodes.end()) {
//                 newBitmask |= (1 << distance(mustVisitNodes.begin(), mustVisitNodes.find(vid)));
//             }
//             int newDistance = u.distance + v.weight;
//             if (newDistance < distance[vid][newBitmask]) {
//                 distance[vid][newBitmask] = newDistance;
//                 node new_node = createNode(vid, newBitmask, newDistance);
//                 new_node.previous = new node(u);
//                 new_node.edge = v;
//                 q.push(new_node);
//             }
//         }
//     }

//     // if we reach this point, there is no path that satisfies the constraints
//     return std::vector<Edge>();
// }
