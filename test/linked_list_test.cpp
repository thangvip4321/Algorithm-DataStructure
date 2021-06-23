#include <gtest/gtest.h>
#include <LinkedList.h>

TEST(CreateListSuit, CreateAndDelete)
{
    LinkedList<int> list0{};
    list0.push_back(1);
    list0.push_back(2);
    list0.clear();
    EXPECT_THROW(int a = list0.pop_back(), std::out_of_range);
    LinkedList<int> *list1 = new LinkedList<int>();
    list1->push_back(1);
    list1->push_back(2);
    EXPECT_NO_THROW(delete list1);
    // EXPECT_ANY_THROW(std::cout << list1->pop_back() << "\n";);
};

class LinkedTest : public ::testing::Test
{
protected:
    LinkedList<int> list0;
    LinkedList<int> list1;
    void SetUp() override
    {
        list0.push_back(5);
        list0.push_back(6);
        //
        list1.push_back(2);
        list1.push_back(3);
        list1.push_back(7);
        list1.push_back(5);
        // std::cerr << list1;
    };
    void TearDown() override
    {
        list0.clear();
        list1.clear();
    }
};

TEST_F(LinkedTest, TEST_POP)
{
    int a = list0.pop_back();
    EXPECT_EQ(a, 6);
    a = list0.pop_back();
    EXPECT_EQ(a, 5);
    EXPECT_THROW(a = list0.pop_back(), std::out_of_range) << "cannot pop the list if it's empty?";
};
TEST_F(LinkedTest, TEST_SEARCH_AND_INSERT)
{
    auto node = list1.search(4);
    EXPECT_EQ(node, nullptr);
    node = list1.search(3);
    EXPECT_EQ(node->value, 3);
    node = list1.search(7);
    EXPECT_EQ(node->value, 7);
    int insert_val = 4;
    list1.insert(insert_val, node);
    auto new_node = list1.search(insert_val);
    EXPECT_EQ(new_node->previous, node);
    EXPECT_EQ(new_node->value, insert_val);
}
TEST_F(LinkedTest, TEST_REMOVE)
{
    int status = list1.remove(4); // attempt to remove non-existent element
    EXPECT_EQ(status, 0);
    status = list1.remove(7);
    EXPECT_EQ(status, 1);
    auto node = list1.search(7);
    EXPECT_EQ(node, nullptr);
}
// TEST_F(LinkedTest, TEST_CLEAR)
// {
//     list0.clear();
// }

// int main(int argc, char **argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
