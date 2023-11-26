#include <iostream>
#include "hashmap.h"
#include <vector>
#include <cassert>
using namespace std;

class Node_ll
{
public:
    int price;
    vector<int> validity;
    hashMap *store;
    Node_ll *next;

    // Default constructor
    Node_ll()
    {
        price = 0;
        validity = vector<int>();
        next = nullptr;
        // store = Map2();
    }

    // Parameterized constructor
    Node_ll(int pri, vector<int> validy, hashMap *ste)
    {
        price = pri;
        validity = vector<int>(validy);
        next = NULL;
        store = ste->Mapmaker(ste);
        // store->inorderTraversal();
        // ste.inorderTraversal();
    }

    // copycall constructor
    Node_ll(const Node_ll &node)
    {
        price = node.price;
        validity = vector<int>(node.validity);
        next = NULL;
        // store = node.store->copycall(node.store);

        hashMap *f = node.store->Mapmaker(node.store);
        store = f;
    }
};

class LinkedList
{

public:
    Node_ll *head;
    Node_ll *tail;
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    ~LinkedList()
    {
        Node_ll *current = head;
        Node_ll *next = NULL;

        while (current != NULL)
        {
            next = current->next;
            delete current;
            current = next;
        }

        head = NULL;
        tail = NULL;
    }

    void addNode(Node_ll &newNode)
    {
        if (head == NULL)
        {
            head = &newNode;
            tail = &newNode;
            tail->next = NULL;
        }
        else
        {
            tail->next = &newNode;
            tail = &newNode;
            tail->next = NULL;
        }
        // std::cout << "chal" << endl;
        return;
    }

    void addNode(hashMap *x, vector<int> y, int z)
    {
        // cout << "d0 " << endl;
        Node_ll *newNode = new Node_ll(z, y, x);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        return;
    }
    void Display()
    {
        Node_ll *itr = head;
        if (head == nullptr && tail == nullptr)
            cout << "bhai null hia";
        while (itr != NULL)
        {
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
            cout << "Price is : " << itr->price << endl;
            cout << "Here are the validity vectors : ";
            for (int i = 0; i < itr->validity.size(); i++)
            {
                cout << itr->validity[i] << " ";
            }
            // if (tail != NULL)
            // {
            //     cout << endl
            //          << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
            //     cout << "Price is : " << tail->price << endl;
            //     cout << "Here are the validity vectors : ";
            //     for (int i = 0; i < tail->validity.size(); i++)
            //     {
            //         cout << tail->validity[i] << " ";
            //     }
            // }
            cout << endl;
            itr->store->print_tree();
            itr = itr->next;
        }
    }
    void add2ndto1st(hashMap *X, hashMap *destination)
    {
        for (int i = 0; i < SIZE; i++)
        {
            destination->addMap(X->Bucket[i]);
        }
    }

    void addtoLC(hashMap &Store, int pr, int ind)
    {
        vector<int> w;
        w.push_back(ind);
        if (head == NULL)
        {

            addNode(&Store, w, pr);
            return;
        }
        LinkedList *S = duplicateLL();
        Node_ll *itr = S->head;
        while (itr != NULL)
        {
            itr->price += pr;
            itr->validity.push_back(ind);
            add2ndto1st(&Store, itr->store);
            itr = itr->next;
        }
        S->addNode(&Store, w, pr);
        tail->next = S->head;
        tail = S->tail;
        return;
    }

    LinkedList *duplicateLL()
    {
        LinkedList *L = new LinkedList();
        L->head = NULL;
        L->tail = NULL;
        if (head == NULL)
        {
            return L;
        }
        else
        {
            // int i = 0;
            Node_ll *itr = head;
            while (itr != NULL)
            {
                // cout << itr->price << endl;
                L->addNode(itr->store, itr->validity, itr->price);
                // L->tail->next = NULL;
                itr = itr->next;
            }
            return L;
        }
    }

    bool checkzeros(vector<int> V)
    {
        for (int i = 0; i < V.size(); i++)
        {
            if (V[i] != 0)
                return false;
        }
        return true;
    }
    void deleteNode(Node_ll *node)
    {
        Node_ll *prev = head;
        if (head == NULL || tail == NULL)
        {
            return;
        }
        if (head == node)
        {
            Node_ll *temp = head;
            head = node->next;
            delete temp;
        }
        else
        {
            while (prev->next != node && prev->next != NULL)
            {
                prev = prev->next;
            }
            prev->next = node->next;
        }
    }
    bool binary_search(int q, vector<int> a)
    {
        int size = a.size();
        int first = 0;
        int last = size - 1;
        while (first <= last)
        {
            if (q == a[(first + last) / 2])
                return true;
            else if (q < a[(first + last) / 2])
            {
                last = ((first + last) / 2) - 1;
            }
            else
            {
                first = 1 + ((first + last) / 2);
            }
        }
        return false;
    }
    void remove_invalid(vector<int> used_up)
    {
        Node_ll *current = head;
        Node_ll *a = head;
        // int die = 0;
        while (current != NULL)
        {
            // cout << ++die << endl;
            bool chi = 0;
            for (int i = 0; i < used_up.size(); i++)
            {
                if (binary_search(used_up[i], current->validity))
                {
                    a = current;
                    current = current->next;
                    deleteNode(a);
                    chi = 1;
                    break;
                }
            }
            if (chi)
            {
                chi = 0;
                continue;
            }
            if (current != NULL)
                current = current->next;
        }
        // cout << "DONE!!" << endl;
        return;
    }

    vector<int> getarbitrage(int &profit)
    {
        Node_ll *minnode = nullptr;
        int maxpric = INT32_MIN;
        Node_ll *itr = head;
        // int i = 0;
        while (itr != NULL)
        {
            // cout << i++ << endl;
            if (itr->store->checkquant())
            {
                // cout << "her";
                if ((itr->price > maxpric) || (itr->price == maxpric && minnode != NULL && minnode->validity.size() > itr->validity.size()))
                {
                    minnode = itr;
                    maxpric = itr->price;
                    // cout << "her";
                }
            }
            itr = itr->next;
        }
        if (minnode == nullptr || maxpric <= 0)
        {
            // cout << "ff" << endl;
            return vector<int>();
        }
        profit = maxpric;
        // cout << minnode->validity.size() << endl;
        return minnode->validity;
    }
};

class Company
{
public:
    hashMap *Pairs;
    bool valid;
    int price;
    // int identifier;
    bool buy;

    Company()
    {
        Pairs = new hashMap();
        valid = 1;
        price = 0;
        buy = 0;
        // identifier = 0;
    }

    void insertion(string cmpny, int quant)
    {
        valid = 1;
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
        // if (a->valid == 0 || valid == 0)
        //     return false;
        // if (price == a->price)
        // {
        //     if (buy == a->buy)
        //         return false;
        //     else if (a->Pairs->compmap(Pairs))
        //     {
        //         valid = 0;
        //         a->valid = 0;
        //         return true;
        //     }
        //     return false;
        // }
        // // return false;
        // if (((buy && price < a->price) || (!buy && price > a->price)))
        //     return false;
        // if (a->Pairs->compmap(Pairs))
        // {
        //     valid = 0;
        //     // a->valid = 0;
        //     return true;
        // }
        // else
        //     return false;

        if (a->valid == 0 || valid == 0)
            return false;
        if (buy == a->buy)
        {
            if (((buy && price < a->price) || (!buy && price > a->price)))
                return false;
            if (a->Pairs->compmap(Pairs))
            {
                valid = 0;
                // a->valid = 0;
                return true;
            }
            else
                return false;
        }
        else
        {
            if (a->Pairs->compmap(Pairs))
            {
                valid = 0;
                a->valid = 0;
                return true;
            }
            return false;
        }
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

class Node2
{
public:
    Node2 *left;
    Node2 *right;
    hashMap *mystocks;
    int price;
    int quant;
    bool buy;
    // int diff;

    Node2()
    {
        left = NULL;
        right = NULL;
        mystocks = new hashMap();
        price = 0;
        quant = 0;
        buy = 0;
        // diff = 0;
    }

    Node2 *Newnode2(hashMap *M, int cost, int count, char buy)
    {
        Node2 *plc = new Node2();
        plc->left = NULL;
        plc->right = NULL;
        plc->mystocks = M;
        plc->price = cost;
        plc->quant = count;
        plc->buy = (buy == 'b');
        // plc->diff = dif;
        return plc;
    }

    void ins(Node2 *newroot)
    {
        if (newroot->price > price)
        {
            if (right == NULL)
                right = newroot;
            else
                right->ins(newroot);
        }
        else
        {
            if (left == NULL)
                left = newroot;
            else
                left->ins(newroot);
        }
        return;
    }

    Node2 *isrch(int cost, hashMap *H, char b)
    {
        if (price == cost)
        {
            if (b != buy)
            {
                if (mystocks->compmap(H))
                {
                    return this;
                }
            }
        }
        if (cost < price && left != NULL)
        {
            return left->isrch(cost, H, b);
        }
        if (cost > price && right != NULL)
        {
            return right->isrch(cost, H, b);
        }
        return NULL;
    }

    void yo2(char b, hashMap *H, vector<Node2 *> &v)
    {
        if (left != NULL)
        {
            left->yo2(b, H, v);
        }
        if (b != buy && mystocks->compmap(H))
        {
            v.push_back(this);
        }
        if (right != NULL)
        {
            right->yo2(b, H, v);
        }
    }

    void yo1(char b, hashMap *H, vector<Node2 *> &v)
    {
        if (right != NULL)
        {
            right->yo1(b, H, v);
        }
        if (b != buy && mystocks->compmap(H))
        {
            v.push_back(this);
        }
        if (left != NULL)
        {
            left->yo1(b, H, v);
        }
    }

    // Node2 *dsrch(int cost, hashMap *H, char b)
    // {
    //     if (left != NULL)
    //         return left->isrch(price, H, b);
    //     if (price == cost)
    //     {
    //         if (b != buy)
    //         {
    //             if (mystocks->compmap(H))
    //             {
    //                 return this;
    //             }
    //         }
    //     }
    //     if (right != NULL)
    //         return right->isrch(cost, H, b);
    //     return NULL;
    // }
};