#include <iostream>
#include <vector>
// #include <cmath>
#define SIZE 69

using namespace std;

class Node
{
public:
    string key;
    int value;
    Node *left;
    Node *right;
    int height;

    int height_val(Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    // A utility function to get maximum
    // of two integers
    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    /* Helper function that allocates a
       new node with the given key and
       NULL left and right pointers. */
    Node *newNode(string key, int value)
    {
        Node *node = new Node();
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->height = 1; // new node is initially
                          // added at leaf
        return (node);
    }

    bool checkq(Node *root)
    {
        if (root == NULL)
            return true;
        // cout << (value == 0) << endl;
        return (value == 0) && checkq(root->left) && checkq(root->right);
    }

    // A utility function to right
    // rotate subtree rooted with y
    // See the diagram given above.
    void inorderwalk(Node *n)
    {
        if (n == NULL)
        {
            return;
        }
        inorderwalk(n->left);
        cout << "key"
             << " " << n->key << " "
             << "value"
             << " " << n->value << endl;
        inorderwalk(n->right);
    }

    bool walkcheck()
    {
        bool l, r;
        if (value != 0)
            return false;
        if (left == NULL)
            l = 1;
        else
            l = left->walkcheck();
        if (right == NULL)
            r = 1;
        else
            r = right->walkcheck();
        return (l and r);
    }

    Node *copynode()
    {
        Node *x = new Node();
        x->height = height;
        x->key = key;
        x->value = value;
        if (left != NULL)
        {
            x->left = left->copynode();
        }
        if (right != NULL)
        {
            x->right = right->copynode();
        }
        return x;
    }

    Node *rightRotate(Node *y)
    {
        std::cout << "here?" << std::endl;
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height_val(y->left),
                        height_val(y->right)) +
                    1;
        x->height = max(height_val(x->left),
                        height_val(x->right)) +
                    1;
        std::cout << "yes" << endl;
        // Return new root
        return x;
    }

    // A utility function to left
    // rotate subtree rooted with x
    // See the diagram given above.
    Node *leftRotate(Node *x)
    {
        std::cout << "here?" << std::endl;
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height_val(x->left),
                        height_val(x->right)) +
                    1;
        y->height = max(height_val(y->left),
                        height_val(y->right)) +
                    1;

        // // Return new root
        std::cout << "yes" << endl;
        return y;
    }

    Node *deleteNode(Node *root, string key)
    {

        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL)
            return root;

        // If the key to be deleted is smaller
        // than the root's key, then it lies
        // in left subtree
        if (key < root->key)
            root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater
        // than the root's key, then it lies
        // in right subtree
        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then
        // This is the node to be deleted
        else
        {
            // node with only one child or no child
            if ((root->left == NULL) ||
                (root->right == NULL))
            {
                Node *temp = root->left ? root->left : root->right;

                // No child case
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else               // One child case
                    *root = *temp; // Copy the contents of
                                   // the non-empty child
                free(temp);
            }
            else
            {
                // node with two children: Get the inorder
                // successor (smallest in the right subtree)
                Node *temp = minValueNode(root->right);

                // Copy the inorder successor's
                // data to this node
                root->key = temp->key;

                // Delete the inorder successor
                root->right = deleteNode(root->right,
                                         temp->key);
            }
        }

        // If the tree had only one node
        // then return
        if (root == NULL)
            return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height_val(root->left),
                               height_val(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF
        // THIS NODE (to check whether this
        // node became unbalanced)
        int balance = getBalance(root);

        // If this node becomes unbalanced,
        // then there are 4 cases

        // Left Left Case
        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 &&
            getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 &&
            getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }
    // Get Balance factor of node N
    int getBalance(Node *N)
    {
        if (N == NULL)
            return 0;

        int leftHeight = (N->left == NULL) ? 0 : N->left->height;
        int rightHeight = (N->right == NULL) ? 0 : N->right->height;

        return leftHeight - rightHeight;
    }

    void inBST(string k, int val)
    {
        if (k > key)
        {
            if (right == NULL)
                right = newNode(k, val);
            else
                right->inBST(k, val);
        }
        else
        {
            if (left == NULL)
                left = newNode(k, val);
            else
                left->inBST(k, val);
        }
        return;
    }

    // Recursive function to insert a key
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    Node *insert(Node *node, string key, int value)
    {
        cout << "here" << endl;
        // /* 1. Perform the normal BST insertion */
        // if (node == NULL)
        //     return (newNode(key, value));
        // if (key < node->key)
        //     node->left = insert(node->left, key, value);
        // else if (key > node->key)
        //     node->right = insert(node->right, key, value);
        // else // Equal keys are not allowed in BST
        //     return node;
        /* 2. Update height of this ancestor node */
        // inBST(node, key, value);
        cout << "rch" << endl;
        if (left != NULL && right != NULL)
            node->height = 1 + max(node->left->height,
                                   node->right->height);
        else if (left == NULL && right != NULL)
        {
            node->height = 1 + node->right->height;
        }
        else if (right == NULL && left != NULL)
        {
            node->height = 1 + node->left->height;
        }
        else
        {
            node->height = 1;
        }

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // A utility function to print preorder
    // traversal of the tree.
    // The function also prints height
    // of every node
    void preOrder(Node *root)
    {
        if (root != NULL)
        {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    int *search(string srch)
    {
        if (srch == key)
            return &value;
        if (srch < key)
        {
            if (left == NULL)
                return NULL;
            return left->search(srch);
        }
        else
        {
            if (right == NULL)
                return NULL;
            return right->search(srch);
        }
    }
};

// A utility function to get the
// height of the tree
