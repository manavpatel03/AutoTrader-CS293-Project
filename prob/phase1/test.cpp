#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
#include "ll.h"

using namespace std;
// int n = 50000;
int main()
{
    Map2 s;
    s.insert("A", 19);
    s.insert("B", 34);
    Map2 *q = new Map2;
    q->root = q;
    q = q->copyMap(&s, q);
    s.insert("C", 68);
    // assert(s.root != q->root);
    s.inorderTraversal();
    LinkedList a;
    // a.Display();
    cout << endl;
    q->inorderTraversal();
}