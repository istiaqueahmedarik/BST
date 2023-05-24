#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *parent, *left, *right;
    Node(int data)
    {
        this->data = data;
        left = right = parent = NULL;
    }
};
class BST
{
    Node *root;
    Node *insertR(Node *r, int data)
    {
        if (r == NULL)
            return r = new Node(data);
        (r->data > data) ? r->left = insertR(r->left, data) : r->right = insertR(r->right, data);
        return r;
    }
    void Inorder(Node *r)
    {
        if (r)
        {
            Inorder(r->left);
            cout << r->data << " ";
            Inorder(r->right);
        }
    }

public:
    BST()
    {
        root = NULL;
    }
    void insert(int data)
    {
        if (root == NULL)
        {
            root = new Node(data);
            return;
        }
        Node *parent = NULL, *curr = root;
        while (curr != NULL)
        {
            parent = curr;
            (data < curr->data) ? curr = curr->left : curr = curr->right;
        }
        (data < parent->data) ? parent->left = new Node(data) : parent->right = new Node(data);
    }
    void recursiveInsert(int data)
    {
        root = insertR(root, data);
    }
    void Print()
    {
        Inorder(root);
    }
    Node *Search(int data)
    {
        Node *temp = root;
        while (temp != NULL, (data > temp->data) ? temp = temp->right : temp = temp->left)
            if (data == temp->data)
                return temp;
        return NULL;
    }
    bool isPresent(int data)
    {
        return Search(data) != NULL;
    }
    int Height(Node *r)
    {
        return (r == NULL) ? 0 : max(Height(r->left), Height(r->right)) + 1;
    }
    Node *dlt(Node *r, int data)
    {
        if (r == NULL)
            return NULL;
        if (r->left == NULL && r->right == NULL)
            return (r == root) ? (root = NULL, delete r, (Node *)NULL) : (delete r, (Node *)NULL);
        if (data < r->data)
            r->left = dlt(r->left, data);
        else if (data > r->data)
            r->right = dlt(r->right, data);
        else
            (Height(r->left) > Height(r->right)) ? r->left = dlt(
                                                       r->left, r->data = [](Node *n)
                                                                { while(n->right) n= n->right; return n->data; }(r->left))
                                                 : r->right = dlt(
                                                       r->right, r->data = [](Node *n)
                                                                 { while(n->left) n = n->left; return n->data; }(r->right));
        return r;
    }
    void Delete(int data)
    {
        dlt(root, data);
    }
    ~BST()
    {
        delete root;
    }
};
int main()
{
    BST st;
    st.recursiveInsert(2);
    st.recursiveInsert(2);
    st.recursiveInsert(20);
    st.recursiveInsert(9);
    st.insert(5);
    st.Delete(2);
    st.Print();
}
