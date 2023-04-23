#include "inc/ShoppingListTest.hpp"

TEST_F(ShoppingListTest, IsEmptyInitially) {
    EXPECT_EQ(list->getList().size(),0);
}

TEST_F(ShoppingListTest, AddItem) {

}
TEST_F(ShoppingListTest, RemoveItem) {

}
TEST_F(ShoppingListTest, ViewList) {
    
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}