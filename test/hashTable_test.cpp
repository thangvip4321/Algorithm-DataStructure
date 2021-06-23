#include <HashTable.h>
#include <chrono>
#include <string>
#include <gtest/gtest.h>
using std::string;
using std::time;
// TEST(TestHashTable, TestInsert)
// {
//     HashTable table1;
//     int res = table1.insert(string(""), 5);
//     EXPECT_EQ(res, -1) << "DO NOT ALLOW empty struct! into the hashTable!";
//     res = table1.insert("", 5);
//     EXPECT_EQ(res, -1) << "DO NOT ALLOW empty struct! into the hashTable!";

//     // check that hashTable cannot insert elements with the same key
//     res = table1.insert("thang", 5);
//     EXPECT_EQ(res, 0);
//     res = table1.insert("thang", 4);
//     EXPECT_EQ(res, -1);

//     res = table1.insert("xvideo", 12);
//     EXPECT_EQ(res, 0);
//     res = table1.insert("haha", 7);
//     EXPECT_EQ(res, 0);
//     res = table1.insert("ahha", 4);
//     EXPECT_EQ(res, 0);

//     int t = table1.get("thang");
//     EXPECT_EQ(t, 5);
//     t = table1.get("xvideo");
//     EXPECT_EQ(t, 12);
//     t = table1.get("haha");
//     EXPECT_EQ(t, 7);
// };

class HashTableTest : public ::testing::Test
{
protected:
    HashTable testTable = HashTable();
    void SetUp() override
    {
        testTable.insert("thang", 2);
        testTable.insert("xvideo", 12);
        testTable.insert("haha", 7);
        testTable.insert("ahha", 65);
        // testTable.insert("damn son", 12);
        // std::cerr << "table is: " << testTable;
    };
};
TEST_F(HashTableTest, TestFind)
{

    // find non-existent key
    EXPECT_THROW(testTable.get("not a key"), std::invalid_argument);
    // EXPECT_EQ(t.key, "");

    //find normal key
    int t = testTable.get("thang");
    EXPECT_EQ(t, 2);
    t = testTable.get(string("xvideo"));
    EXPECT_EQ(t, 12);
    t = testTable.get("haha");
    EXPECT_EQ(t, 7);
    t = testTable.get("ahha");
    EXPECT_EQ(t, 65);
    // remove and find the key again
    testTable.remove("ahha");
    EXPECT_THROW(testTable.get("ahha"), std::invalid_argument);
    // EXPECT_EQ(t, "");
    std::cerr << "everything is ok\n";
};
TEST_F(HashTableTest, TestDelete)
{
    // try to remove twice
    int res = testTable.remove("thang");
    EXPECT_EQ(res, 0);
    res = testTable.remove("thang");
    EXPECT_EQ(res, -1);
    // remove and then add the same key
    res = testTable.remove("haha");
    EXPECT_EQ(res, 0);
    res = testTable.insert("haha", 3);
    EXPECT_EQ(res, 0);
    // remove non-existent key;
    res = testTable.remove("not a key");
    EXPECT_EQ(res, -1);
    // remove and get the same key;
    res = testTable.remove("ahha");
    EXPECT_EQ(res, 0);
    EXPECT_THROW(testTable.get("ahha"), std::invalid_argument);
    // remove ""
    res = testTable.remove("");
    EXPECT_EQ(res, -1);
};

TEST_F(HashTableTest, TEST_REHASH)
{
    auto t0 = std::chrono::high_resolution_clock::now();
    // iteration : add 26*26*26 entries string of 3 chars.
    char *test_str = new char[3];
    for (int a = 97; a < 123; a++)
    {
        test_str[0] = a;
        for (int b = 97; b < 123; b++)
        {
            test_str[1] = b;
            for (int c = 97; c < 123; c++)
            {
                test_str[2] = c;
                string str = string(test_str);
                int val = a + b + c;
                testTable.insert(str, val);
            }
        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "time spent inserting and also rehashig 17576 elements is: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() << "\n";
    // auto v = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();

    // check num of bucket after rehash
    EXPECT_EQ(testTable.numOfBuckets(), 32768);
    // find original keys: thang,haha,ahha,...
    int t = testTable.get("thang");
    EXPECT_EQ(t, 2);
    t = testTable.get("haha");
    EXPECT_EQ(t, 7);
    t = testTable.get("ahha");
    EXPECT_EQ(t, 65);
    t = testTable.get("xvideo");
    EXPECT_EQ(t, 12);
    // check variance
};
// // TEST(TEST_HASH_MAP, TEST_HASH_PERFORMANCE){};
