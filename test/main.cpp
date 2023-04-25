#include "inc/ShoppingListTest.hpp"

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}