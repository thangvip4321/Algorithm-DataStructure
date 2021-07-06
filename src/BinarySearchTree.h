#pragma once
class BinarySearchTree
{
protected:
public:
    BinarySearchTree(){};
    virtual ~BinarySearchTree(){};
    virtual bool insert(int value) = 0;
    virtual bool remove(int value) = 0;
    virtual int find(int value) = 0;
};
