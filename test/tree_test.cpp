#include <gtest/gtest.h>
#include <RedBlackTree.h>
#include <NormalBST.h>
#include <iostream>
TEST(CreateTree, TestInsert)
{
    auto tree = NormalBST(7);
    tree.insert(12);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(9);
    tree.insert(1);
    cout << tree;
}
TEST(CreateTree, TestRemove)
{
    auto tree = NormalBST(7);
    tree.insert(12);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(9);
    tree.insert(1);
    tree.remove(5);
    tree.remove(12);
    cout << tree;
}
TEST(CreateTree, TestClear)
{
    auto tree = new NormalBST(7);
    tree->insert(12);
    tree->insert(5);
    tree->insert(4);
    tree->insert(3);
    tree->insert(9);
    tree->insert(1);
    tree->remove(5);
    tree->remove(12);
    delete tree;
}
TEST(CreateTree, TestFind)
{
    auto tree = NormalBST(7);
    tree.insert(12);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    cout << tree.find(3) << "\n";
    tree.insert(9);
    tree.insert(1);
    tree.remove(5);
    cout << tree.find(5) << "\n";
    tree.remove(12);
    cout << tree;
}