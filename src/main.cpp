#include "../include/GroceryStore.hpp"
#include "../include/ShoppingList.hpp"
#include "../include/Context.hpp"
#include "../include/SearchStrategy.hpp"
#include "../include/BruteForceStrategy.hpp"
#include "../include/NearestNeighborStrategy.hpp"
#include "../include/TwoOptStrategy.hpp"
//Function to handle various menu options for our main

void strategyMenuOption(ShoppingList& list);
void GroceryStoreMenuOptions(int option ,ShoppingList& list);
void menuOptions(int option, ShoppingList& list);

int main(int argv, char** argc) {
    //create list to be used
    ShoppingList list;
    //Use the files to setup the grocery store with default nodes and edges
    setupGroceryStoreNodes();
    setupGroceryStoreEdges();
    std::cout << "Welcome to StoreMapper!" << std::endl;
    char option = '0';
    //set the precision of floats to 2 to have prices look correct
    std::cout << std::fixed<< std::setprecision(2);
    //basic loop used to control program flow
    while(option != '6') {
        std::cout << "Please select an option below:\n1) Add Item to List\n2) Remove Item from List\n3) View Current Cart\n4) View Path to Items\n5) Change Grocery Store Layout\n6) Exit" << std::endl;
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

void menuOptions(int option, ShoppingList& list){
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
            strategyMenuOption(list);
            break; //For our search strategies, we need to initalize various variables
        }
        case '5': {
            //doing this could lead to unexpected results, so the user must know what they are doing
            GroceryStoreMenuOptions(option, list);
            break;
        }
        case '6':
            std::cout << "Thank you for using StoreMapper!" << std::endl;
            break;
        default:
            throw std::invalid_argument("Invalid Selection! Please try again.");
            break;
    }
}

void strategyMenuOption(ShoppingList& list){
    char search_option = '0';
    bool cancel = false;
    Context k;
    std::cout << "Now please select an option below:\n1) Use Brute Force Algorithm\n2) Use Nearest Neighbor Algorithm\n3) Use 2-Opt Algorithm\n4) Choose Algorithm for Me!\n5) Cancel" << std::endl;
    try
    {
        std::cin >> search_option;
        if(!isdigit(search_option)) {
            throw std::invalid_argument("Please enter a valid argument!");
        }
        //second switch for the various search options
        switch(search_option) {
            case '1': {
                //setup for search by adding nodes for beginning and end
                list.setupForSearch();
                k.setStrategy(std::make_unique<BruteForceStrategy>());
                break;
            }
            case '2': {
                //setup for search by adding nodes for beginning and end
                list.setupForSearch();
                k.setStrategy(std::make_unique<NearestNeighborStrategy>());
                break;
            }
            case '3': {
                //setup for search by adding nodes for beginning and end
                list.setupForSearch();
                k.setStrategy(std::make_unique<TwoOptStrategy>());
                break;
            }
            case '4': {
                //setup for search by adding nodes for beginning and end
                list.setupForSearch();
                //Since the various strategies are better for certain sizes, the size will decide which strategy to pick
                std::vector<ItemNode*> shopList = list.getList();
                if (shopList.size() < 5) {
                    k.setStrategy(std::make_unique<BruteForceStrategy>());
                } else if (shopList.size() < 10) {
                    k.setStrategy(std::make_unique<NearestNeighborStrategy>());
                } else {
                    k.setStrategy(std::make_unique<TwoOptStrategy>());
                }
                break;
            }
            case '5': {
                cancel = true;
                break;
            }
        }
        if (cancel) {
            return;
        } else {
            try {
                // perform the search
                std::vector<Edge> path = k.strategy(list);
                // print path when done
                GroceryStore::getInstance().printShortestPath(path);
                list.cleanupAfterSearch();
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << '\n';
                list.cleanupAfterSearch();
            } catch (const std::bad_alloc& e) {
                std::cerr << e.what() << '\n';
                list.cleanupAfterSearch();
            }
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
}

void GroceryStoreMenuOptions(int option, ShoppingList& list){
    std::cout << "WARNING! IF YOU CHANGE THE GROCERY STORE MAPPING, THE SEARCH MAY FAIL AND LEAD TO UNEXPECTED RESULTS!\nONLY ADMINISTRATORS SHOULD DO THIS\nMAKE SURE THE STORE IS WELL LAID OUT!\nARE YOU SURE YOU WANT TO CONTINUE?\n1) Yes, 2) No\n";
    char search_option = '0';
    try {
        std::cin >> search_option;
        if(!isdigit(search_option)) {
            throw std::invalid_argument("Please enter a valid argument!");
        }
        switch(search_option){
            case '1':{
                while(true){
                    char search2 = '0';
                    //getting the users input
                    std::cout << "What would you like to change?\n1) Add Item\n2) Add Aisle\n3) Add Path Between Two Nodes\n4) Remove Path Between Two Nodes (May cause unexpected behavior)\n5) Remove Node (May cause unexpected behavior)\n6) Exit\n";
                    std::cin >> search2;
                    //exit case
                    if(search2 == '6'){
                        break;
                    }
                    //adding itemnode, this adds to both the grocery store and the shopping list possibilities
                    else if(search2 == '1'){
                        GroceryStore::getInstance().addItem(list);
                    }
                    //only adding to grocery store
                    else if(search2 == '2'){
                        GroceryStore::getInstance().addAisle();
                    }
                    //adding edge in grocery store
                    else if(search2 == '3'){
                        GroceryStore::getInstance().addEdgeMenu();
                    }
                    //deleting edge from grocery store
                    else if(search2 == '4'){
                        GroceryStore::getInstance().getEdge();
                    }
                    //deleting node from grocery store
                    else if(search2 == '5'){
                        GroceryStore::getInstance().deleteNodeMenu();
                    }
                    search_option = '0';
                    std::cout << "Would you like to continue?\n1)Yes 2)No\n";
                    std::cin >> search_option;
                    //invalid argument
                    if(!isdigit(search_option)) {
                        throw std::invalid_argument("Please enter a valid argument!");
                    }
                    else if(search_option != '1' && search_option != '2'){
                        std::cout << "Invalid selection! Try again later!\n";
                        break;
                    }
                    else if(search_option == '1'){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                break;
            }
            case '2': {
                break;
            } 
            default:{
                throw std::invalid_argument("Invalid Selection! Please try again.");
                break;
            }       
        }
    }
    catch(const std::invalid_argument &e) {
        std::cerr << e.what() << '\n';
        //if we get an invalid argument, we need to flush cin to allow it to be used again
        std::cin.clear();
        std::cin.ignore(option, '\n');
    }
}