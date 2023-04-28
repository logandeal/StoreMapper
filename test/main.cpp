#include "inc/ShoppingListTest.hpp"
#include "inc/GroceryStoreTest.hpp"


TEST_F(ShoppingListTest, IsEmptyInitially) {
    EXPECT_EQ(list->getList().size(),0);
}

TEST_F(ShoppingListTest, AddItem) {
    list->addItem();
    ASSERT_EQ(list->getList().size(),1);
    list->addItem();
    ASSERT_EQ(list->getList().size(),2);
}
TEST_F(ShoppingListTest, RemoveItem) {
    list->addItem();
    list->removeItem();
    ASSERT_EQ(list->getList().size(),0);
}

TEST_F(GroceryStoreTest, AddNode){
    GroceryStore::getInstance().addNode("Milk");
    ASSERT_EQ(GroceryStore::getInstance().getMap().size(), 1);
}

TEST_F(GroceryStoreTest, AddEdge){
    Edge e;
    e.name = "Milk";
    e.weight = 1;
    
    GroceryStore::getInstance().addNode("Milk");
    GroceryStore::getInstance().addNode("Cookies");
    GroceryStore::getInstance().addEdge("Cookies", e);
    ASSERT_EQ(GroceryStore::getInstance().getMap().size(), 2);
    ASSERT_EQ(GroceryStore::getInstance().getMap().at("Cookies").front(), e);
    e.name = "Cookies";
    ASSERT_EQ(GroceryStore::getInstance().getMap().at("Milk").front(), e);
}

TEST_F(GroceryStoreTest, DeleteNode){
    GroceryStore::getInstance().addNode("Milk");
    ASSERT_EQ(GroceryStore::getInstance().getMap().size(), 1);
    GroceryStore::getInstance().deleteNode("Milk");
    ASSERT_EQ(GroceryStore::getInstance().getMap().size(), 0);
}

TEST_F(GroceryStoreTest, DeleteNodeWithEdges){
    Edge e;
    e.name = "Milk";
    e.weight = 1;
    
    GroceryStore::getInstance().addNode("Milk");
    GroceryStore::getInstance().addNode("Cookies");
    GroceryStore::getInstance().addEdge("Cookies", e);
    GroceryStore::getInstance().deleteNode("Milk");
    ASSERT_EQ(GroceryStore::getInstance().getMap().at("Cookies").size(), 0);
}

TEST_F(GroceryStoreTest, DeleteEdge){
    Edge e;
    e.name = "Milk";
    e.weight = 1;
    
    GroceryStore::getInstance().addNode("Milk");
    GroceryStore::getInstance().addNode("Cookies");
    GroceryStore::getInstance().addEdge("Cookies", e);
    ASSERT_EQ(GroceryStore::getInstance().getMap().at("Cookies"), 1);
    GroceryStore::getInstance().deleteEdge("Cookies", e);
    ASSERT_EQ(GroceryStore::getInstance().getMap().at("Cookies").size(), 0);
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}