#include "../include/GroceryStore.hpp"
#include "../include/ShoppingList.hpp"
#include "../include/Context.hpp"
#include "../include/SearchStrategy.hpp"
#include "../include/BruteForceStrategy.hpp"
#include "../include/NearestNeighborStrategy.hpp"
#include "../include/TwoOptStrategy.hpp"
//Function to handle various menu options for our main
void menuOptions(int option, ShoppingList& list) {
    //This switch handles the first menu options and the various possiblities
    switch(option) {
        case '1':
            list.addItem();
            break;
        case '2':
            list.removeItem();
            break;
        case '3':
            list.viewCurrentList();
            break;
        case '4': {
            //For our search strategies, we need to initalize various variables
            char search_option = '0';
            bool cancel = false;
            Context k;
            SearchStrategy* newStrategy;
            //Add an exit node to our list to be included in the search
            list.getList().push_back(new ItemNode("Exit",-1,false));
            std::cout << "Now please select an option below:\n1)Use Brute Force Algorithm\n2)Use Nearest Neighbor Algorithm\n3)Use 2-Opt Algorithm\n4)Choose Algorithm for Me!\n5)Cancel" << std::endl;
            try
            {
                std::cin >> search_option;
                if(!isdigit(search_option)) {
                    throw std::invalid_argument("Please enter a valid argument!");
                }
                //second switch for the various search options
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
                        //Since the various strategies are better for certain sizes, the size will decide which strategy to pick
                        std::vector<ItemNode*> shopList = list.getList();
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
                    std::vector<Edge> path = k.strategy(list);
                    // print path when done
                    GroceryStore::getInstance().printShortestPath(path);
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
        }
        case '5':
            std::cout << "Thank you for using StoreMapper!" << std::endl;
            break;
        default:
            throw std::invalid_argument("Invalid Selection! Please try again.");
            break;
    }
}

int main(int argv, char** argc) {
    //create list to be used
    ShoppingList list;
    std::cout << "Welcome to StoreMapper!" << std::endl;
    char option = '0';
    std::cout << std::fixed<< std::setprecision(2);
    //basic loop used to control program flow
    while(option != '5') {
        std::cout << "Please select an option below:\n1)Add Item to List\n2)Remove Item from List\n3)View Current Cart\n4)View Path to Items\n5)Exit" << std::endl;
        try
        {
            //error handling that will check to make sure that the given argument is a number not a character
            std::cin >> option;
            if(!isdigit(option)) {
                throw std::invalid_argument("Please enter a valid argument!");
            }
            menuOptions(option,list);
        }
        catch(const std::invalid_argument &e) {
            std::cerr << e.what() << '\n';
            //if we get an invalid argument, we need to flush cin to allow it to be used again
            std::cin.clear();
            std::cin.ignore(option, '\n');
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

    }
}
