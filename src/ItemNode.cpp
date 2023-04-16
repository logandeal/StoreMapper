#include "../include/ItemNode.hpp"

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