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
    L->addNode(&H, a, 233);
    // L->addNode(X);
    // L->head = &X;
    // L->tail = &X;
    hashMap S;
    for (int i = 0; i < 3; i++)
    {
        S.addorinsert(to_string(char(i + 97)), i + 10);
    }
    vector<int> j;
    j.push_back(1);
    // Node_ll RR = Node_ll(45, j, S);
    // L->tail->next = &RR;
    // L->tail = L->tail->next;
    // L->tail->next = NULL;
    for (int i = 0; i < 31; i++)
    {
        L->addNode(&S, j, i * 4 - 2 + 56);
    }
    // L->Display();
    hashMap q;
    for (int i = 1; i < 4; i++)
    {
        q.addorinsert(to_string(char(i + 97)), i * 10 + 10);
    }
    // L->Display();
    cout << "real deal" << endl;
    L->addtoLC(q, 22, 2);
    L->Display();
}