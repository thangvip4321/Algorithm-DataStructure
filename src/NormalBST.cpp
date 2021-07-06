#include "NormalBST.h"

NormalBST::NormalBST(int val)
{
    left = NULL;
    right = NULL;
    value = val;
}
NormalBST::~NormalBST()
{
    // cerr << "problem?: " << value << "\n";
    if (left != NULL)
    {
        delete left;
        left = nullptr;
    }
    if (right != NULL)
    {
        delete right;
        right = nullptr;
    }
}
NormalBST *NormalBST::find(int value)
{
    NormalBST *desiredNode = nullptr;

    if (this->value == value)
        return this;
    else if (this->value > value)
    {
        if (left != nullptr)
            desiredNode = left->find(value);
    }
    else
    {
        if (right != nullptr)
            desiredNode = right->find(value);
    }
    return desiredNode;
};
NormalBST *NormalBST::remove(int value)
{
    if (this->value == value)
    {
        // start deleting;
        if (left == nullptr && right == nullptr)
        {
            delete this; // bruh is it ok to commit suicide
            return nullptr;
        }
        else if (right != nullptr)
        {
            // how to make successor parent points to nothing?
            auto PreSuccessorAndDirection = findPreSuccessor(this);
            auto preSuccessor = PreSuccessorAndDirection.first;
            auto isLeft = PreSuccessorAndDirection.second;
            NormalBST *successor = nullptr;
            if (isLeft)
            {
                successor = preSuccessor->left;
                preSuccessor->left = successor->right;
            }
            else
            {
                successor = preSuccessor->right;
                preSuccessor->right = successor->right;
            }
            successor->left = left;
            successor->right = right;
            // successor cannot have left child, as it is the smallest element that is > current node;
            left = nullptr;
            right = nullptr;
            delete this;
            return successor;
        }
        else
        {
            auto child = left;
            left = nullptr;
            delete this;
            return child;
        }
    }
    else if (value < this->value)
    {
        if (left == nullptr)
        {
            cout << "cant delete if it doesnt exist";
            return this;
        }
        left = left->remove(value);
    }
    else if (value > this->value)
    {
        if (right == nullptr)
        {
            cout << "cant delete if it doesnt exist";
            return this;
        }
        right = right->remove(value);
    }
    return this;
};
void NormalBST::insert(int value)
{
    if (this->value == value)
        return;
    else if (value < this->value)
    {
        if (left == nullptr)
            left = new NormalBST(value);
        else
            left->insert(value);
    }
    else
    {
        if (right == nullptr)
            right = new NormalBST(value);
        else
            right->insert(value);
    }
    return;
};

pair<NormalBST *, bool> NormalBST::findPreSuccessor(NormalBST *root)
// return the predecessor of the successor and whether this successor is the left or the right child of the predecessor
{
    auto preSuccessor = root->right;
    NormalBST *successor = nullptr;

    while (preSuccessor->left != nullptr)
    {
        successor = preSuccessor->left;
        if (successor->left == nullptr)
            break; // reach the end, take successor
        preSuccessor = preSuccessor->left;
    }
    if (successor == nullptr)
        return {root, false};
    else
        return {preSuccessor, true};
};