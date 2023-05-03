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
                        if (shopList.size() < 10) {
                            k.setStrategy(std::make_unique<BruteForceStrategy>());
                        } else if (shopList.size() < 20) {
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
                    break;
                } else {
                    std::vector<Edge> path = k.strategy(list);
                    // print path when done
                    GroceryStore::getInstance().printShortestPath(path);
                    list.cleanupAfterSearch();
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
        case '5': {
            //doing this could lead to unexpected results, so the user must know what they are doing
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
                            //only adding to grocery store
                            else if(search2 == '2'){
                                std::string name;
                                std::cout << "What is the name of your aisle?\n";
                                std::cin >> name;
                                GroceryStore::getInstance().addNode(name);
                            }
                            //adding edge in grocery store
                            else if(search2 == '3'){
                                int node;
                                int node2;
                                std::cout << "Which node would you like connect first?\n";
                                int i = GroceryStore::getInstance().printNodes();
                                std::cin >> node;
                                if(node < 1 || node > i){
                                    throw std::invalid_argument("Please enter a valid argument!");
                                }
                                std::string nodename = GroceryStore::getInstance().returnNodeName(node);
                                std::cout << "Which node would you like to connect to the first node?\n";
                                GroceryStore::getInstance().printNodes();
                                std::cin >> node2;
                                if(node2 < 1 || node2 > i){
                                    throw std::invalid_argument("Please enter a valid argument!");
                                }
                                else if(node == node2){
                                    throw std::invalid_argument("Cannot connect the node to itself!");
                                }
                                std::string nodename2 = GroceryStore::getInstance().returnNodeName(node2);
                                float weight;
                                std::cout << "How far apart are they (in steps)?\n";
                                std::cin >> weight;
                                Edge e;
                                e.name = nodename2;
                                e.weight = weight;
                                GroceryStore::getInstance().addEdge(nodename, e);
                            }
                            else if(search2 == '4'){
                                GroceryStore::getInstance().getEdge();
                            }
                            else if(search2 == '5'){
                                std::cout << "Which node would you like to delete?\n";
                                int node;
                                int i = GroceryStore::getInstance().printNodes();
                                std::cin >> node;
                                if(node < 1 || node > i){
                                    throw std::invalid_argument("Please enter a valid argument!");
                                }
                                std::string nodename = GroceryStore::getInstance().returnNodeName(node);
                                GroceryStore::getInstance().deleteNode(nodename);
                            }
                            search_option = '0';
                            std::cout << "Would you like to continue?\n1)Yes 2)No\n";
                            std::cin >> search_option;
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

int main(int argv, char** argc) {
    //create list to be used
    ShoppingList list;
    setupGroceryStore();
    std::cout << "Welcome to StoreMapper!" << std::endl;
    char option = '0';
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

