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
            // cout << "dfsfsfsfsdfsdfsdfsfsd";
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
        // cout << "dfdfsf";
        // S->Display();
        // cout << "dfdfsf";
        // S->Display();
        // cout << (head == NULL) << endl;
        // cout << "\n\n\n\n\n1\n\n\n\n";
        // S->Display();
        if (head == NULL)
        {
            head = S->head;
            tail = S->tail;
        }
        // assert(tail->next == NULL);
        else
        {

            // cout << endl
            //      << "dffsfsdfsdfs" << endl;
            tail->next = S->head;
            // assert(tail->next != NULL);
            tail = S->tail;
        }
        // assert(tail->next == S->head);
        // cout << "2\n\n\n\n\n";
        // Display();
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
            if (tail == node)
                tail = NULL;
            delete temp;
        }
        else
        {
            while (prev->next != node && prev->next != NULL)
            {
                prev = prev->next;
            }
            if (tail == node)
                tail = prev;
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

    bool compareOppsame(Company *a, bool &same)
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
            if (price == a->price)
            {
                if (buy == a->buy)
                    return false;
                else if (a->Pairs->compmap(Pairs))
                {
                    valid = 0;
                    a->valid = 0;
                    same = true;
                    return true;
                }
                return false;
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

    void removeused(vector<int> &del)
    {
        for (int i = 0; i < del.size(); i++)
        {
            LCs[del[i]]->valid = 0;
        }
    }

    bool checkcancel(Company *S, vector<int> &ret, bool &same)
    {
        for (int i = 0; i < LCs.size() - 1; i++)
        {
            if (LCs[i]->compareOppsame(S, same))
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
    Node2 *ll_next;
    int price;
    int quant;
    int j;
    bool buy;
    string Broke;
    bool valid;
    // int diff;

    Node2()
    {
        left = NULL;
        right = NULL;
        mystocks = new hashMap();
        ll_next = NULL;
        price = 0;
        quant = 0;
        buy = 0;
        Broke.assign("");
        j = 0;
        // diff = 0;
    }

    Node2 *Newnode2(hashMap *M, int cost, int count, char buy, int jval)
    {
        Node2 *plc = new Node2();
        plc->left = NULL;
        plc->right = NULL;
        plc->mystocks = M;
        plc->price = cost;
        plc->quant = count;
        plc->buy = (buy == 'b');
        plc->ll_next = NULL;
        plc->valid = 1;
        plc->j = jval;
        plc->Broke.assign("");
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
        if (newroot->price == price)
        {
            Node2 *itr = ll_next;
            while (itr != NULL)
                itr = itr->ll_next;
            itr->ll_next = newroot;
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

    bool isrch(int cost, hashMap *H, char b)
    {
        if (price == cost)
        {
            Node2 *itr = this;
            while (itr != NULL)
            {
                if (b != itr->buy)
                {
                    if (itr->mystocks->compmap(H) && itr->valid)
                    {
                        itr->valid = 0;
                        return true;
                    }
                }
                itr = itr->ll_next;
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
        return false;
    }

    Node2 *yo_dec(char b, hashMap *H)
    {
        if (left != NULL)
        {
            Node2 *x = left->yo_dec(b, H);
            if (x != NULL)
                return x;
        }
        vector<Node2 *> my_node;
        vector<string> my_strings;
        Node2 *itr = this;
        while (itr != NULL)
        {
            if (itr->valid && itr->mystocks->compmap(H) && itr->buy != b)
            {
                my_node.push_back(itr);
                my_strings.push_back(itr->Broke);
            }
            itr = itr->ll_next;
        }
        if (my_node.size() == 0)
        {
            if (right != NULL)
                return right->yo_dec(b, H);
            else
                return NULL;
        }
        else
        {
            int ret = min(my_strings);
            return my_node[ret];
        }

        // v.push_back(this);
    }

    Node2 *yo_inc(char b, hashMap *H)
    {
        if (right != NULL)
        {
            Node2 *x = right->yo_dec(b, H);
            if (x != NULL)
                return x;
        }
        vector<Node2 *> my_node;
        vector<string> my_strings;
        Node2 *itr = this;
        while (itr != NULL)
        {
            if (itr->valid && itr->mystocks->compmap(H) && itr->buy != b)
            {
                my_node.push_back(itr);
                my_strings.push_back(itr->Broke);
            }
            itr = itr->ll_next;
        }
        if (my_node.size() == 0)
        {
            if (left != NULL)
                return left->yo_dec(b, H);
            else
                return NULL;
        }
        else
        {
            int ret = min(my_strings);
            return my_node[ret];
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

class Timevect
{
public:
    vector<Node2 *> vect;
    Timevect()
    {
        vect.resize(0);
    }

    void Bestdeal(Node2 *x, bool b, int my_price, hashMap *H, vector<Node2 *> &Deals, int q)
    {
        vector<Node2 *> Res;
        if (b)
        {
            for (int i = 0; i < vect.size(); i++)
            {
                if (vect[i] != NULL)
                {
                    Res.push_back(vect[i]->yo_inc(b, H));
                }
            }
            if (Res.size() == 0)
                return;
            else
            {
                // int max_price = my_price;
                Node2 *X = NULL;
                for (int i = 0; i < Res.size(); i++)
                {
                    if (Res[i] != NULL)
                    {
                        if (Res[i]->price > my_price)
                        {
                            // max_price = Res[i]->price;
                            // X = Res[i];
                            if (q <= 0)
                                return;
                            Deals.push_back(Res[i]);
                            if (q < Res[i]->quant)
                                return;
                            else
                                q = q - Res[i]->quant;
                        }
                    }
                }
            }
        }

        if (!b)
        {
            for (int i = 0; i < vect.size(); i++)
            {
                if (vect[i] != NULL)
                {
                    Res.push_back(vect[i]->yo_dec(b, H));
                }
            }
            if (Res.size() == 0)
                return;
            else
            {
                // int max_price = my_price;
                Node2 *X = NULL;
                for (int i = 0; i < Res.size(); i++)
                {
                    if (Res[i] != NULL)
                    {
                        if (Res[i]->price > my_price)
                        {
                            // max_price = Res[i]->price;
                            // X = Res[i];
                            if (q <= 0)
                                return;
                            Deals.push_back(Res[i]);
                            if (q < Res[i]->quant)
                                return;
                            else
                                q = q - Res[i]->quant;
                        }
                    }
                }
            }
        }
    }
};

int min(vector<string> &S)
{
    int min = 0;
    for (int i = 1; i < S.size(); i++)
    {
        if (S[i] < S[min])
            min = i;
    }
    return min;
}