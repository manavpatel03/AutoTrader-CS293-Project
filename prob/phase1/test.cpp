#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
#include "ll.h"

using namespace std;
int n = 500;
int main()
{
    LinkedList *L = new LinkedList;
    L->head = NULL;
    L->tail = NULL;
    hashMap H;
    vector<int> a;
    a.push_back(0);
    for (int i = 0; i < 3; i++)
    {
        H.addorinsert(to_string(char(i + 97)), i * 100 + 10);
    }
    // L->addtoLC(H, 69, 0);
    Node_ll X = Node_ll(34, a, H);
    // L->addNode(X);
    L->head = &X;
    L->tail = &X;
    L->tail->next = NULL;
    hashMap S;
    for (int i = 0; i < 3; i++)
    {
        S.addorinsert(to_string(char(i + 97)), i * 10 + 10);
    }
    L->addtoLC(S, 69, 1);
    L->Display();
}