#ifndef ITEMNODE_GUARD
#define ITEMNODE_GUARD

#include <iostream>

class ItemNode {
    public:
        ItemNode(std::string name, float price, bool coupon);
        ~ItemNode();
        std::string getName();
        float getPrice();
    private:
        std::string itemName;
        float price;
        bool validCoupon;
        // int Quantity;
        //can add more attributes for each item here
};

#endif