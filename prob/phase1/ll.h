#include <iostream>
#include "map2.h"
#include <vector>
using namespace std;

class Node
{
public:
    int price;
    vector<int> validity;
    Map2 store;
    Node *next;

    // Default constructor
    Node() : price(0), validity(vector<int>()), store(Map2()), next(NULL) {}

    // Parameterized constructor
    Node(int price, vector<int> validity, Map2 store) : price(price), validity(validity), store(store), next(NULL) {}

    // Copy constructor
    Node(const Node &node) : price(node.price), validity(node.validity), store(node.store), next(NULL) {}
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

    Node *addNode(Map2 x, vector<int> y, int z)
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
        return newNode;
    }
    void Display()
    {
        Node *itr = head;
        while (itr != tail && itr != NULL)
        {
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
            cout << "Price is : " << itr->price << endl;
            cout << "Here are the validity vectors : ";
            for (int i = 0; i < itr->validity.size(); i++)
            {
                cout << itr->validity[i] << " ";
            }
            cout << endl;
            itr->store.inorderTraversal();
        }
    }
    void addtoLC(Map2 Store, int price, int ind)
    {
        Node *starter = head;
        Node *stopper = tail;
        while (starter != stopper)
        {
            Node x = Node(*starter);
            tail->next = &x;
            add_2nd_to_1st(&tail->store, &Store);
            tail->price += price;
            starter = starter->next;
            tail->validity.push_back(ind);
        }
        Node x = Node(*starter);
        tail->next = &x;
        add_2nd_to_1st(&tail->store, &Store);
        tail->price += price;
        tail->validity.push_back(ind);
        // create a new node for this order
        addNode(Store, vector<int>(1, ind), price);
        return;
    }
    void add_2nd_to_1st(Map2 *a, Map2 *b)
    {
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
