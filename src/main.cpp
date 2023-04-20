#include "../include/GroceryStore.hpp"

int main(void) {
    Edge e;
    e.name = "Eggs";
    e.weight = 2;
    GroceryStore::getInstance().addNode("Milk");
    GroceryStore::getInstance().addNode("Eggs");
    GroceryStore::getInstance().addNode("Cookies");
    GroceryStore::getInstance().addNode("Sauce");

    GroceryStore::getInstance().addEdge("Milk", e);
    e.name = "Sauce";
    e.weight = 10;
    GroceryStore::getInstance().addEdge("Eggs", e);
    e.weight = 4;
    GroceryStore::getInstance().addEdge("Milk", e);
    e.weight = 3;
    e.name = "Cookies";
    GroceryStore::getInstance().addEdge("Sauce", e);
    e.weight = 200;
    e.name = "Milk";
    GroceryStore::getInstance().addEdge("Cookies", e);


    GroceryStore::getInstance().printMap();
    std::cout << std::endl;

    GroceryStore::getInstance().deleteNode("Sauce");
    GroceryStore::getInstance().printMap();

    std::cout << std::endl;
    GroceryStore::getInstance().deleteEdge("Cookies", e);
    GroceryStore::getInstance().printMap();
}