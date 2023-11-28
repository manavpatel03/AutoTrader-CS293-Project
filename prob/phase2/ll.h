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
    int in_time;
    int out_time;
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
        in_time = 0;
        out_time = 0;
        // diff = 0;
    }

    Node2 *Newnode2(hashMap *M, int cost, int count, char buy, int in_tim, int outtime, string broker)
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
        plc->in_time = in_tim;
        for (int i = 0; i < broker.size(); i++)
        {
            plc->Broke.push_back(broker[i]);
        }
        if (outtime == -1)
        {
            plc->out_time = INT32_MAX;
        }
        else
        {
            plc->out_time = in_tim + outtime;
        }
        // plc->diff = dif;
        return plc;
    }

    void ins(Node2 *newroot)
    {
        // cout << "here" << endl;
        if (newroot->price > price)
        {
            if (right == NULL)
                right = newroot;
            else
                right->ins(newroot);
        }
        else if (newroot->price == price)
        {
            Node2 *itr = this;
            while (itr->ll_next != NULL)
            {
                assert(itr != itr->ll_next);
                itr = itr->ll_next;
                // cout << "here" << endl;
            }
            itr->ll_next = newroot;
            newroot->ll_next = NULL;
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

    void yo_dec(char b, hashMap *H, bool done, vector<Node2 *> &pusher, int intime)
    {
        if (!done)
            return;
        if (left != NULL)
        {
            left->yo_dec(b, H, done, pusher, intime);
        }
        Node2 *itr = this;
        while (itr != NULL)
        {
            if (b != itr->buy && itr->mystocks->compmap(H) && itr->valid && itr->out_time >= intime)
            {
                done = false;
                pusher.push_back(itr);
            }
            itr = itr->ll_next;
        }
        if (!done)
            return;
        if (right != NULL)
        {
            right->yo_dec(b, H, done, pusher, intime);
        }
    }

    void yo_inc(char b, hashMap *H, bool done, vector<Node2 *> &pusher, int intime)
    {
        if (!done)
            return;
        if (right != NULL)
        {
            right->yo_dec(b, H, done, pusher, intime);
        }
        Node2 *itr = this;
        while (itr != NULL)
        {
            if (b != itr->buy && itr->mystocks->compmap(H) && itr->valid && itr->out_time >= intime)
            {
                done = false;
                pusher.push_back(itr);
            }
            itr = itr->ll_next;
        }
        if (!done)
            return;
        if (left != NULL)
        {
            left->yo_dec(b, H, done, pusher, intime);
        }
        return;
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

    void insert(Node2 *A)
    {
        // cout << A->in_time << " " << vect.size() << endl;
        // assert(A->in_time <= vect.size());
        if (vect.size() <= A->in_time)
        {
            int i = vect.size();
        }
        else
            vect[A->in_time]->ins(A);
        return;
    }

    void Bestdeal(Node2 *x, vector<Node2 *> &Deals)
    {
        // assert(x != NULL);
        vector<Node2 *> Res;
        if (x->buy)
        {
            for (int i = 0; i < vect.size(); i++)
            {
                if (vect[i] != NULL)
                {
                    bool done = 1;
                    // Res.push_back(vect[i]->yo_inc(b, H));
                    vect[i]->yo_dec('b', x->mystocks, done, Res, x->in_time);
                }
            }
            // cout << "dfs" << endl;

            if (Res.size() == 0)
            {
                return;
            }
            else
            {
                // cout << "grfs" << endl;
                // sort Res here -x-x-x-x-x-x-x-x--x-xx-x-x-
                sortNodes(Res, 1);
                //  int max_price = my_price;
                // Node2 *X = NULL;
                int q = x->quant;
                for (int i = 0; i < Res.size(); i++)
                {
                    if (Res[i] != NULL)
                    {
                        if (Res[i]->price <= x->price)
                        {
                            // max_price = Res[i]->price;
                            // X = Res[i];
                            if (q <= 0)
                                return;
                            cout << x->Broke << endl;
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

        if (!x->buy)
        {
            for (int i = 0; i < vect.size(); i++)
            {
                if (vect[i] != NULL)
                {
                    bool done = 1;
                    // Res.push_back(vect[i]->yo_inc(b, H));
                    vect[i]->yo_dec('b', x->mystocks, done, Res, x->in_time);
                }
            }
            if (Res.size() == 0)
                return;
            else
            {
                sortNodes(Res, 0);
                // int max_price = my_price;
                Node2 *X = NULL;
                int q = x->quant;
                for (int i = 0; i < Res.size(); i++)
                {
                    if (Res[i] != NULL)
                    {
                        if (Res[i]->price >= x->price)
                        {
                            // max_price = Res[i]->price;
                            // X = Res[i];
                            if (q <= 0)
                                return;
                            cout << x->Broke << endl;
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
    int compareNodess(const Node2 *a, const Node2 *b)
    {
        // Sort by price (decreasing)
        if (a->price != b->price)
        {
            return a->price < b->price ? -1 : 1;
        }

        // If prices are equal, sort by in_time (increasing)
        if (a->in_time != b->in_time)
        {
            return a->in_time < b->in_time ? -1 : 1;
        }

        // If in_time is also equal, sort alphabetically by Broke
        return a->Broke.compare(b->Broke);
    }

    int compareNodesb(const Node2 *a, const Node2 *b)
    {
        // Sort by price (decreasing)
        if (a->price != b->price)
        {
            return a->price > b->price ? -1 : 1;
        }

        // If prices are equal, sort by in_time (increasing)
        if (a->in_time != b->in_time)
        {
            return a->in_time < b->in_time ? -1 : 1;
        }

        // If in_time is also equal, sort alphabetically by Broke
        return a->Broke.compare(b->Broke);
    }

    // Quicksort partition function
    int partition(std::vector<Node2 *> &nodes, int low, int high)
    {
        Node2 *pivot = nodes[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (compareNodesb(nodes[j], pivot) == -1)
            {
                i++;
                Node2 *A = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = A;
                // std::swap(nodes[i], nodes[j]);
            }
        }

        Node2 *A = nodes[i + 1];
        nodes[i + 1] = nodes[high];
        nodes[high] = A;
        // std::swap(nodes[i + 1], nodes[high]);
        return i + 1;
    }

    int partition2(std::vector<Node2 *> &nodes, int low, int high)
    {
        Node2 *pivot = nodes[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (compareNodess(nodes[j], pivot) == -1)
            {
                i++;
                // std::swap(nodes[i], nodes[j]);
                Node2 *A = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = A;
            }
        }

        // std::swap(nodes[i + 1], nodes[high]);
        Node2 *A = nodes[i + 1];
        nodes[i + 1] = nodes[high];
        nodes[high] = A;
        return i + 1;
    }

    // Quicksort function
    void quicksort(std::vector<Node2 *> &nodes, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(nodes, low, high);

            quicksort(nodes, low, pi - 1);
            quicksort(nodes, pi + 1, high);
        }
    }

    void quicksort2(std::vector<Node2 *> &nodes, int low, int high)
    {
        if (low < high)
        {
            int pi = partition2(nodes, low, high);

            quicksort2(nodes, low, pi - 1);
            quicksort2(nodes, pi + 1, high);
        }
    }

    // Function to sort vector of Node2*
    void sortNodes(std::vector<Node2 *> &nodes, bool b)
    {
        if (!b)
        {
            quicksort(nodes, 0, nodes.size() - 1);
        }
        else
        {
            quicksort2(nodes, 0, nodes.size() - 1);
        }
    }
};
