#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int val;
    Node *parent, *left, *right;
    Node(int data, Node *parent) : val(data), parent(parent), left(NULL), right(NULL){};
};
class BST
{
public:
    Node *root;

    BST() : root(NULL){};
    ~BST() { delete root; }
    // recursively
    void Preorder(Node *r)
    {
        if (r)
        {
            cout << r->val << " ";
            Preorder(r->left);
            Preorder(r->right);
        }
    }
    void Inorder(Node *r)
    {
        if (r)
        {
            Inorder(r->left);
            cout << r->val << " ";
            Inorder(r->right);
        }
    }
    void Postorder(Node *r)
    {
        if (r)
        {
            Postorder(r->left);
            Postorder(r->right);
            cout << r->val << " ";
        }
    }
    void levelOrder(Node *r)
    {
        if (r)
        {
            queue<Node *> q;
            q.push(r);
            while (!q.empty())
            {
                Node *curr = q.front();
                q.pop();
                cout << curr->val << " ";
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
    }
    Node *iterativeSearch(Node *r, int key)
    {
        while (r != NULL)
        {
            if (r->val == key)
                return r;
            if (r->val > key)
                r = r->left;
            else
                r = r->right;
        }
        return NULL;
    }
    Node *recursiveSearch(Node *r, int key)
    {
        if (r == NULL || r->val == key)
            return r;
        return recursiveSearch(r->val > key ? r->left : r->right, key);
    }
    void iterativeInsert(Node *r, int key)
    {
        if (r == NULL)
        {
            r = new Node(key, NULL);
            return;
        }
        Node *parent = NULL;
        while (r != NULL)
        {
            parent = r;
            if (r->val > key)
                r = r->left;
            else
                r = r->right;
        }
        if (parent->val > key)
            parent->left = new Node(key, parent);
        else
            parent->right = new Node(key, parent);
    }

    Node *recursiveInsert(Node *r, int key, Node *parent)
    {
        if (r == NULL)
            return r = new Node(key, parent);
        if (r->val > key)
            r->left = recursiveInsert(r->left, key, r);
        else if (r->val < key)
            r->right = recursiveInsert(r->right, key, r);
        return r;
    }
    Node *inorderPre(Node *r)
    {
        if (r == NULL || r->right == NULL)
            return r;
        return inorderPre(r->right);
    }
    Node *inorderSucc(Node *r)
    {
        if (r == NULL || r->left == NULL)
            return r;
        return inorderSucc(r->left);
    }
    int Height(Node *r)
    {
        if (r == NULL)
            return 0;
        return max(Height(r->left), Height(r->right)) + 1;
    }
    void recursiveInsert(int key)
    {
        root = recursiveInsert(root, key, NULL);
    }
    void deleteLeaf(Node *current)
    {
        if (current == root)
            root = NULL;
        else if (current->parent->left == current)
            current->parent->left = NULL;
        else
            current->parent->right = NULL;
        delete current;
    }
    void deleteOneChild(Node *current)
    {
        bool leftNode = current->left == NULL;
        if (leftNode)
        {
            if (current == root)
                root = current->right;
            else if (current->parent->left == current)
                current->parent->left = current->right;
            else
                current->parent->right = current->right;
            delete current;
            return;
        }
        if (current == root)
            root = current->left;
        else if (current->parent->right == current)
            current->parent->right = current->left;
        else
            current->parent->left = current->left;
        delete current;
    }
    void deleteNodeIterative(int key)
    {
        Node *current = recursiveSearch(root, key);
        if (root == NULL || current == NULL)
            return;

        // delete leaf node
        bool leafNode = current->left == NULL && current->right == NULL;
        bool oneNode = current->left == NULL || current->right == NULL;
        if (leafNode)
        {
            deleteLeaf(current);
            return;
        }

        // delete one child node
        if (oneNode)
        {
            deleteOneChild(current);
            return;
        }

        // delete two child node
        if (Height(current->left) > Height(current->right))
        {
            Node *pre = inorderPre(current->left);
            current->val = pre->val;
            if (pre->left == NULL && pre->right == NULL)
            {
                deleteLeaf(pre);
                return;
            }
            deleteOneChild(pre);
            return;
        }
        Node *succ = inorderSucc(current->right);
        current->val = succ->val;
        if (succ->left == NULL && succ->right == NULL)
        {
            deleteLeaf(succ);
            return;
        }
        deleteOneChild(succ);
        return;
    }
    Node *deleteReccursively(Node *current, int key)
    {
        if (current == NULL)
            return NULL;

        if (current->left == NULL && current->right == NULL)
        {
            if (current == root)
                root = NULL;
            delete current;
            return NULL;
        }
        if (current->val > key)
            current->left = deleteReccursively(current->left, key);
        if (current->val < key)
            current->right = deleteReccursively(current->right, key);
        else
        {
            if (Height(current->left) > Height(current->right))
            {
                Node *pre = inorderPre(current->left);
                current->val = pre->val;
                current->left = deleteReccursively(current->left, current->val);
            }
            else
            {
                Node *succ = inorderSucc(current->right);
                current->val = succ->val;
                current->right = deleteReccursively(current->right, current->val);
            }
        }
        return current;
    }
    void deleteReccursively(int key)
    {
        root = deleteReccursively(root, key);
    }
};
int main()
{
    BST b;
    b.recursiveInsert(100);
    b.recursiveInsert(120);
    b.recursiveInsert(110);
    b.recursiveInsert(115);
    b.deleteReccursively(100);
    b.Inorder(b.root);
}
