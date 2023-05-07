#include "../include/SearchStrategy.hpp"

// print each edge name in the path in order
void printPathInOrder(const std::vector<Edge> path) {
    for (Edge e : path) {
        std::cout << e.name << " ";
    }
    std::cout << std::endl;
}