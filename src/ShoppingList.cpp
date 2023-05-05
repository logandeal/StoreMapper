#include "../include/ShoppingList.hpp"
ShoppingList::ShoppingList() {
    std::ifstream node_file;
    try
    {
        //open up the edge setup file
        node_file.open("itemnodesetup.csv");
        if(!node_file) {
            throw std::ios_base::failure("Cannot open file!");       
        }
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    std::string node_string = "";
    //getting each line of the csv which holds one node, with the weight and possible coupons
    while(getline(node_file,node_string)) {
        //Using a stringstream to parse each line of the CSV
        std::istringstream s(node_string);
        //Variables that will hold the node statistics
        std::string item = "";
        std::string price = "";
        std::string coupon = "";
        //Get each node variable, separated by a comma delimeter
        getline(s,item, ',');
        getline(s,price,',');
        getline(s,coupon,',');
        possiblechoices.push_back(new ItemNode(item,std::stof(price),toBool(coupon)));
    }
}
//Helper function to determine if a string is true or false to convert it to boolean
bool toBool(std::string s) {
    if(s == "false") {
        return false;
    }
    return true;
}
ShoppingList::~ShoppingList() {
    for(ItemNode* n : this->possiblechoices) {
        //iterating through and deleting all of the created nodes
        delete n;
    }
    for(ItemNode* node : this->list) {
        delete node;
    }
}
void ShoppingList::setupForSearch() {
    //Add an exit node to our list to be included in the search
    list.push_back(new ItemNode("Exit",-1,false));
    //Adding the enter node to our final list which will be searched upon
    list.insert(list.begin(), new ItemNode("Enter",-1,false));
}
//Getter for the final list
std::vector<ItemNode*> ShoppingList::getList() {
    return this->list;
}
//Function to add items to the final list
void ShoppingList::addItem() {
    std::cout << "Please select one of the items below to add to your list:\n";
    for(int i = 0; i < (int) this->possiblechoices.size();i++) {
        //Iterate through and print all of the possible choices in the list
        std::cout << i << ") " << possiblechoices[i]->getName() << " : $" << possiblechoices[i]->getPrice() << std::endl;
    }
    std::string input = "-1";
    try
    {
        //Performing error checking on the input to make sure that it is a single valid number
        std::cin >> input;
        if(hasCharacters(input)) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
        //If the number is too big or too small from the numbers shown to the user then throw an error
        if(std::stoi(input) < 0 || std::stoi(input) >= (int) this->possiblechoices.size()) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        //clear cin on an error to allow it to be used, then set input to -1 to indicate error and return
        std::cin.clear();
        input = "-1";
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    //Add the selected option if it passed the error checking to the final list and remove it from the possible choices
    this->list.push_back(this->possiblechoices[std::stoi(input)]);
    this->possiblechoices.erase(possiblechoices.begin() + std::stoi(input));
}
//Function to remove items from the final list
void ShoppingList::removeItem() {
    //If the list is empty, then nothing can be done so return
    if(this->list.size() == 0) {
        return;
    }
    std::cout << "Please select one of the items below to be removed from your list:\n";
    for(int i = 0; i < (int) this->list.size();i++) {
        //Iterate through each item that could be removed
        std::cout << i << ") " << list[i]->getName() << " : $" << list[i]->getPrice() << std::endl;
    }

    std::string input = "-1";
    try
    {
        //Similar to addItem, with error checking for the input
        std::cin >> input;
        if(hasCharacters(input)) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
        if(std::stoi(input) < 0 || std::stoi(input) >= (int)this->list.size()) {
            throw std::invalid_argument("Invalid choice, please select again!");
        }
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        std::cin.clear();
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    //If we pass the error checking, we readd the item that was removed to possiblechoices, and remove it from the final list
    this->possiblechoices.push_back(this->list[std::stoi(input)]);
    list.erase(list.begin() + std::stoi(input));
    
}
//Function to view the current final list
void ShoppingList::viewCurrentList() {
    for(ItemNode* n : list) {
        std::cout << n->getName() << "  : $" <<n->getPrice() << std::endl;
    }
}
//helper function for error checking to see if a given string has characters inside of it
bool hasCharacters(std::string s) {
    for(auto &character : s) {
        //iterate through the string and check if the given character is not a digit
        if(!std::isdigit(character)) {
            return true;
        }
    }
    return false;
}

void ShoppingList::addToPossibleChoices(ItemNode* item){
    possiblechoices.push_back(item);
}
void ShoppingList::cleanupAfterSearch() {
    list.pop_back();
    list.erase(list.begin());
}