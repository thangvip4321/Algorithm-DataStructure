#pragma once
#include "BinarySearchTree.h"
#include <iostream>
#include <string>
using std::cout;
using std::string;
struct RedBlackNode
{
    int value;
    RedBlackNode *left;
    RedBlackNode *right;
    bool isRed;
    void printTree(const string prefix = "", bool isLeft = false)
    {
        cout << prefix << (isLeft ? "L--" : "R--");
        cout << "\033[1;47;" << ((isRed) ? "31m" : "30m") << value << "\033[0m\n";
        if (this->left != nullptr)
            this->left->printTree(prefix + (isLeft ? "|   " : "    "), true);
        if (this->right != nullptr)
            this->right->printTree(prefix + (isLeft ? "|   " : "    "), false);
    }
};

class RedBlackTree : public BinarySearchTree
{
private:
    RedBlackNode *root;
    int deleteSubTree(RedBlackNode *node);
    int leftRotate(RedBlackNode *root);
    int rightRotate(RedBlackNode *root);
    RedBlackNode *insert(RedBlackNode *node, int val);
    void colorFlip(RedBlackNode *node);
    RedBlackNode *rotateLeft(RedBlackNode *dad)
    {
        auto newDad = dad->right;
        auto child = newDad->left;
        newDad->left = dad;
        dad->right = child;
        return newDad;
    }
    RedBlackNode *rotateRight(RedBlackNode *dad)
    {
        auto newDad = dad->left;
        auto abandonedChild = newDad->right;
        newDad->right = dad;
        dad->left = abandonedChild;
        return newDad;
    }
    RedBlackNode *remove(RedBlackNode *node, int val);

public:
    RedBlackTree(/* args */);
    ~RedBlackTree();
    bool insert(int val) override;
    int find(int val) override;
    bool remove(int val) override;
    void printTree()
    {
        root->printTree();
    }
};
