#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
#include "ll.h"

using namespace std;

int main()
{
    hashMap H;
    for (int j = 0; j < 5; j++)
    {
        for (int i = j; i < 10 + j; i++)
        {
            H.addorinsert(to_string(i + 1), 1);
        }
    }
    H.print_tree();
    // cout << H.Bucket[44] << " " << G->Bucket[44];
}