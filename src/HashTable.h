#pragma once
#include "LinkedList.h"
#include "math.h"
#include <string>
#include <iostream>
using std::string;

// this is the djb2 hash algo
uint32_t defaultHash(string str);

class tuple
{
public:
    string key;
    int value;
    uint32_t hash;
    tuple(string k, int v, uint32_t h) : key(k), value(v), hash(h){};
    bool operator==(tuple rhs)
    {
        // std::cerr << "tuple : " << key << " " << rhs.key << "\n";
        if (hash != rhs.hash)
            return false;
        if (key != rhs.key)
            return false;
        return true;
    };
    friend std::ostream &operator<<(std::ostream &s, tuple b)
    {
        s << "{" << b.key << " :" << b.value << "}";
    }
};

typedef uint32_t (*HashFunc)(string str);

class HashTable
{
private:
    LinkedList<tuple> **buckets; // hmm this should be a dynamic array, for rehashing purpose
    HashFunc hashFunctor;
    int elemNum = 0;
    int bucketNum = 8;
    int exponentBucket = log2(bucketNum);

    // flag 1 : if the bucket is empty, create a new list at that bucket, while flag 0 will do nothing;
    Node<tuple> *findNode(string key, int flag);
    //remember this is only for hashing from integer datatype to an index in the hash table.
    // should there be a rehash, this multiplicative hash will change according to the bucketNum.
    uint32_t multiplicativeHash(uint32_t prehash);
    LinkedList<tuple> *bucket(string key); // this function should not be public
    int rehash();
    // We need a proper assignment operator
    // auto a = HashTable();
    // a = HashTable(); this code will cause double free: in the assignment the new bucket will be copied to the old address
    //  while the old HashTable() object will call its destructor, accidentally deleted the newly assigned bucket.
public:
    HashTable(HashFunc functor = defaultHash);
    ~HashTable();
    int get(string key);
    int insert(string key, int value);
    float load_factor()
    {
        return elemNum / bucketNum;
    };
    float max_load_factor()
    {
        return 0.9;
    }
    int remove(string key);
    int numOfBuckets()
    {
        return bucketNum;
    };
    friend std::ostream &operator<<(std::ostream &s, HashTable &table)
    {
        s << "\nBucket|  List\n";
        for (int i = 0; i < table.bucketNum; i++)
        {
            s << i << "|      ";
            auto list = table.buckets[i];
            if (list != nullptr)
            {
                for (auto node = list->first(); node != nullptr; node = node->next)
                {
                    s << node->value << "  ";
                }
            }
            s << "\n";
        }
        return s;
    }
};