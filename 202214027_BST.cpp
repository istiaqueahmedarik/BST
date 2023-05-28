#include <bits/stdc++.h>

using namespace std;
int menu();
class Book;
Book *createBook();
class Book
{
    long long ISBN;
    string title;
    string author;
    double price;
    int quantity;

public:
    Book(long long ISBN, string title, string author, double price, int quantity)
    {
        this->ISBN = ISBN;
        this->title = title;
        this->author = author;
        this->price = price;
        this->quantity = quantity;
    }
    long long getIsbn() { return ISBN; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void display()
    {
        cout << "ISBN: " << ISBN << "\nTitle: " << title << "\nAuthor: " << author << "\nPrice: $" << setprecision(2) << fixed << price << "\nQuantity: " << quantity << "\n";
    }
    ~Book() {}
};

class Node
{
public:
    Book *book;
    Node *parent, *left, *right;
    Node()
    {
        this->book = NULL;
        this->parent = this->left = this->right = NULL;
    }
    Node(Book *book, Node *parent)
    {
        this->book = book;
        this->parent = parent;
        this->left = this->right = NULL;
    }
};
class BST
{
    Node *root;
    Node *insert(Node *current, Book *newBook, Node *parent)
    {
        if (current == NULL)
            return current = new Node(newBook, parent);
        (current->book->getIsbn() > newBook->getIsbn()) ? current->left = insert(current->left, newBook, current) : current->right = insert(current->right, newBook, current);
        return current;
    }
    Node *search(Node *current_book, Book &book)
    {
        if (current_book == NULL)
            return current_book;
        if (book.getIsbn() == current_book->book->getIsbn())
            return current_book;
        (current_book->book->getIsbn() > book.getIsbn()) ? current_book = search(current_book->left, book) : current_book = search(current_book->right, book);
    }
    Book *inorderPre(Node *current)
    {
        if (current->right == NULL)
            return current->book;
        return inorderPre(current->right);
    }
    Book *inorderSucc(Node *current)
    {
        if (current->left == NULL)
            return current->book;
        return inorderSucc(current->left);
    }
    int Height(Node *node) { return (node == NULL) ? 0 : max(Height(node->left), Height(node->right)) + 1; }
    Node *dlt(Node *current, Book *book)
    {
        if (current == NULL)
            return current;
        if (current->left == NULL && current->right == NULL)
        {
            if (current == root)
                root = NULL;
            delete current;
            return NULL;
        }
        if (current->book->getIsbn() > book->getIsbn())
            current->left = dlt(current->left, book);
        else if (current->book->getIsbn() < book->getIsbn())
            current->right = dlt(current->right, book);
        else
        {
            if (Height(current->left) > Height(current->right))
                current->left = dlt(current->left, current->book = inorderPre(current->left));
            else
                current->right = dlt(current->right, current->book = inorderSucc(current->right));
        }
        return current;
    }

    void BFS(Node *r)
    {
        if (r == NULL)
            return;
        queue<Node *> q;
        q.push(r);
        while (!q.empty())
        {
            Node *current = q.front();
            current->book->display();
            cout << endl;
            q.pop();
            if (current->left != NULL)
                q.push(current->left);
            if (current->right != NULL)
                q.push(current->right);
        }
    }
    Node *searchWithIsbn(Node *current, long long isbn)
    {
        if (current == NULL || current->book->getIsbn() == isbn)
            return current;
        if (current->book->getIsbn() > isbn)
            return searchWithIsbn(current->left, isbn);
        return searchWithIsbn(current->right, isbn);
    }

public:
    BST() { root = NULL; }
    ~BST() { delete root; }
    void addBook(Book *newBook) { root = insert(root, newBook, NULL); }
    void removeBook(long long isbn) { root = dlt(root, searchWithIsbn(root, isbn)->book); }
    void updateQuantity(long long isbn, int quantity)
    {
        Node *b = searchWithIsbn(root, isbn);
        if (b == NULL)
            return;
        b->book->setQuantity(quantity);
    }
    void Print() { BFS(root); }
    Book *searchBook(long long isbn)
    {
        Node *b = searchWithIsbn(root, isbn);
        if (b == NULL)
        {
            cout << "not found";
            return NULL;
        }
        return b->book;
    }
};

int main()
{
    BST b;
    while (1)
    {
        int choice = menu();
        Book *newBook;
        if (choice == 1)
        {
            newBook = createBook();
            b.addBook(newBook);
            cout << "\n\nBook added to the inventory successfully.\n";
        }
        else if (choice == 2)
        {
            long long isbn;
            cout << "\nEnter the ISBN of the book to remove: ";
            cin >> isbn;
            b.removeBook(isbn);
            cout << "\nBook removed from the inventory successfully.\n";
        }
        else if (choice == 3)
        {
            long long isbn;
            cout << "\nEnter the ISBN of the book to remove: ";
            cin >> isbn;
            int newQuantity;
            cout << "Enter the new quantity: ";
            cin >> newQuantity;
            b.updateQuantity(isbn, newQuantity);
            cout << "\nBook quantity updated successfully.\n";
        }
        else if (choice == 4)
        {
            long long isbn;
            cout << "Enter the ISBN of the book to search: ";
            cin >> isbn;
            Book *bk = b.searchBook(isbn);
            bk->display();
        }
        else if (choice == 5)
        {
            cout << "Inventory:\n\n";
            b.Print();
        }
        else if (choice == 7)
        {
            delete newBook;
            break;
        }
    }
}

int menu()
{
    cout << "Welcome to the Bookstore Inventory Management System!\n\n";
    cout << "1. Add a book to the inventory\n2. Remove a book from the inventory\n3. Update the quantity of a book\n4. Search for a book by ISBN\n5. Display all books in the inventory\n7. Exit\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

Book *createBook()
{
    long long isbn;
    string title, author;
    double price;
    int quantity;
    cout << "Enter the book's ISBN: ";
    cin >> isbn;
    cin.ignore();
    cout << "Enter the book's title: ";
    getline(cin, title);
    cout << "Enter the book's author: ";
    getline(cin, author);
    cout << "Enter the book's price: ";
    cin >> price;
    cout << "Enter the book's quantity: ";
    cin >> quantity;
    return new Book(isbn, title, author, price, quantity);
}