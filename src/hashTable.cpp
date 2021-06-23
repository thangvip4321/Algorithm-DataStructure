#include "HashTable.h"
#include <string>
#include <iostream>
uint32_t defaultHash(string str)
{
    uint32_t hash = 5381;
    for (int c = 0; c < str.length(); c++)
    {
        hash = (hash << 5) + hash + str[c];
    }
    return hash;
}
uint32_t _multiplicativeHash(uint32_t prehash, int log2BucketNum)
{
    // idea of multiplicative hash:
    // multiply k by A, 0 < A < 1, and k is an integer. We used fixed point presentation for speeed : uint32_t.uint32_t
    //  A is recommended to be (sqrt(5)-1) / 2: which is 0.6180339887 in decimal and 0.100111100.... in binary
    // k * A = k *(A*2^32) / (2^32); (A*2^32 shift the whole decimal part to the whole number part);
    // t = mod(k*A,1) requires taking the decimal part of k*A(uint32_t.uint32_t)
    // technically, we only need to remove /(2^32) part, as if k*A has whole number part , it will surely overflow.
    // floor(m*mod(k*A,1)) ,if m = 2^p , is effectively taking the most significant p bit of t
    uint32_t A = 2654435769;

    uint32_t hash = prehash * A;
    uint32_t index = hash >> (32 - log2BucketNum); //;
    return index;
}

uint32_t HashTable::multiplicativeHash(uint32_t prehash)
{
    return _multiplicativeHash(prehash, exponentBucket);
}

LinkedList<tuple> *HashTable::bucket(string key)
{
    if (key.empty())
        return nullptr;
    uint32_t hash = hashFunctor(key);
    uint32_t bucketIndex = multiplicativeHash(hash);
    LinkedList<tuple> *ls = buckets[bucketIndex];
    return ls;
}

int HashTable::get(string key)
{
    if (key.empty())
        throw std::invalid_argument("key cannot be an empty string");
    uint32_t hash = hashFunctor(key);
    uint32_t bucketIndex = multiplicativeHash(hash);
    LinkedList<tuple> *ls = buckets[bucketIndex];
    if (ls == nullptr)
        throw std::invalid_argument("no such key");
    auto node = ls->search({key, 0, hash});
    if (node == nullptr)
    {
        throw std::invalid_argument("no such key");
    }
    return node->value.value;
};

Node<tuple> *HashTable::findNode(string key, int flag)
{
    if (key.empty())
        throw std::invalid_argument("key cant be empty");
    uint32_t hash = hashFunctor(key);
    uint32_t bucketIndex = multiplicativeHash(hash);
    auto ls = buckets[bucketIndex];
    if (ls == nullptr)
    {
        if (flag == 1)
            ls = new LinkedList<tuple>();
    }
    auto node = ls->search({key, 0, hash});

    return node;
};

// LinkedList<tuple> HashTable::bucket(string key){};
// insert return 0 on success and -1 on failure
int HashTable::insert(string key, int val)
{
    if (key.empty())
        return -1;
    uint32_t hash = hashFunctor(key);
    // std::cerr << "hash number is: " << hash << key << "\n";
    uint32_t bucketIndex = multiplicativeHash(hash);
    // std::cerr << "bucket index is " << bucketIndex << "\n";
    auto ls = buckets[bucketIndex];
    if (ls == nullptr)
    {
        // std::cerr << "list is empty, index is: " << bucketIndex << ", creating one\n";
        buckets[bucketIndex] = new LinkedList<tuple>();
        // std::cerr << "before insert: " << *buckets[bucketIndex];
        buckets[bucketIndex]->push_back({key, val, hash});
        // std::cerr << *buckets[bucketIndex];
        elemNum++;
        return 0;
    }
    // std::cerr << "list not empty, index is: " << bucketIndex << "\n";

    auto node = ls->search({key, val, hash});
    if (node != nullptr)
    {
        std::cerr << "found existing element with the same key, abort insertion " << node->value.key << " \n";
        return -1;
    }
    // std::cerr << "before insert: " << *buckets[bucketIndex];
    buckets[bucketIndex]->push_back({key, val, hash});
    // std::cerr << *buckets[bucketIndex];
    elemNum++;
    if (load_factor() > max_load_factor())
    {
        std::cerr << "elements num is " << elemNum << ",rehash time!!\n";
        rehash();
    }
    return 0;
};

int HashTable::remove(string key)
{
    if (key.empty())
        return -1;
    uint32_t hash = hashFunctor(key);
    uint32_t bucketIndex = multiplicativeHash(hash);
    auto ls = buckets[bucketIndex];
    if (ls == nullptr)
    {
        return -1;
    }
    int countRemoved = ls->remove({key, 0, hash});
    if (countRemoved == 0)
    {
        std::cerr << "non-existent key";
        return -1;
    }
    elemNum--;
    return 0;
};

int HashTable::rehash()
{
    // double the bucket
    int newBucketNum = bucketNum * 2;
    int log2NewBucket = log2(newBucketNum);
    LinkedList<tuple> **newBuckets = (LinkedList<tuple> **)calloc(newBucketNum, sizeof(void *));
    // std::cerr << "current number of bucket before rehashing is: " << bucketNum << "\n";
    // std::cerr << *this;
    for (int i = 0; i < bucketNum; i++)
    {
        auto ls = buckets[i];
        if (ls == nullptr)
            continue;
        for (auto node = ls->first(); node != nullptr; node = node->next)
        {
            tuple t = node->value;
            uint32_t newIndex = _multiplicativeHash(t.hash, log2NewBucket);
            // std::cerr << newBuckets[newIndex];
            // std::cerr << "new index is: " << newIndex << newBuckets[newIndex] << "\n";
            if (newBuckets[newIndex] == nullptr)
            {
                // std::cerr << "no bug here\n";
                newBuckets[newIndex] = new LinkedList<tuple>();
            }
            newBuckets[newIndex]->push_back(t);
        }
    }

    // delete the old bucket
    for (int i = 0; i < bucketNum; i++)
    {
        auto ls = buckets[i];
        if (ls == nullptr)
            continue;
        delete ls;
    }
    free(buckets);
    bucketNum = newBucketNum;
    exponentBucket = log2NewBucket;
    buckets = newBuckets;
    return 0;
};
HashTable::~HashTable()
{
    std::cerr << "calling table destructor\n";
    free(this->buckets);
};
HashTable::HashTable(HashFunc functor /*= defaultHash*/)
{
    this->hashFunctor = functor;
    this->buckets = (LinkedList<tuple> **)calloc(this->bucketNum, sizeof(void *));
    std::cout
        << "address is : " << this->buckets[0] << "\n";
    this->elemNum = 0;
};