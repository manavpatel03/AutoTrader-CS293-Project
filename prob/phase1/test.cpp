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
    // hashMap H;
    // vector<int> a;
    // a.push_back(0);
    // for (int i = 0; i < 3; i++)
    // {
    //     H.addorinsert(to_string(char(i + 97)), 0);
    // }
    // // L->addtoLC(H, 69, 0);
    // L->addNode(&H, a, 233);
    // // L->addNode(X);
    // // L->head = &X;
    // // L->tail = &X;
    hashMap S;
    for (int i = 0; i < 5; i++)
    {
        S.addorinsert(to_string(char(i + 97)), 0);
    }
    // // Node_ll RR = Node_ll(45, j, S);
    // // L->tail->next = &RR;
    // // L->tail = L->tail->next;
    // // L->tail->next = NULL;
    for (int i = 0; i < 5; i++)
    {
        vector<int> j;
        j.push_back(i);
        L->addNode(&S, j, i * 4 - 2 + 56);
        for (int k = 0; k < 5; k++)
        {
            j[k]++;
        }
    }
    vector<int> yo;
    yo.push_back(0);
    yo.push_back(3);
    L->Display();
    cout << endl
         << endl
         << endl
         << endl;
    L->remove_invalid(yo);
    L->Display();
    // hashMap q;
    // for (int i = 1; i < 4; i++)
    // {
    //     q.addorinsert(to_string(char(i + 97)), i + 3);
    // }
    // // L->Display();
    // // q.print_tree();
    // // cout << "real deal" << endl;
    // L->addtoLC(q, 22, 2);
    // // L->Display();
    // int a69 = INT32_MIN;
    // vector<int> ty = L->getarbitrage(a69);
    // // cout << ty.size();
    // // for (int i = 0; i < ty.size(); i++)
    // //     cout << ty[i] << endl;
    // // L->remove_invalid(ty);
    // L-
}