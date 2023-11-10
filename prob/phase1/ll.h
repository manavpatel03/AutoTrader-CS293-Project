#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Node {
public:
    int price;
    vector<bool> validity;
    map<int, int> map2;
    Node* next;

    // Default constructor
    Node() : price(0), validity(vector<bool>()), map2(map<int, int>()), next(NULL) {}

    // Parameterized constructor
    Node(int price, vector<bool> validity, map<int, int> map2) : price(price), validity(validity), map2(map2), next(NULL) {}

    // Copy constructor
    Node(const Node& node) : price(node.price), validity(node.validity), map2(node.map2), next(NULL) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(NULL), tail(NULL) {}

    ~LinkedList() {
        Node* current = head;
        Node* next = NULL;

        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }

        head = NULL;
        tail = NULL;
    }

    Node *addNode(map<int, int> x, vector<bool> y, int z) {
        Node* newNode = new Node(z, y, x);

        if(head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        return newNode;
    }
};
