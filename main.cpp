#include <HashTable.h>
#include <iostream>
int main()
{
    HashTable b;
    b.insert("lmao", 2);
    b.insert("xd", 2);
    b.insert("tan dung", 1);
    b.insert("thang", 5);
    b.insert("ho cam dao", 7);
    std::cerr << b;
}