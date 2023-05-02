#include "../include/ItemNode.hpp"
//Nodes that will be created will use the following constructor
ItemNode::ItemNode(std::string name, float price, bool coupon) {
    this->itemName = name;
    this->price = price;
    this->validCoupon = coupon;
}

std::string ItemNode::getName() {
    return this->itemName;
}

float ItemNode::getPrice() {
    return this->price;
}
ItemNode::~ItemNode() {
    
}