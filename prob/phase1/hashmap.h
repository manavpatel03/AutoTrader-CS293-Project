#include <iostream>
#include "AVL.h"
#define SIZE 69

class hashMap
{
public:
    hashMap()
    {
        Bucket.resize(SIZE, NULL);
    }

    hashMap(hashMap *sample)
    {
        hashMap M = hashMap();
        for (int i = 0; i < SIZE; i++)
        {

            if (sample->Bucket[i] != NULL)
                M.Bucket[i] = sample->Bucket[i]->copynode();
        }
    }

    vector<Node *> Bucket;

    void print_tree()
    {
        cout << "-----------NEW tree------" << endl;
        for (int i = 0; i < 69; i++)
        {
            if (Bucket[i] != NULL)
            {
                cout << i << "." << endl;
                Bucket[i]->inorderwalk(Bucket[i]);
            }
        }
        cout << "-----------END------" << endl
             << endl;
    }

    bool Checkzero()
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (Bucket[i] != NULL)
            {
                if (Bucket[i]->walkcheck() == false)
                    return false;
            }
        }
        return true;
    }

    int hashVal(string K)
    {
        int h = 0;  // Initialize the hash value to 0
        int p = 31; // Choose a prime number as the base
        int m = 69; // Choose a number slightly larger than the desired range

        for (char c : K)
        {
            // Update the hash value using the formula of the polynomial rolling hash
            h = (h * p + c) % m;
        }

        return h;
        // return 1;
    }

    int *search_Val(string k) { return Bucket[hashVal(k)]->search(k); }
    void addtoBucket(hashMap X, Node *src)
    {
        if (src == NULL)
            return;
        X.addorinsert(src->key, src->value);
        addtoBucket(X, src->left);
        addtoBucket(X, src->right);
        return;
    }
    void addMap(hashMap *X)
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (X->Bucket[i] != NULL)
            {
            }
        }
    }

    void addorinsert(string K, int val)
    {
        int ind = hashVal(K);
        if (Bucket[ind] == NULL)
        {
            Bucket[ind] = new Node();
            Bucket[ind]->left = NULL;
            Bucket[ind]->right = NULL;
            Bucket[ind]->value = val;
            Bucket[ind]->height = 1;
            Bucket[ind]->key = K;
            return;
        }
        else
        {
            if (Bucket[ind]->search(K) == NULL)
            {
                Bucket[ind]->inBST(K, val);
            }
            else
            {
                int *ptr = Bucket[ind]->search(K);
                *ptr += val;
            }
            // cout << "end" << endl;
            return;
        }
    }
};