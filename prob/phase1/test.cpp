#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
#include "hashmap.h"

using namespace std;
// int n = 50000;
int main()
{
    hashMap m;
    for (int i = 0; i < 5; i++)
    {
        m.addorinsert(to_string(i * 2), i + 69);
        m.print_tree();
    }
    hashMap X(m);
    m.addorinsert("fs", 69);
    X.print_tree();
}