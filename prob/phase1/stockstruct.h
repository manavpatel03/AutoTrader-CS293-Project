#include <iostream>
#include <cassert>
#include "hashmap.h"

class Company
{
public:
    hashMap *Pairs;
    int price;
    // int identifier;
    bool buy;

    Company()
    {
        Pairs = new hashMap();

        price = 0;
        buy = 0;
        // identifier = 0;
    }

    void insertion(string cmpny, int quant)
    {
        // cout << &Pairs << endl;
        Pairs->addorinsert(cmpny, quant);
        // price = cost;
        // buy = buy;
        return;
    }

    void insertion(int cost)
    {
        price = cost;
        return;
    }

    void insertion(char decide)
    {
        buy = (decide == 'b');
        return;
    }

    bool compareOppsame(Company *a)
    {
        if (price != a->price)
            return false;
        if (buy == a->buy)
            return false;
        if (a->Pairs->compmap(Pairs))
            return true;
        else
            return false;
    }
};

class Com_list
{
public:
    vector<Company *> LCs;

    Com_list()
    {
        LCs.resize(0);
    }

    void addtolist(string cmpny, int quant, int ind)
    {
        assert(ind <= LCs.size());
        if (ind == LCs.size())
        {
            Company *s = new Company();
            // cout << &s->Pairs->Bucket << endl;
            s->insertion(cmpny, quant);
            // cout << "gd" << endl;
            LCs.push_back(s);
        }
        else
        {
            LCs[ind]->insertion(cmpny, quant);
        }
        return;
    }

    void addtolist(int cost, char fst, int ind)
    {
        assert(ind < LCs.size());
        LCs[ind]->price = cost;
        LCs[ind]->buy = (fst == 'b');
    }

    bool checkcancel(Company *S, vector<int> &ret)
    {
        for (int i = 0; i < LCs.size(); i++)
        {
            if (LCs[i]->compareOppsame(S))
            {
                ret.push_back(i);
                return true;
            }
        }
        return false;
    }
    // Company_struct()
    // {
    //     // price = 0;
    //     // buy = 0;
    //     LCs.resize(1);
    // }
};