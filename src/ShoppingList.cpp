#include "../include/ShoppingList.hpp"

ShoppingList::ShoppingList() {
    possiblechoices.push_back(new ItemNode("Soda",10,false));
    possiblechoices.push_back(new ItemNode("Cheese",3.4,false));
    possiblechoices.push_back(new ItemNode("Milk",3.99,true));
    possiblechoices.push_back(new ItemNode("Cookies",4.29,false));
    possiblechoices.push_back(new ItemNode("Chips",2.49,false));
    possiblechoices.push_back(new ItemNode("Juice",1.99,false));
    possiblechoices.push_back(new ItemNode("Yogurt",0.59,true));
    possiblechoices.push_back(new ItemNode("Eggs",5,false));

    GroceryStore::getInstance().addNode("Soda");
    GroceryStore::getInstance().addNode("Cheese");
    GroceryStore::getInstance().addNode("Milk");
    GroceryStore::getInstance().addNode("Cookies");
    GroceryStore::getInstance().addNode("Chips");
    GroceryStore::getInstance().addNode("Juice");
    GroceryStore::getInstance().addNode("Yogurt");
    GroceryStore::getInstance().addNode("Eggs");

    GroceryStore::getInstance().addNode("Enter");
    GroceryStore::getInstance().addNode("A1Left");
    GroceryStore::getInstance().addNode("A1Right");
    GroceryStore::getInstance().addNode("A2Left");
    GroceryStore::getInstance().addNode("A2Right");
    GroceryStore::getInstance().addNode("A3Left");
    GroceryStore::getInstance().addNode("A3Right");
    GroceryStore::getInstance().addNode("Exit");

    Edge e;
    e.name = "A1Left";
    e.weight = 2;
    GroceryStore::getInstance().addEdge("Enter",e);
    e.name = "A1Right";
    e.weight = 6;
    GroceryStore::getInstance().addEdge("Enter",e);
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Cheese",e);
    e.name = "Cheese";
    e.weight = 5;
    GroceryStore::getInstance().addEdge("Milk",e);
    e.name = "Milk";
    e.weight = 4;
    GroceryStore::getInstance().addEdge("A1Left",e);
    e.name = "A2Left";
    e.weight = 3;
    GroceryStore::getInstance().addEdge("A1Left",e);
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Chips",e);
    e.name = "Cookies";
    e.weight = 4;
    GroceryStore::getInstance().addEdge("Chips",e);
    e.weight = 2;
    GroceryStore::getInstance().addEdge("Soda",e);
    e.name = "A2Right";
    e.weight = 3;
    GroceryStore::getInstance().addEdge("Soda",e);
    GroceryStore::getInstance().addEdge("A1Right",e);
    GroceryStore::getInstance().addEdge("A3Right",e);
    e.name = "Juice";
    e.weight = 5;
    GroceryStore::getInstance().addEdge("A3Right",e);
    e.name = "Yogurt";
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Juice",e);
    e.weight = 3;
    GroceryStore::getInstance().addEdge("Eggs",e);
    e.name = "A3Left";
    e.weight = 1;
    GroceryStore::getInstance().addEdge("Eggs",e);
    e.weight = 3;
    GroceryStore::getInstance().addEdge("A2Left",e);
    e.name = "Exit";
    e.weight = 4;
    GroceryStore::getInstance().addEdge("A3Left",e);
    e.weight = 8;
    GroceryStore::getInstance().addEdge("A3Right",e);
    
}

ShoppingList::~ShoppingList() {
    for(ItemNode* n : this->possiblechoices) {
        delete n;
    }
    for(ItemNode* node : this->list) {
        delete node;
    }
}

std::vector<ItemNode*> ShoppingList::getList() {
    return this->list;
}

void ShoppingList::addItem() {
    std::cout << "Please select one of the items below to add to your list:\n";
    for(int i = 0; i < (int) this->possiblechoices.size();i++) {
        std::cout << i << ") " << possiblechoices[i]->getName() << " : $" << possiblechoices[i]->getPrice() << std::endl;
    }
    char input = '0';
    try
    {
        std::cin >> input;
        if(std::atoi(&input) < 0 || std::atoi(&input) >= (int) this->possiblechoices.size()) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
        else if(!isdigit(input)) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(input, '\n');
        input = -1;
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    this->list.push_back(this->possiblechoices[std::atoi(&input)]);
    this->possiblechoices.erase(possiblechoices.begin() + std::atoi(&input));
}

void ShoppingList::removeItem() {
    if(this->list.size() == 0) {
        return;
    }
    std::cout << "Please select one of the items below to be removed from your list:\n";
    for(int i = 0; i < (int) this->list.size();i++) {
        std::cout << i << ") " << list[i]->getName() << " : $" << list[i]->getPrice() << std::endl;
    }

    char input = '0';
    try
    {
        std::cin >> input;
        if(std::atoi(&input) < 0 || std::atoi(&input) >= (int)this->list.size()) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
        else if(!isdigit(input)) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(input, '\n');
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    this->possiblechoices.push_back(this->list[std::atoi(&input)]);
    list.erase(list.begin() + std::atoi(&input));
    
}

void ShoppingList::viewCurrentList() {
    for(ItemNode* n : list) {
        std::cout << n->getName() << "  : " << n->getPrice() << std::endl;
    }
}