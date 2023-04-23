#include "../include/ShoppingList.hpp"

ShoppingList::ShoppingList() {
    possiblechoices.push_back(new ItemNode("Soda",10,false));
    possiblechoices.push_back(new ItemNode("Cheese",3.4,false));
    possiblechoices.push_back(new ItemNode("Milk",3.99,true));
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
    int input = -1;
    try
    {
        std::cin >> input;
        if(input < 0 || input >= (int) this->possiblechoices.size()) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        addItem();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    this->list.push_back(this->possiblechoices[input]);
    this->possiblechoices.erase(possiblechoices.begin() + input);
}

void ShoppingList::removeItem() {
    if(this->list.size() == 0) {
        return;
    }
    std::cout << "Please select one of the items below to be removed from your list:\n";
    for(int i = 0; i < (int) this->list.size();i++) {
        std::cout << i << ") " << list[i]->getName() << " : $" << list[i]->getPrice() << std::endl;
    }

    int input = -1;
    try
    {
        std::cin >> input;
        if(input < 0 || input >= (int)this->list.size()) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        removeItem();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    this->possiblechoices.push_back(this->list[input]);
    list.erase(list.begin() + input);
    
}

void ShoppingList::viewCurrentList() {
    for(ItemNode* n : list) {
        std::cout << n->getName() << "  : " << n->getPrice() << std::endl;
    }
}