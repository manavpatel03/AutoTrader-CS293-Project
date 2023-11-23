#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
#include "ll.h"

using namespace std;
int n = 500;
int main()
{
    LinkedList L = LinkedList();
    hashMap H;
    vector<int> a;
    a.push_back(4);
    for (int i = 0; i < 3; i++)
    {
        H.addorinsert(to_string(char(i + 97)), i * 100 + 10);
    }
    // L->addtoLC(H, 69, 0);
    Node_ll X = Node_ll(34, a, H);
    cout << L.head << endl;
    L.addNode(X);
    L.Display();
}