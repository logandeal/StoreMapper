#include "../include/GroceryStore.hpp"


int main(int argv, char** argc) {
    //will need to initalize a grocery store instance here (singleton)
    

    std::cout << "Welcome to StoreMapper!" << std::endl;

    int option = 0;
    while(option != -1) {
        std::cout << "Please select an option below:\n1) Add Item to List\n2)Remove Item from List\n3)View Path to Items\n4)Exit" << std::endl;
        std::cin >> option;
    }
}
