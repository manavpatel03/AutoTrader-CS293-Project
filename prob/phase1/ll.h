#include <iostream>
#include "map2.h"
#include <vector>
#include <cassert>
using namespace std;

class Node
{
public:
    int price;
    vector<int> validity;
    Map2 *store;
    Node *next;

    // Default constructor
    Node()
    {
        price = 0;
        validity = vector<int>();
        next = nullptr;
        // store = Map2();
    }

    // Parameterized constructor
    Node(int pri, vector<int> validy, Map2 ste)
    {
        price = pri;
        validity = vector<int>(validy);
        next = NULL;
        // store = ste.copycall(&ste);
        // store->inorderTraversal();
        // ste.inorderTraversal();
    }

    // copycall constructor
    Node(const Node &node)
    {
        price = node.price;
        validity = vector<int>(node.validity);
        next = NULL;
        // store = node.store->copycall(node.store);
    }
};

class LinkedList
{
private:
    Node *head;
    Node *tail;

public:
    LinkedList() : head(NULL), tail(NULL) {}

    ~LinkedList()
    {
        Node *current = head;
        Node *next = NULL;

        while (current != NULL)
        {
            next = current->next;
            delete current;
            current = next;
        }

        head = NULL;
        tail = NULL;
    }

    void addNode(Node newNode)
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
        return;
    }

    void addNode(Map2 x, vector<int> y, int z)
    {
        Node *newNode = new Node(z, y, x);

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
        Node *itr = head;
        if (head == nullptr && tail == nullptr)
            cout << "bhai null hia";
        while (itr != tail && itr != NULL)
        {
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
            cout << "Price is : " << itr->price << endl;
            cout << "Here are the validity vectors : ";
            for (int i = 0; i < itr->validity.size(); i++)
            {
                cout << itr->validity[i] << " ";
            }
            if (tail != NULL)
            {
                cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
                cout << "Price is : " << tail->price << endl;
                cout << "Here are the validity vectors : ";
                for (int i = 0; i < tail->validity.size(); i++)
                {
                    cout << tail->validity[i] << " ";
                }
            }
            cout << endl;
            itr->store->inorderTraversal();
        }
    }
    void addtoLC(Map2 Store, int price, int ind)
    {
        Node *starter = head;
        Node *stopper = tail;
        cout << "fsfsdfdfsdfsd" << endl;
        // assert(starter != stopper);
        while (starter != stopper && starter != nullptr)
        {
            Node x = Node(*starter);
            // tail->next = &x;
            addNode(x);
            add_2nd_to_1st(tail->store, &Store);
            tail->price += price;
            starter = starter->next;
            tail->validity.push_back(ind);
        }
        if (starter != nullptr)
        {
            Node x = Node(*starter);
            // cout << "fsfsdfdfsdfsd" << endl;
            tail->next = &x;
            // add_2nd_to_1st(&tail->store, &Store);
            tail->price += price;
            tail->validity.push_back(ind);
        }
        // create a new node for this order
        addNode(Store, vector<int>(1, ind), price);
        return;
    }
    void add_2nd_to_1st(Map2 *a, Map2 *b)
    {
        // cout << "fsfsdfdfsdfsd" << endl;
        if (b != nullptr)
        {
            add_2nd_to_1st(a, b->left);
            // Process the current a (e.g., print or store the key-value pair)
            Map2 *curr = a->find(b->first);
            if (curr == nullptr)
            {
                a->insert(b->first, b->second);
            }
            else
            {
                curr->second += b->second;
            }
            add_2nd_to_1st(a, b->right);
        }
        return;
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
    void deleteNode(Node *node)
    {
        Node *prev = head;
        if (head == NULL || tail == NULL)
        {
            return;
        }
        if (head == node)
        {
            Node *temp = head;
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
        Node *current = head;
        Node *a = head;
        while (current != NULL)
        {
            for (int i = 0; i < used_up.size(); i++)
            {
                if (binary_search(used_up[i], current->validity))
                {
                    a = current->next;
                    deleteNode(current);
                    break;
                }
            }
            current = a;
        }
    }

    vector<int> getarbitrage(int &profit)
    {
        Node *minnode = nullptr;
        int maxpric = INT32_MIN;
        Node *itr = head;
        while (itr != NULL)
        {
            if (checkzeros(itr->validity))
            {
                if (itr->price > maxpric)
                    minnode = itr;
            }
        }
        if (minnode == nullptr || maxpric <= 0)
        {
            return vector<int>();
        }
        profit = maxpric;
        return minnode->validity;
    }
};
