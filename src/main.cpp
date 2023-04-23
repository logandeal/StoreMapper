#include "../include/GroceryStore.hpp"
#include "../include/ShoppingList.hpp"

void menuOptions(int option, ShoppingList* list) {
    switch(option) {
        case '1':
            list->addItem();
            break;
        case '2':
            list->removeItem();
            break;
        case '3':
            list->viewCurrentList();
            break;
        case '4':
            //ADD SEARCH ALGORITHMS HERE
            break;
        case '5':
            std::cout << "Thank you for using StoreMapper!" << std::endl;
            break;
        default:
            throw std::invalid_argument("Invalid Selection! Please try again.");
            break;
    }
}


int main(int argv, char** argc) {
    //will need to initalize a grocery store instance here (singleton)
    ShoppingList* list = new ShoppingList();

    std::cout << "Welcome to StoreMapper!" << std::endl;

    char option = '0';
    while(option != '5') {
        std::cout << "Please select an option below:\n1)Add Item to List\n2)Remove Item from List\n3)View Current Cart\n4)View Path to Items\n5)Exit" << std::endl;
        try
        {
            std::cin >> option;
            if(!isdigit(option)) {
                throw std::invalid_argument("Please enter a valid argument!");
            }
            menuOptions(option,list);
        }
        catch(const std::invalid_argument &e) {
            std::cerr << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(option, '\n');
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

    }
    delete list;
}
