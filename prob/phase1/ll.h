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
            if (X->Bucket[i] == NULL)
                continue;
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
            for (int i = 0; i < SIZE; i++)
            {
                add2ndto1st(&Store, itr->store);
            }
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
        while (current != NULL)
        {
            bool chi = 0;
            for (int i = 0; i < used_up.size(); i++)
            {
                if (binary_search(used_up[i], current->validity))
                {
                    a = current->next;
                    deleteNode(current);
                    chi = 1;
                    break;
                }
            }
            if (chi)
                continue;
            current = current->next;
        }
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
            if (checkzeros(itr->validity))
            {
                if (itr->price > maxpric)
                    minnode = itr;
            }
            itr = itr->next;
        }
        if (minnode == nullptr || maxpric <= 0)
        {
            return vector<int>();
        }
        profit = maxpric;
        return minnode->validity;
    }
};
