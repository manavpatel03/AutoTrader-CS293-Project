#include <iostream>
#include "ll.h"

using namespace std;

int main()
{
    hashMap *H1 = new hashMap();
    Timevect *T = new Timevect();
    H1->addorinsert("a", 12);
    H1->addorinsert("b", 23);
    H1->addorinsert("d", 13);
    int quantity = 5;
    int dealprice = 200;
    int intime = 0;
    bool b = 1;
    Node2 *X;
    X = X->Newnode2(H1, dealprice, quantity, 's', intime, 45);
    // X->ll_next = NULL;
    for (int i = 0; i < 100; i++)
    {
        cout << "dsff" << endl;
        T->insert(X);
    }
    // T.vect.push_back(X);
    // for (int i = 0; i < 40; i++)
    // {
    //     hashMap *H = new hashMap();
    //     H->addorinsert(to_string(i + 45), i + 8);
    //     H->addorinsert(to_string(i + 5), i + 38);
    //     int q = 2 * i + 6;
    //     bool b = (i % 2 == 0);
    //     char sr = 'b';
    //     if (!b)
    //         sr = 's';
    //     int deal = i * 5 + 23;
    //     Node2 *s = new Node2();
    //     s = s->Newnode2(H, deal, q, sr, 0);
    //     X->ins(s);
    // }

    // hashMap *H2 = new hashMap();
    // H2->addorinsert("a", 12);
    // H2->addorinsert("b", 23);
    // H2->addorinsert("c", 13);
    // quantity = 5;
    // dealprice = 200;
    // intime = 0;
    // b = 0;
    // Node2 *S;
    // S = S->Newnode2(H2, dealprice, quantity + 1, 'b', intime);
    // X->ins(S);
    // S = S->Newnode2(H2, dealprice + 34, quantity + 2, 'b', intime);
    // T.vect.push_back(S);
    // S = S->Newnode2(H2, dealprice + 3333, quantity, 's', intime);
    // vector<Node2 *> res;
    // T.Bestdeal(S, res);
}