#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int val;
    Node *left, *right, *parent;
    Node(int val, Node *parent) : val(val), left(NULL), right(NULL), parent(parent){};
};
class BST
{
    Node *root;

public:
    BST() : root(NULL){};
    ~BST() { delete root; }

    void insertIteratively(int val)
    {
        if (root == NULL)
        {
            root = new Node(val, NULL);
            return;
        }
        Node *curr = root, *parent = NULL;
        while (curr)
        {
            parent = curr;
            curr = (curr->val > val) ? curr->left : curr->right;
        }
        (parent->val > val) ? parent->left = new Node(val, parent) : parent->right = new Node(val, parent);
    }
    Node *insertRecursively(Node *curr, int val, Node *parent)
    {
        if (curr == NULL)
            return curr = new Node(val, parent);
        if (curr->val > val)
            curr->left = insertRecursively(curr->left, val, curr);
        else
            curr->right = insertRecursively(curr->right, val, curr);
        return curr;
    }
    void insertRecursively(int val)
    {
        root = insertRecursively(root, val, NULL);
    }
    Node *search(Node *curr, int val)
    {
        if (curr == NULL || curr->val == val)
            return curr;
        return search((curr->val > val) ? curr->left : curr->right, val);
    }
    bool isPresent(int val) { return search(root, val) != NULL; }
    Node *inSucc(Node *curr) { return curr->right ? inSucc(curr->right) : curr; }
    Node *inPre(Node *curr) { return curr->left ? inPre(curr->left) : curr; }
    int height(Node *curr) { return curr ? max(height(curr->left), height(curr->right)) + 1 : 0; }
    int status(Node *curr)
    {
        if (curr == NULL)
            return -1;
        if (curr->left == NULL && curr->right == NULL)
            return 0;
        if (curr->left == NULL || curr->right == NULL)
            return 1;
        return 2;
    }
    void deleteLeaf(Node *curr)
    {
        if (curr == root)
            root = NULL;
        if (curr->parent->left == curr)
            curr->parent->left = NULL;
        else
            curr->parent->right = NULL;
        delete curr;
    }
    void deleteSingleChild(Node *curr)
    {
        if (curr->left)
        {
            if (curr == root)
            {
                root = curr->left;
                return;
            }
            if (curr->parent->left == curr)
                curr->parent->left = curr->left;
            else
                curr->parent->right = curr->left;
            delete curr;
            return;
        }
        if (curr == root)
        {
            root = curr->right;
            return;
        }
        if (curr->parent->right == curr)
            curr->parent->right = curr->right;
        else
            curr->parent->left = curr->right;
        delete curr;
    }
    void deleteNode(Node *curr)
    {
        if (status(curr) == 0)
        {
            deleteLeaf(curr);
            return;
        }
        else if (status(curr) == 1)
        {
            deleteSingleChild(curr);
            return;
        }
        if (height(curr->left) > height(curr->right))
        {
            Node *pre = inPre(curr);
            curr->val = pre->val;
            deleteNode(pre);
            return;
        }
        Node *succ = inSucc(curr);
        curr->val = succ->val;
        deleteNode(succ);
    }
    void deleteNode(int val)
    {
        Node *curr = search(root, val);
        if (curr)
            deleteNode(curr);
    }
    void inorder(Node *curr)
    {
        if (curr == NULL)
            return;
        inorder(curr->left);
        cout << curr->val << " ";
        inorder(curr->right);
    }
    void print() { inorder(root); }
};
int main()
{
    BST b;
    b.insertRecursively(100);
    b.insertRecursively(120);
    b.insertRecursively(110);
    b.insertRecursively(115);
    b.deleteNode(120);
    b.print();
}