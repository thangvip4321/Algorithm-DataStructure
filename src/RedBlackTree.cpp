#include "RedBlackTree.h"
#include <stdexcept>
bool isRed(RedBlackNode *node)
{
    if (node == nullptr)
        return false;
    return node->isRed;
}
RedBlackTree::RedBlackTree(/* args */)
{
    root = nullptr;
}

RedBlackTree::~RedBlackTree()
{
    deleteSubTree(root);
}
int RedBlackTree::find(int val)
{
    RedBlackNode *node = root;
    while (node != nullptr)
    {
        if (node->value == val)
            return node->value;
        if (val < node->value)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    throw std::out_of_range("no such value");
}
RedBlackNode *RedBlackTree::insert(RedBlackNode *node, int val)
{
    if (node == nullptr)
        return new RedBlackNode{val, nullptr, nullptr, true};
    if (isRed(node->left) && isRed(node->right))
        colorFlip(node); // this will cause some violation, which we will fix after insertion is done
    if (node->value == val)
        return node;
    else if (node->value > val)
        node->left = insert(node->left, val);
    else
        node->right = insert(node->right, val);

    //  fix violation after insertion
    // we cannot do anything if the current node is red, but we can assure that
    // 1. there can be no 3 consecutive red node in insertion process.
    // 2. the rotating work can be delegated to the parent
    if (isRed(node))
        return node;
    // hence , this fix violation thing is done recursively with assumptions that
    // 1.the current node is black.
    // 2. the node 's children cannot be both red, as we have already splited above
    if (isRed(node->left))
    {
        if (isRed(node->left->right))
        {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        else if (isRed(node->left->left))
            node = rotateRight(node);
        else
            // both children of the left node are not red, which cannot violate anything, so exit early
            return node;
        node->right->isRed = true;
    }
    else if (isRed(node->right))
    {
        if (isRed(node->right->left))
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        else if (isRed(node->right->right))
            node = rotateLeft(node);
        else
            return node;
        node->left->isRed = true;
    }
    else
        // both of children node are black, what do we expect? Just exit.
        return node;
    // however, if rotation is involved, the current node must be set to black
    // this area will become a 4 node after rotation (r|b|r)
    node->isRed = false;
    return node;
}
void RedBlackTree::colorFlip(RedBlackNode *node)
{
    node->left->isRed = !node->left->isRed;
    node->right->isRed = !node->right->isRed;
    if (node == this->root)
        return;
    node->isRed = !node->isRed;
}
RedBlackNode *RedBlackTree::remove(RedBlackNode *node, int val)
{
    // search, while making 2-node becoming 3-node or 4-node, so that when we delete a node, we don't have to worry about underflow
    if (node == nullptr)
        return nullptr;
    // if (isRed(node->left) && isRed(node->right))
    // colorFlip(node); // this will cause some violation, which we will fix after insertion is done
    if (node->value == val)
        // delete this shit, if it is NOT an internal node; :/
        return nullptr;
    else if (node->value > val)
        node->left = remove(node->left, val);
    else
        node->right = remove(node->right, val);
};
bool RedBlackTree::remove(int val)
{
    RedBlackNode *tmpNode = nullptr;
    remove(root, val);
}
bool RedBlackTree::insert(int val)
{
    root = insert(root, val);
    root->isRed = false;
    return true;
}
int RedBlackTree::deleteSubTree(RedBlackNode *node) {}