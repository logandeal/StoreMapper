#include "../include/GroceryStore.hpp"
#include "../include/ShoppingList.hpp"
#include "../include/Context.hpp"
#include "../include/SearchStrategy.hpp"
#include "../include/BruteForceStrategy.hpp"
#include "../include/NearestNeighborStrategy.hpp"
#include "../include/TwoOptStrategy.hpp"

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
            char search_option = '0';
            bool cancel = false;
            Context k;
            SearchStrategy* newStrategy;
            std::cout << "Now please select an option below:\n1)Use Brute Force Algorithm\n2)Use Nearest Neighbor Algorithm\n3)Use 2-Opt Algorithm\n4)Choose Algorithm for Me!\n5)Cancel" << std::endl;
            try
            {
                std::cin >> search_option;
                if(!isdigit(search_option)) {
                    throw std::invalid_argument("Please enter a valid argument!");
                }
                switch(search_option) {
                    case '1': {
                        newStrategy = new BruteForceStrategy();
                        k.setStrategy(newStrategy);
                        delete newStrategy;
                        break;
                    }
                    case '2': {
                        newStrategy = new NearestNeighborStrategy();
                        k.setStrategy(newStrategy);
                        delete newStrategy;
                        break;
                    }
                    case '3': {
                        newStrategy = new TwoOptStrategy();
                        k.setStrategy(newStrategy);
                        delete newStrategy;
                        break;
                    }
                    case '4': {
                        std::vector<ItemNode*> shopList = list->getList();
                        if (shopList.size() < 10) {
                            newStrategy = new BruteForceStrategy();
                        } else if (shopList.size() < 20) {
                            newStrategy = new NearestNeighborStrategy();
                        } else {
                            newStrategy = new TwoOptStrategy();
                        }
                        k.setStrategy(newStrategy);
                        delete newStrategy;
                        break;
                    }
                    case '5': {
                        cancel = true;
                        break;
                    }
                }
                if (cancel) {
                    break;
                } else {
                    std::vector<Edge> path = k.strategy(*list);
                    // print path!!!!
                }
            }
            catch(const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                std::cin.clear();
                std::cin.ignore(search_option, '\n');
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
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
