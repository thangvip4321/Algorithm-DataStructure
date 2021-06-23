#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
using std::string;

template <typename T>
struct Node
{
    T value;
    Node<T> *previous;
    Node<T> *next;
};

template <typename T>
class LinkedList
{
private:
    Node<T> *begin;
    Node<T> *end;
    int remove_node(Node<T> *node)
    {
        if (node == nullptr)
        {
            return -1;
        }
        Node<T> *prev_node = node->previous;
        Node<T> *next_node = node->next;
        if (prev_node != nullptr)
            prev_node->next = next_node;
        if (next_node != nullptr)
            next_node->previous = prev_node;
        delete node;
        return 0;
    };

public:
    LinkedList()
    {
        this->begin = nullptr;
        this->end = nullptr;
    }
    ~LinkedList()
    {
        this->clear();
    }
    int push_back(T value)
    {
        Node<T> *node = new Node<T>{value};
        node->next = nullptr;
        Node<T> *last_node = this->end;
        if (last_node != nullptr)
        {
            last_node->next = node;
        }
        else
        {
            this->begin = node;
        }

        node->previous = last_node;
        this->end = node;
        return 0;
    };
    // int pop_front(T value);
    T pop_back()
    {
        if (this->end == nullptr)
        {
            throw std::out_of_range("no more node to pop");
        }
        T val = this->end->value;
        if (this->begin == this->end)
        {
            this->begin = nullptr;
        }
        Node<T> *prev_node = this->end->previous;
        delete this->end;
        this->end = prev_node;
        return val;
    };
    int insert(T value, Node<T> *before)
    {
        Node<T> *new_node = new Node<T>{value};
        if (before == nullptr)
            return -1;
        auto next_node = before->next;
        before->next = new_node;
        new_node->previous = before;
        new_node->next = next_node;
        if (next_node != nullptr)
            next_node->previous = new_node;
        return 1;
    };
    Node<T> *search(T value)
    {
        for (Node<T> *node = this->begin; node != nullptr; node = node->next)
        {
            if (node->value == value)
            {
                return node;
            }
        }
        return nullptr;
        // auto a = new Node<int>{-1};
        // return a;
    };
    //seriously this search is useless
    int remove(T value)
    {
        int removed = 0;
        for (Node<T> *node = this->begin; node != nullptr; node = node->next)
        {
            if (node->value == value)
            {
                remove_node(node);
                removed++;
            }
        }
        return removed;
    }; // return number of element deleted
    int clear()
    {
        while (this->end != nullptr)
        {
            this->pop_back();
        }
        return 0;
    };
    Node<T> *first()
    {
        return this->begin;
    }
    Node<T> *last()
    {
        return this->end;
    }
    bool isEmpty()
    {
        return (this->begin == nullptr);
    }
    friend std::ostream &operator<<(std::ostream &s, LinkedList<T> &ls)
    {
        s << "\nList: ";
        for (auto node = ls.first(); node != nullptr; node = node->next)
        {
            s << node->value << " ";
        }
        s << "\n";
        return s;
    }
};
// #endif