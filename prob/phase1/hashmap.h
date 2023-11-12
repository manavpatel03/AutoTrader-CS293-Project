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
        for (int i = 0; i < 69; i++)
        {
            cout << i << "." << endl;
            Bucket[i]->inorderwalk(Bucket[i]);
        }
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
    }

    int *search_Val(string k) { return Bucket[hashVal(k)]->search(k); }

    int addorinsert(string K, int val)
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
                Bucket[ind]->insert(Bucket[ind], K, val);
            }
            else
            {
                int *ptr = Bucket[ind]->search(K);
                *ptr += val;
            }
        }
    }
};