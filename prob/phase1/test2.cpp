#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
// #include "stockstruct.h"
#include "ll.h"

using namespace std;

int main()
{
    int n = 1333;
    Node2 *p = new Node2();
    hashMap *w = new hashMap();
    int cost;
    w->addorinsert("dg", 45);
    for (int i = 0; i < n; i++)
    {
        Node2 *q = p->Newnode2(w, (i - 400) * (200 - i) + 1, i + 2, 'b');
        p->ins(q);
        if(i == 534) cost = (i - 400) * (200 - i) + 1;
    }
    cout << p->isrch(cost, w, 's');
}