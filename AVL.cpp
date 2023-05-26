#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int value;
    Node *left, *right, *parent;
    int height;
    Node(int value)
    {
        this->value = value;
        left = right = parent = NULL;
        height = 1;
    }
};

class BST
{
    Node *root;
    int Height(Node *r)
    {
        return (r == NULL) ? 0 : max(Height(r->left), Height(r->right)) + 1;
    }
    int balanceFactor(Node *r) { return (r) ? Height(r->left) - Height(r->right) : 0; }
    Node *LLRotation(Node *r)
    {
        Node *rl = r->left;
        Node *rlr = rl->right;

        rl->right = r;
        r->left = rlr;
        r->height = Height(r);
        rl->height = Height(rl);
        if (root == r)
            root = rl;
        return rl;
    }
    Node *LRRotation(Node *r)
    {
        Node *rl = r->left;
        Node *rlr = rl->right;
        rl->right = rlr->left;
        r->left = rlr->right;
        rlr->left = rl;
        rlr->right = r;
        r->height = Height(r);
        rl->height = Height(rl);
        rlr->height = Height(rlr);
        if (root == r)
            root = rlr;
        return rlr;
    }
    Node *RRRotation(Node *r)
    {
        Node *rr = r->right;
        Node *rrl = rr->left;
        rr->left = r;
        r->right = rrl;
        r->height = Height(r);
        rr->height = Height(rr);
        if (root == r)
            root = rr;
        return rr;
    }
    Node *RLRotation(Node *r)
    {
        Node *rr = r->right;
        Node *rrl = rr->left;
        rr->left = rrl->right;
        r->right = rrl->left;
        rrl->left = rr;
        rrl->right = r;
        r->height = Height(r);
        rr->height = Height(rr);
        rrl->height = Height(rrl);
        if (root == r)
            root = rrl;
        return rrl;
    }
    Node *recursiveInsert(Node *r, int value)
    {
        if (r == NULL)
            return r = new Node(value);
        (r->value > value) ? r->left = recursiveInsert(r->left, value) : r->right = recursiveInsert(r->right, value);
        r->height = Height(r);
        if (balanceFactor(r) > 1 && balanceFactor(r->left) == 1)
            return LLRotation(r);
        if (balanceFactor(r) > 1 && balanceFactor(r->left) == -1)
            return LRRotation(r);
        if (balanceFactor(r) < -1 && balanceFactor(r->right) == -1)
            return RRRotation(r);
        if (balanceFactor(r) < -1 && balanceFactor(r->right) == 1)
            return RLRotation(r);
        return r;
    }

public:
    BST() { root = NULL; }
    ~BST() { delete root; }
    void insert(int value)
    {
        if (root == NULL)
        {
            root = new Node(value);
            return;
        }
        Node *curr = root;
        Node *prev = NULL;
        while (curr != NULL)
        {
            prev = curr;
            (curr->value > value) ? curr = curr->left : curr = curr->right;
        }
        if (prev->value > value)
        {
            prev->left = new Node(value);
            prev->left->parent = prev;
            return;
        }
        prev->right = new Node(value);
        prev->right->parent = prev;
    }
    Node *Search(int value)
    {
        Node *temp = root;
        while (temp != NULL, (value > temp->value) ? temp = temp->right : temp = temp->left)
            if (value == temp->value)
                return temp;
        return NULL;
    }
    Node *rSearch(Node *r, int value)
    {
        if (r == NULL)
            return NULL;
        if (r->value == value)
            return r;
        (r->value > value) ? r = rSearch(r->left, value) : r = rSearch(r->right, value);
    }
    Node *Search_r(int value) { return rSearch(root, value); }
    bool isPresent(int value) { return rSearch(root, value) != NULL; }
    int inorderSucc(Node *r)
    {
        while (r->right != NULL)
        {
            r = r->right;
        }
        return r->value;
    }
    int inorderPred(Node *r)
    {
        while (r->left != NULL)
        {
            r = r->left;
        }
        return r->value;
    }
    Node *recursiveDelete(Node *r, int value)
    {
        if (r == NULL)
            return NULL;
        if (r->left == NULL && r->right == NULL)
        {
            if (r == root)
            {
                root = NULL;
                delete r;
                return NULL;
            }
            if (r->value > value)
            {
                r->left = recursiveDelete(r->left, value);
            }
            else if (r->value < value)
            {
                r->right = recursiveDelete(r->right, value);
            }
            else
            {
                if (Height(r->left) > Height(r->right))
                {
                    r->left = recursiveDelete(r->left, r->value = inorderPred(r->left));
                }
                else
                {
                    r->right = recursiveDelete(r->right, r->value = inorderSucc(r->right));
                }
            }
        }
    }
    void Print()
    {
        Inorder(root);
    }
    void Inorder(Node *r)
    {
        if (r)
        {
            Inorder(r->left);
            cout << r->value << " ";
            Inorder(r->right);
        }
    }
    void deleteNode(int value)
    {
        root = recursiveDelete(root, value);
    }
    void insertR(int value)
    {
        root = recursiveInsert(root, value);
    }
};
int main()
{
    BST st;
    st.insertR(2);
    st.insertR(2);
    st.insertR(20);
    st.insertR(9);
    st.insertR(5);
    st.Print();
}
