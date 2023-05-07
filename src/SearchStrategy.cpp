#include "../include/SearchStrategy.hpp"

// print each edge name in the path in order
void SearchStrategy::printPathInOrder(const std::vector<Edge> path) {
    for (Edge e : path) {
        std::cout << e.name << " ";
    }
    std::cout << std::endl;
}