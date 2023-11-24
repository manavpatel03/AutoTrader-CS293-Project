#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
#include "ll.h"

using namespace std;

int main()
{
    hashMap H;
    H.addorinsert("nope", 56);
    H.addorinsert("fhf", 44);
    hashMap *G = H.Mapmaker(&H);
    H.addorinsert("fhf", 4);
    G->print_tree();
    cout << H.Bucket[44] << " " << G->Bucket[44];
}