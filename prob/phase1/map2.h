// map.h

// C++ Program to implement Map class(using AVL tree)
// This is a header file map.h and doesnot contain main()

#include <iostream>
#include <string>
using namespace std;

// Custom Map Class
class Map2
{
private:
    Map2 *iterator(std::string first)
    {
        // A temporary variable created
        // so that we do not
        // lose the "root" of the tree
        Map2 *temp = root;

        // Stop only when either the key is found
        // or we have gone further the leaf node
        while (temp != nullptr &&
               temp->first != first)
        {

            // Go to left if key is less than
            // the key of the traversed node
            if (first < temp->first)
            {
                temp = temp->left;
            }

            // Go to right otherwise
            else
            {
                temp = temp->right;
            }
        }
        // If there doesn't exist any element
        // with first as key, nullptr is returned
        return temp;
    }

    // Returns the pointer to element
    // whose key matches first.
    // Specially created for search method
    // (because search() is const qualified).
    const Map2 *iterator(std::string first) const
    {
        Map2 *temp = root;
        while (temp != nullptr && temp->first != first)
        {
            if (first < temp->first)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return temp;
    }

    // The const property is used to keep the
    // method compatible with the method "const
    // int&[]operator(int) const"
    // Since we are not allowed to change
    // the class attributes in the method
    // "const int&[]operator(int) const"
    // we have to assure the compiler that
    // method called(i.e "search") inside it
    // doesn't change the attributes of class

    // Utility function to return the Map2* object
    // with its members initialized
    // to default values except the key
    Map2 *create(std::string first)
    {
        Map2 *newnode = (Map2 *)malloc(sizeof(Map2));
        newnode->first = first;
        newnode->second = 0;
        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->par = nullptr;

        // Depth of a newnode shall be 1
        // and not zero to differentiate
        // between no child (which returns
        // nullptr) and having child(returns 1)
        newnode->depth = 1;
        return newnode;
    }

    // All the rotation operation are performed
    // about the node itself
    // Performs all the linking done when there is
    // clockwise rotation performed at node "x"
    void right_rotation(Map2 *x)
    {
        Map2 *y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
        {
            y->right->par = x;
        }
        if (x->par != nullptr && x->par->right == x)
        {
            x->par->right = y;
        }
        else if (x->par != nullptr && x->par->left == x)
        {
            x->par->left = y;
        }
        y->par = x->par;
        y->right = x;
        x->par = y;
    }

    // Performs all the linking done when there is
    // anti-clockwise rotation performed at node "x"
    void left_rotation(Map2 *x)
    {
        Map2 *y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
        {
            y->left->par = x;
        }
        if (x->par != nullptr && x->par->left == x)
        {
            x->par->left = y;
        }
        else if (x->par != nullptr && x->par->right == x)
        {
            x->par->right = y;
        }
        y->par = x->par;
        y->left = x;
        x->par = y;
    }

    // Draw the initial and final graph of each
    // case(take case where every node has two child)
    // and update the nodes depth before any rotation
    void helper(Map2 *node)
    {
        // If left skewed
        if (depthf(node->left) - depthf(node->right) > 1)
        {

            // If "depth" of left subtree of
            // left child of "node" is
            // greater than right
            // subtree of left child of "node"
            if (depthf(node->left->left) > depthf(node->left->right))
            {
                node->depth = max(depthf(node->right) + 1,
                                  depthf(node->left->right) + 1);
                node->left->depth = max(depthf(node->left->left) + 1,
                                        depthf(node) + 1);
                right_rotation(node);
            }

            // If "depth" of right subtree
            // of left child of "node" is
            // greater than
            // left subtree of left child
            else
            {
                node->left->depth = max(
                    depthf(node->left->left) + 1,
                    depthf(node->left->right->left) + 1);
                node->depth = max(depthf(node->right) + 1,
                                  depthf(node->left->right->right) + 1);
                node->left->right->depth = max(depthf(node) + 1,
                                               depthf(node->left) + 1);
                left_rotation(node->left);
                right_rotation(node);
            }
        }

        // If right skewed
        else if (depthf(node->left) - depthf(node->right) < -1)
        {

            // If "depth" of right subtree of right
            // child of "node" is greater than
            // left subtree of right child
            if (depthf(node->right->right) > depthf(node->right->left))
            {
                node->depth = max(depthf(node->left) + 1,
                                  depthf(node->right->left) + 1);
                node->right->depth = max(depthf(node->right->right) + 1,
                                         depthf(node) + 1);
                left_rotation(node);
            }

            // If "depth" of left subtree
            // of right child of "node" is
            // greater than that of right
            // subtree of right child of "node"
            else
            {
                node->right->depth = max(
                    depthf(node->right->right) + 1,
                    depthf(node->right->left->right) + 1);
                node->depth = max(
                    depthf(node->left) + 1,
                    depthf(node->right->left->left) + 1);
                node->right->left->depth = max(depthf(node) + 1,
                                               depthf(node->right) + 1);
                right_rotation(node->right);
                left_rotation(node);
            }
        }
    }

    // Balancing the tree about the "node"
    void inorderTraversal(const Map2 *node) const
    {
        if (node != nullptr)
        {
            inorderTraversal(node->left);
            // Process the current node (e.g., print or store the key-value pair)
            std::cout << "Key: " << node->first << ", Value: " << node->second << std::endl;
            inorderTraversal(node->right);
        }
    }

    void balance(Map2 *node)
    {
        while (node != root)
        {
            int d = node->depth;
            node = node->par;
            if (node->depth < d + 1)
            {
                node->depth = d + 1;
            }
            if (node == root && depthf(node->left) - depthf(node->right) > 1)
            {
                if (depthf(node->left->left) > depthf(node->left->right))
                {
                    root = node->left;
                }
                else
                {
                    root = node->left->right;
                }
                helper(node);
                break;
            }
            else if (node == root && depthf(node->left) - depthf(node->right) < -1)
            {
                if (depthf(node->right->right) > depthf(node->right->left))
                {
                    root = node->right;
                }
                else
                {
                    root = node->right->left;
                }
                helper(node);
                break;
            }
            helper(node);
        }
    }

    // Utility method to return the
    // "depth" of the subtree at the "node"
    int depthf(Map2 *node)
    {
        if (node == nullptr)

            // If it is null node
            return 0;
        return node->depth;
    }

    // Function to insert a value in map2
    Map2 *insert(std::string first)
    {
        cnt++;
        Map2 *newnode = create(first);
        if (root == nullptr)
        {
            root = newnode;
            return root;
        }
        Map2 *temp = root, *prev = nullptr;
        while (temp != nullptr)
        {
            prev = temp;
            if (first < temp->first)
            {
                temp = temp->left;
            }
            else if (first > temp->first)
            {
                temp = temp->right;
            }
            else
            {
                free(newnode);
                cnt--;
                return temp;
            }
        }
        if (first < prev->first)
        {
            prev->left = newnode;
        }
        else
        {
            prev->right = newnode;
        }
        newnode->par = prev;
        balance(newnode);
        return newnode;
    }

    // Returns the previous node in
    // inorder traversal of the AVL Tree.
    Map2 *inorderPredecessor(Map2 *head)
    {
        if (head == nullptr)
            return head;
        while (head->right != nullptr)
        {
            head = head->right;
        }
        return head;
    }

    // Returns the next node in
    // inorder traversal of the AVL Tree.
    Map2 *inorderSuccessor(Map2 *head)
    {
        if (head == nullptr)
            return head;
        while (head->left != nullptr)
        {
            head = head->left;
        }
        return head;
    }

public:
    // Root" is kept static because it's a class
    // property and not an instance property
    static class Map2 *root;
    static int cnt;

    // "first" is key and "second" is value
    Map2 *left, *right, *par;
    std::string first;
    int depth;
    int second;

    // overloaded [] operator for assignment or
    // inserting a key-value pairs in the map2
    // since it might change the members of
    // the class therefore this is
    // invoked when any assignment is done
    void inorderTraversal() const
    {
        inorderTraversal(root);
    }
    int &operator[](std::string key)
    {
        return insert(key)->second;
    }

    // Since we have two methods with
    // the same name "[]operator(int)" and
    // methods/functions cannot be
    // distinguished by their return types
    // it is mandatory to include a const
    // qualifier at the end of any of the methods

    // This method will be called from a const
    // reference to the object of Map2 class

    // It will not be called for assignment
    // because it doesn't allow to change
    // member variables

    // We cannot make it return by reference
    // because the variable "temp" returned
    // by the "search" method is
    // statically allocated and therefore
    // it's been destroyed when it is called out
    int operator[](std::string key) const
    {
        return search(key);
    }

    // Count returns whether an element
    // exists in the Map2 or not
    int count(std::string first)
    {
        Map2 *temp = iterator(first);
        if (temp != nullptr)
        {
            return 1;
        }
        return 0;
    }

    // Returns number of elements in the map2
    int size(void)
    {
        return cnt;
    }

    // Removes an element given its key
    void erase(std::string first, Map2 *temp = root)
    {
        Map2 *prev = nullptr;
        cnt--;
        while (temp != nullptr &&
               temp->first != first)
        {
            prev = temp;
            if (first < temp->first)
            {
                temp = temp->left;
            }
            else if (first > temp->first)
            {
                temp = temp->right;
            }
        }
        if (temp == nullptr)
        {
            cnt++;
            return;
        }
        if (cnt == 0 && temp == root)
        {
            free(temp);
            root = nullptr;
            return;
        }
        Map2 *l = inorderPredecessor(temp->left);
        Map2 *r = inorderSuccessor(temp->right);
        if (l == nullptr && r == nullptr)
        {
            if (prev == nullptr)
            {
                root = nullptr;
            }
            else
            {
                if (prev->left == temp)
                {
                    prev->left = nullptr;
                }
                else
                {
                    prev->right = nullptr;
                }
                free(temp);
                balance(prev);
            }
            return;
        }
        Map2 *start;
        if (l != nullptr)
        {
            if (l == temp->left)
            {
                l->right = temp->right;
                if (l->right != nullptr)
                {
                    l->right->par = l;
                }
                start = l;
            }
            else
            {
                if (l->left != nullptr)
                {
                    l->left->par = l->par;
                }
                start = l->par;
                l->par->right = l->left;
                l->right = temp->right;
                l->par = nullptr;
                if (l->right != nullptr)
                {
                    l->right->par = l;
                }
                l->left = temp->left;
                temp->left->par = l;
            }
            if (prev == nullptr)
            {
                root = l;
            }
            else
            {
                if (prev->left == temp)
                {
                    prev->left = l;
                    l->par = prev;
                }
                else
                {
                    prev->right = l;
                    l->par = prev;
                }
                free(temp);
            }
            balance(start);
            return;
        }
        else
        {
            if (r == temp->right)
            {
                r->left = temp->left;
                if (r->left != nullptr)
                {
                    r->left->par = r;
                }
                start = r;
            }
            else
            {
                if (r->right != nullptr)
                {
                    r->right->par = r->par;
                }
                start = r->par;
                r->par->left = r->right;
                r->left = temp->left;
                r->par = nullptr;
                if (r->left != nullptr)
                {
                    r->left->par = r;
                }
                r->right = temp->right;
                temp->right->par = r;
            }
            if (prev == nullptr)
            {
                root = r;
            }
            else
            {
                if (prev->right == temp)
                {
                    prev->right = r;
                    r->par = prev;
                }
                else
                {
                    prev->left = r;
                    r->par = prev;
                }
                free(temp);
            }
            balance(start);
            return;
        }
    }

    // Returns if the map2 is empty or not
    int search(std::string first) const
    {
        const Map2 *temp = iterator(first);
        if (temp != nullptr)
        {
            return temp->second;
        }
        return -1;
    }
    bool empty(void)
    {
        if (root == nullptr)
            return true;
        return false;
    }

    // Given the key of an element it updates
    // the value of the key
    bool check(std::string first)
    {
        if (iterator(first) == nullptr)
            return 0;
        return 1;
    }
    void update(std::string first, int second)
    {
        Map2 *temp = iterator(first);
        if (temp != nullptr)
        {
            temp->second = second;
        }
    }

    // Deleting the root of
    // the tree each time until the map2
    // is not empty
    void clear(void)
    {
        while (root != nullptr)
        {
            erase(root->first);
        }
    }

    // Inorder traversal of the AVL tree
    void iterate(Map2 *head = root)
    {
        if (root == nullptr)
            return;
        if (head->left != nullptr)
        {
            iterate(head->left);
        }
        cout << head->first << ' ';
        if (head->right != nullptr)
        {
            iterate(head->right);
        }
    }

    // Returns a pointer/iterator to the element
    // whose key is first
    Map2 *find(std::string first)
    {
        return iterator(first);
    }

    // Overloaded insert method,
    // takes two parameters - key and value
    void insert(std::string first, int second)
    {
        Map2 *temp = iterator(first);
        if (temp == nullptr)
        {
            insert(first)->second = second;
        }
        else
        {
            temp->second = second;
        }
    }
};

Map2 *Map2::root = nullptr;
int Map2::cnt = 0;
