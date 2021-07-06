#pragma once
#include "BinarySearchTree.h"
#include <iostream>
#include <string>
using std::cerr;
using std::cout;
using std::ostream;
using std::pair;
using std::string;
class NormalBST
{
private:
    NormalBST *left;
    NormalBST *right;
    int value;
    // void traverse(NormalBST *root);
    void printTree(const string prefix = "", bool isLeft = false)
    {
        cout << prefix << (isLeft ? "L--" : "R--");
        cout << value << "\n";
        if (this->left != nullptr)
            this->left->printTree(prefix + (isLeft ? "|   " : "    "), true);
        if (this->right != nullptr)
            this->right->printTree(prefix + (isLeft ? "|   " : "    "), false);
    }
    pair<NormalBST *, bool> findPreSuccessor(NormalBST *node);

public:
    NormalBST(int val);
    ~NormalBST();
    NormalBST *find(int value);
    NormalBST *remove(int value);
    void insert(int value);
    friend ostream &operator<<(ostream &s, NormalBST &tree)
    {
        tree.printTree();
        return s;
    }
};