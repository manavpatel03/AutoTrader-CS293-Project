#include <iostream>
#include <string>
// #include "map2.h"
#include <cassert>
#include "stockstruct.h"
// #include "ll.h"

using namespace std;

int main()
{
    int n = 400;
    Com_list *S = new Com_list();
    // S->addtolist("kargo", 4 * 2 + 4, 0);
    // S->addtolist("qwer", 2 * 9 + 4, 0);
    // S->addtolist(4 * 6 + 2, 'b', 0);

    Company *com = new Company();

    for (int i = 0; i < 100; i++)
    {
        S->addtolist("kargo", i * 2 + 4, i);
        S->addtolist("qwer", i * 9 + 4, i);
        S->addtolist(i * 6 + 2, 'b', i);
        if (i == 44)
        {
            com->insertion("kargo", i * 2 + 4);
            com->insertion("qwer", i * 9 + 4);
            com->insertion('s');
            com->insertion(i * 6 + 2);
        }
    }
    // com->insertion("kargo", 6);
    // com->insertion('s');
    // S->addtolist("qwer", 13, 1);
    // com->insertion(8);

    vector<int> x;
    cout << S->checkcancel(com, x);
    cout << x[0];
}