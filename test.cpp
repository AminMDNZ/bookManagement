
// #include "DS.h"
// #include "cat.h"
// #include "trie.h"
// #include "manage.h"
#include<bits/stdc++.h>
using namespace std;

// Node class
template <class T>
class Node {
public:
    T data;          // Data stored in the node
    Node* next;      // Pointer to the next node
    Node() : next(nullptr) {}
};

// Stack class 
template <class T>
class Stack {
public:
    Stack();         // Constructor for Stack class
    ~Stack();        // Destructor for Stack class
    void push(T p);  // Push an element to the stack
    bool pop();      // Pop an element from the stack
    bool empty();    // Check if the stack is empty
    T& reTop();      // Get the top element of the stack

private:
    Node<T>* top;     // Pointer to the top of the stack
};

// Implementation of the Stack class
template <class T>
Stack<T>::Stack() : top(nullptr) {}

template <class T>
Stack<T>::~Stack() {
    while (!empty()) {
        pop();
    }
}

template <class T>
void Stack<T>::push(T p) {
    Node<T>* tNew = new Node<T>();  // Create a new node
    tNew->next = top;               // Link the new node to the current top
    tNew->data = p;                 // Set data for the new node
    top = tNew;                     // Update top to the new node
}

template <class T>
bool Stack<T>::empty() {
    return (top == nullptr);
}

template <class T>
bool Stack<T>::pop() {
    if (empty())
        return false;

    Node<T>* oldTop = top;
    top = top->next;                // Move top to the next node
    delete oldTop;                  // Delete the old top node
    return true;
}

template <class T>
T& Stack<T>::reTop() {
    return top->data;               // Return the data of the top node
}

// implementing linked list
template <class T>
class LinkedList {
public:
    LinkedList();                    // Constructor for LinkedList class
    ~LinkedList();                   // Destructor for LinkedList class
    Node<T>* insert(T);              // Insert a new node at the end of the list
    void print();                    // Print the elements of the list
    Node<T>* reHead() { return head; };  // Get the head of the list
    void pop();                      // Remove the head node
    Node<T>* searchByTrackingNumber(int trackingNumber);  // Search for a node by tracking number
    void deleteNode(T data);         // Delete a node with specific data

private:
    Node<T>* head;                   // Pointer to the head of the list
};

// Implementation of the LinkedList class
template <class T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T>* cur = head;
    Node<T>* nextNode;

    while (cur != nullptr) {
        nextNode = cur->next;
        delete cur;
        cur = nextNode;
    }
}

template <class T>
Node<T>* LinkedList<T>::insert(T nl) {
    Node<T>* nNode = new Node<T>();   // Create a new node
    nNode->data = nl;                 // Set data for the new node
    nNode->next = nullptr;

    if (head == nullptr) {
        head = nNode;                  // If the list is empty set the new node as the head
    } else {
        Node<T>* tmp = head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;           // Traverse the list to find the last node
        }
        tmp->next = nNode;             // Link the last node to the new node
    }
    return nNode;
}

template <class T>
void LinkedList<T>::print() {
    Node<T>* tmp = head;
    while (tmp != nullptr) {
        cout << tmp->data << " ";     
        tmp = tmp->next;
    }
    cout << endl;
}

template <class T>
void LinkedList<T>::pop() {
    if (head != nullptr) {
        Node<T>* oldHead = head;
        head = head->next;             // Move head to the next node
        delete oldHead;                // Delete the old head node
    }
}

template <class T>
Node<T>* LinkedList<T>::searchByTrackingNumber(int trackingNumber) {
    Node<T>* current = head;

    while (current != nullptr) {
        if (current->data->getTrackingNumber() == trackingNumber) {
            return current;  // Return the node if found
        }
        current = current->next;
    }

    return nullptr;       // Return nullptr if not found
}

template <class T>
void LinkedList<T>::deleteNode(T data) {
    Node<T>* cur = head;
    Node<T>* prev = nullptr;

    while (cur != nullptr && cur->data != data) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != nullptr) {
        if (prev != nullptr) {
            prev->next = cur->next;
        } else {
            head = cur->next;
        }

        delete cur;
    }
}

// Queue class implementing 
template <class T>
class Queue {
public:
    Queue();                          // Constructor for Queue class
    ~Queue();                         // Destructor for Queue class
    void enqueue(T p);               // Enqueue an element into the queue
    bool dequeue();                   // Dequeue an element from the queue
    bool empty();                     // Check if the queue is empty
    T front();                        // Get the front element of the queue

private:
    Node<T>* head;                    // Pointer to the head of the queue
    Node<T>* tail;                    // Pointer to the tail of the queue
};

// Implementation of the Queue class
template <class T>
Queue<T>::Queue() : head(nullptr), tail(nullptr) {}

template <class T>
Queue<T>::~Queue() {
    while (!empty()) {
        dequeue();
    }
}

template <class T>
bool Queue<T>::empty() {
    return (tail == nullptr && head == nullptr);
}

template <class T>
void Queue<T>::enqueue(T p) {
    Node<T>* tNew = new Node<T>();   // Create a new node
    tNew->data = p;                  // Set data for the new node
    tNew->next = nullptr;

    if (empty()) {
        tail = head = tNew;           
    } else {
        tail->next = tNew;            // Link the current tail to the new node
        tail = tNew;                  // Update tail to the new node
    }
}

template <class T>
bool Queue<T>::dequeue() {
    if (empty())
        return false;

    Node<T>* old = head;
    head = head->next;                // Move head to the next node
    if (head == nullptr)
        tail = nullptr;               // If the queue becomes empty update tail to nullptr
    delete old;                       // Delete the old head node
    return true;
}

template <class T>
T Queue<T>::front() {
    return head->data;                 // Return the data of the head node
}

// implementing heap operation using concept of HVector and dynamic array
template <class T, class Compare = std::less<T>>
class HVector {
    T* arr;                            // Dynamic array
    int cap;                           // Capacity of the array
    int cur;                           // Current number of elements in the array
    Compare comp;                      // Comparison function for heap operations

public:
    HVector();                         // Constructor for HVector class
    HVector(Compare compareFunc);      // Constructor with custom comparison function
    ~HVector();                        // Destructor for HVector class
    T* get(int ind);                  // Get an element at a specific index
    int getCap() { return cap; }      // Get the capacity of the array
    int getSize() { return cur; }     // Get the current size of the array
    void push(T nEl);                 // Add an element to the array
    void push(T nEl, int ind);        // Add an element at a specific index
    T pop();                          // Remove and return the last element
    void heapify(int i);              // Heapify the array at a specific index
    void buildHeap();                 // Build a heap from the array
    T extractRoot();                  // Extract the root element from the heap
    bool empty() const { return cur == 0; }  // Check if the array is empty
};

// Implementation of the HHVector class
template <class T, class Compare>
HVector<T, Compare>::HVector() : arr(new T[1]), cur(0), cap(1), comp(Compare()) {}

template <class T, class Compare>
HVector<T, Compare>::HVector(Compare compareFunc) : arr(new T[1]), cur(0), cap(1), comp(compareFunc) {}

template <class T, class Compare>
HVector<T, Compare>::~HVector() {
    delete[] arr;
}

template <class T, class Compare>
void HVector<T, Compare>::push(T nEl) {
    if (cap == cur) {
        T* temp = new T[2 * cap];     // Create a new array with double the capacity
        for (int i = 0; i < cur; i++) {
            temp[i] = arr[i];         // Copy elements to the new array
        }
        delete[] arr;
        arr = temp;
        cap *= 2;
    }
    arr[cur] = nEl;                    // Add the new element to the array
    cur++;
    buildHeap();                       // Rebuild the heap
}

template <class T, class Compare>
void HVector<T, Compare>::push(T nEl, int ind) {
    if (ind < 0 || ind > cur) {
        throw std::out_of_range("Index out of bounds");
    }

    if (cap == cur) {
        T* temp = new T[2 * cap];     // Create a new array with double the capacity
        for (int i = 0; i < ind; i++) {
            temp[i] = arr[i];         // Copy elements before the insertion point
        }
        temp[ind] = nEl;               // Insert the new element
        for (int i = ind + 1; i <= cur; i++) {
            temp[i] = arr[i - 1];      // Copy elements after the insertion point
        }
        delete[] arr;
        arr = temp;
        cap *= 2;
    } else {
        for (int i = cur; i > ind; i--) {
            arr[i] = arr[i - 1];        // Shift elements to make space for the new element
        }
        arr[ind] = nEl;                 // Insert the new element
    }

    cur++;
    buildHeap();                        // Rebuild the heap
}

template <class T, class Compare>
T* HVector<T, Compare>::get(int ind) {
    if (ind >= 0 && ind < cur) {
        return &arr[ind];                // Return a pointer to the element at the specified index
    }
    return nullptr;
}

template <class T, class Compare>
T HVector<T, Compare>::pop() {
    if (cur <= 0) {
        throw std::out_of_range("Empty");
    }

    T root = arr[cur - 1];               // Get the last element
    cur--;
    buildHeap();                         // Rebuild the heap
    return root;
}

template <class T, class Compare>
void HVector<T, Compare>::heapify(int i) {
    int ind = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < cur && comp(arr[ind], arr[left])) {
        ind = left;
    }

    if (right < cur && comp(arr[ind], arr[right])) {
        ind = right;
    }

    if (ind != i) {
        std::swap(arr[i], arr[ind]);
        heapify(ind);                    // Recursive heapify at the modified index
    }
}

template <class T, class Compare>
void HVector<T, Compare>::buildHeap() {
    for (int i = (cur - 1) / 2; i >= 0; i--) {
        heapify(i);                      // Heapify each non-leaf node from bottom to top
    }
}

template <class T, class Compare>
T HVector<T, Compare>::extractRoot() {
    if (cur <= 0) {
        throw std::out_of_range("Heap is empty");
    }

    T root = arr[0];                    // Get the root element
    arr[0] = arr[cur - 1];              // Replace root with the last element
    cur--;
    heapify(0);                         // Heapify from the root
    buildHeap();                        // Rebuild the heap
    return root;
}

template <class T>
class Vector {
    T* arr;                            // Dynamic array
    int cap;                           // Capacity of the array
    int cur;                           // Current number of elements in the array

public:
    Vector();                          // Constructor for Vector class
    ~Vector();                         // Destructor for Vector class
    T get(int ind);                   // Get a reference to an element at a specific index
    int getCap() const { return cap; } // Get the capacity of the array
    int getSize() const { return cur; } // Get the current size of the array
    void push(const T& nEl);           // Add an element to the array
    void push(const T& nEl, int ind);  // Add an element at a specific index
    T pop();                           // Remove and return the last element
};

// Implementation of the Vector class
template <class T>
Vector<T>::Vector() : arr(new T[1]), cur(0), cap(1) {}

template <class T>
Vector<T>::~Vector() {
    delete[] arr;
}

template <class T>
T Vector<T>::get(int ind) {
    if (ind >= 0 && ind < cur) {
        return arr[ind];                // Return a reference to the element at the specified index
    }
    // Note: This is not safe, and in a production environment, you might want to handle this differently.
    // Returning a reference to a dummy value may lead to undefined behavior.
    return arr[0];
}

template <class T>
void Vector<T>::push(const T& nEl) {
    if (cap == cur) {
        T* temp = new T[2 * cap];     // Create a new array with double the capacity
        for (int i = 0; i < cur; i++) {
            temp[i] = arr[i];         // Copy elements to the new array
        }
        delete[] arr;
        arr = temp;
        cap *= 2;
    }
    arr[cur] = nEl;                    // Add the new element to the array
    cur++;
}

template <class T>
void Vector<T>::push(const T& nEl, int ind) {
    if (ind < 0 || ind > cur) {
        throw std::out_of_range("Index out of bounds");
    }

    if (cap == cur) {
        T* temp = new T[2 * cap];     // Create a new array with double the capacity
        for (int i = 0; i < ind; i++) {
            temp[i] = arr[i];         // Copy elements before the insertion point
        }
        temp[ind] = nEl;               // Insert the new element
        for (int i = ind + 1; i <= cur; i++) {
            temp[i] = arr[i - 1];      // Copy elements after the insertion point
        }
        delete[] arr;
        arr = temp;
        cap *= 2;
    } else {
        for (int i = cur; i > ind; i--) {
            arr[i] = arr[i - 1];        // Shift elements to make space for the new element
        }
        arr[ind] = nEl;                 // Insert the new element
    }

    cur++;
}

template <class T>
T Vector<T>::pop() {
    if (cur <= 0) {
        throw std::out_of_range("Empty");
    }

    T popped = arr[cur - 1];            // Get the last element
    cur--;
    return popped;
}

class Book {
    string writer, name, price, catName;

public:
    Book() : writer(""), name(""), price(""), catName("") {}

    Book(string name, string writer, string price, string catName)
        : name(name), writer(writer), price(price), catName(catName) {}

    void print() const {
        cout << std::setw(20) << std::left << "Writer:" << writer << std::endl;
        cout << std::setw(20) << std::left << "Name:" << name << std::endl;
        cout << std::setw(20) << std::left << "Price:" << price << std::endl;
        cout << std::setw(20) << std::left << "category:" << catName << std::endl;
    }
    
    void setWriter(const std::string& writer) { this->writer = writer; }
    void setName(const std::string& name) { this->name = name; }
    void setPrice(const std::string& price) { this->price = price; }
    void setCatNAme(const std::string& catName) { this->catName = catName; }

    string getWriter() { return writer; }
    string getName()  { return name; }
    string getPrice()  { return price; }
    string getCatNAme()  { return catName; }

};

class cat{
public:
    string name;
    Vector<Book*> books;
    Vector<cat*> cats;
    cat(string name) : name(name), books(), cats() {}

    void insertBook(Book* book){ // it should be checked if the book exists
        books.push(book);    
    }

    void insertCat(cat* Cat){
        cats.push(Cat);
    }    


};


bool checkNumerical(string num){
    for(int i=0;i<num.size();i++){
        if(num[i] < '0' || num[i] > '9')  return false;
    }
    return true;
}

class TrieNode {
public:
    char data;
    Vector<TrieNode*> children;
    Book* book;  // Single book associated with the node

    TrieNode(char ch) : data(ch), book(nullptr) {}

    ~TrieNode() {
        // delete children;
        delete book;
    }
};

class Trie {
private:
    

public:
TrieNode* root;
    Trie() {
        root = new TrieNode(NULL); 
    }

    ~Trie() {
        delete root;
    }

    void insert(Book& book) {
        TrieNode* current = root;
        string str = book.getName();
        for (char ch : str) {
            bool check = false;
            TrieNode* child = nullptr;
            int k = current->children.getSize();
            for(int i=0;i<k;i++){
                if(ch == current->children.get(i)->data){
                    current = current->children.get(i);
                    check = true;
                    break;
                }
            }
            if(!check){
                TrieNode* Node = new TrieNode(ch);
                current->children.push(Node);     
                current = Node;           
            }
        }
        current->book = &book;
    }

    TrieNode* search(const string& key) {
        TrieNode* current = root;
        for (char ch : key) {
            TrieNode* child = nullptr;
            int k = current->children.getSize();
            for (int i=0;i<k;i++) {
                TrieNode* node = current->children.get(i);
                if (node->data == ch) {
                    child = node;
                    break;
                }
            }
            if (!child) {
                return nullptr;  
            }
            current = child;
        }
        return current;
    }

    void printBook(TrieNode* Node){
        TrieNode* cur = Node;
        Stack<TrieNode*> dfsSt;
        dfsSt.push(Node);
        while(!dfsSt.empty()){
            cur = dfsSt.reTop();
            dfsSt.pop();
            if(cur->book != nullptr) cur->book->print();
            for(int i=0;i<cur->children.getSize();i++){
                dfsSt.push(cur->children.get(i));
            }
        }
    }

    Book* select(const string& key) {
        if(search(key) == nullptr) return nullptr;
        return search(key)->book;
    }

    bool remove(const string& key){
        // if(search(key)->book == nullptr) return false;
        
        // return true;
        TrieNode* current = root;

    // Step 1: Traverse the Trie to find the last node of the key
    for (char ch : key) {
        TrieNode* child = nullptr;
        int k = current->children.getSize();
        for (int i = 0; i < k; i++) {
            TrieNode* node = current->children.get(i);
            if (node->data == ch) {
                child = node;
                break;
            }
        }
        if (!child) {
            // The key is not in the Trie
            return false;
        }
        current = child;
    }

    // Step 2: Set the book pointer to nullptr
    if (current->book == nullptr) {
        // No associated book, nothing to remove
        return false;
    }

    current->book = nullptr;

    // Step 3: Traverse back and remove nodes with no children and no associated book
    current = root;
    Stack<TrieNode*> path;  // Keep track of the path to the last node
    path.push(root);

    for (char ch : key) {
        TrieNode* child = nullptr;
        int k = current->children.getSize();
        for (int i = 0; i < k; i++) {
            TrieNode* node = current->children.get(i);
            if (node->data == ch) {
                child = node;
                break;
            }
        }
        path.push(child);
        current = child;
    }

    // Traverse back and remove nodes with no children and no associated book
    while (!path.empty()) {
        TrieNode* node = path.reTop();
        path.pop();

        if (node->children.getSize() == 0 && node->book == nullptr) {
            // Node has no children and no associated book, remove it
            delete node;
        } else {
            // Stop removal if a node has children or an associated book
            break;
        }
    }

    return true;
    }

    void sort(TrieNode* node){

    }
    
};

class manage{

public:
    Trie allBooks;
    cat CatsRoot;
    manage() : allBooks(), CatsRoot("all cats") {}

    void mainf(){
        string in = "";
        while(in != "exit"){
            cout<<"1.add a category "<<endl;
            cout<<"2.add a book "<<endl;
            cout<<"3.remove a cetegory "<<endl;
            cout<<"4.remove a book "<<endl;
            cout<<"5.search "<<endl;
            cout<<"6.print all books of a cetegory"<<endl;

            cin>>in;

            if(in == "1"){
                cout<<"add to a specific category\n1.yes\nelse.no\nreturn"<<endl;
                string in;
                cin>>in;
                string selCat, catName;
                cat* addingcat = &CatsRoot;
                if(in == "return") continue;
                if(in == "1"){
                    cout<<"selected category : "<<endl;  
                    cin.ignore();                  
                    getline(cin, selCat);
                    cout<<selCat<<endl;
                    addingcat = findCat(selCat, &CatsRoot);
                    if(addingcat == nullptr){
                        cout<<"can't find the category"<<endl;
                        continue;
                    }
                }
                
                cout<<"new category : "<<endl;
                cin.ignore();
                getline(cin, catName); 
                cout<<catName<<endl; 
                if(findCat(catName, addingcat) != nullptr) {
                    cout<<"category exists"<<endl;
                    continue;
                }       
                addCat(catName, addingcat);
                cout<<"added"<<endl;
            }
            else if(in == "2"){
                string bookName, writer, catName, price;

                cout<<"category, name, writer, price\n1.return";

                getline(cin, catName);
                if(catName == "1") return;
                cin.ignore();
                getline(cin, writer);
                cin.ignore();
                getline(cin, bookName);
                cin.ignore();
                getline(cin, price);

                addBooks(bookName, writer, catName, price, &CatsRoot);
            }
            else if(in == "3"){

            }
        }
    }







    bool checkBook(string key){
        return (allBooks.search(key) == nullptr || allBooks.search(key)->book == nullptr);
    }
    
    bool checkCat(string key){
        return allBooks.search(key)->book == nullptr;
    }
    
    cat* findCat(string key, cat* bfsRoot){
        Queue<cat*> bfsQ;
        cat* cur = bfsRoot;
        bfsQ.enqueue(cur);
        while(!bfsQ.empty()){
            cur = bfsQ.front();
            bfsQ.dequeue();
            for(int i =0;i<cur->cats.getSize();i++){
                if(cur->cats.get(i)->name == key) return cur->cats.get(i);
                bfsQ.enqueue(cur->cats.get(i));
            }
        }
        return nullptr;
    }

    void addCat(string catName, cat* addRoot)   {
        cat* addedCat = new cat(catName);
        addRoot->cats.push(addedCat);
    }

    void addBooks(string bookName, string writer, string catName, string price, cat* start) {
        cat* selecetedCat = findCat(catName, &CatsRoot);
        // cout << selecetedCat->name << " sada s " << bookName << endl;
        Book book(bookName, writer, price, catName);

        if (!checkBook(bookName) || selecetedCat == nullptr || !checkNumerical(price)) {
            cout << "can't add the book" << endl;
            return;
        }
        cout<<selecetedCat->name<<" "<<book.getName()<<endl;
        selecetedCat->books.push(&book);
        allBooks.insert(book);
    }

    void removeBook(){
        string bookName;
        cout<<"eneter the books name : \n1.return"<<endl;
        getline(cin, bookName);
        if(bookName == "1") return;
        if(checkBook(bookName)){
            cout<<"can't find the book"<<endl;
            return;
        }
        cat* bfsRoot = &CatsRoot;
        Queue<cat*> bfsQ;
        cat* cur = bfsRoot;
        bfsQ.enqueue(cur);
        bool check = false;
        while(!bfsQ.empty()){
            cur = bfsQ.front();
            for(int i =0;i<cur->cats.getSize();i++){
                for(int j=0;j<cur->cats.get(i)->books.getSize();j++){
                    if(cur->cats.get(i)->books.get(j)->getName() == bookName){
                        check = true;
                        break;
                    }
                }
                bfsQ.enqueue(cur->cats.get(i));
            }
            if(check) break;
        }

        if(!check){
            cout<<"can't find thre book"<<endl;
            return;

        }

        Vector<Book*> curBook;
        
        for(int i =0;i<cur->books.getSize();i++){
            if(cur->books.get(i)->getName() == bookName) continue;
            curBook.push(cur->books.get(i));
        }
        
        cur->books = curBook;
        allBooks.remove(bookName);
        cout<<"removed."<<endl;
    }

    void removeCat(){
        string catName;
        cout<<"category name : \n1.return"<<endl;
        // cin.ignore();
        getline(cin, catName);
        if(catName == "1") return;
        Queue<cat*> bfsQ;
        cat* bfsRoot = &CatsRoot;
        cat* cur = bfsRoot;
        bfsQ.enqueue(cur);
        cat* found;
        bool check = false;
        while(!bfsQ.empty()){
            cur = bfsQ.front();
            for(int i =0;i<cur->cats.getSize();i++){
                cout<<cur->cats.get(i)->name<<endl;
                if(cur->cats.get(i)->name == catName){
                    check = true;
                    found = cur->cats.get(i);
                    break;
                } 
                bfsQ.enqueue(cur->cats.get(i));
            }
            if(check) break;
        }
        
        if(!check){
            cout<<"can't find the category"<<endl;
            return;
        }

        Vector<cat*> curCat;
        

        for(int i =0;i<cur->cats.getSize();i++){
            if(cur->cats.get(i)->name == catName) continue;
            curCat.push(cur->cats.get(i));
        }


    Vector<Book*> booksToRemove;
    cout<<found->name;
    // for (int i = 0; i < found->books.getSize(); i++) {
        // cout << found->books.get(i)->getName() << endl;
    //     booksToRemove.push(found->books.get(i));
    // }

    // // Remove the books from the 'allBooks' Trie
    // for (int i = 0; i < booksToRemove.getSize(); i++) {
    //     allBooks.remove(booksToRemove.get(i)->getName());
    // }

        cur->cats = curCat;
        cout<<"removed."<<endl;
    }

    void printBooks(){
        string catName, in;
        cout<<"1.print all books\n2.print books of an specific category\nelse.return"<<endl;
        cin>>in;
        cat* printRoot = &CatsRoot;
        if(in == "2"){
            cout<<"write the categories name :"<<endl;
            getline(cin, catName); 
            printRoot = findCat(catName, &CatsRoot);
        }
        
        if(printRoot == nullptr){
            cout<<"can't find the category"<<endl;
            return;
        }

        Stack<cat*> dfsSt;
        cat* dfsRoot = printRoot;
        cat* cur = dfsRoot;
        dfsSt.push(cur);
        bool check = false;
        while(!dfsSt.empty()){
            cur = dfsSt.reTop();
            dfsSt.pop();

            cout<<endl<<"category : "<<cur->name<<endl;
    
            for(int i=0;i<cur->books.getSize();i++){
                cout<<cur->books.get(i)->getName()<<endl;
            }

            for(int i =0;i<cur->cats.getSize();i++){
                dfsSt.push(cur->cats.get(i));
            }
        }
    }

    void printByTrie(){
        // cout<<"enter book's name : \n1.return"<<endl;
        // cin.ignore();
        string bookName = "cal";
        // getline(cin, bookName);
        if(bookName == "1") return;
        TrieNode* printNode = allBooks.search(bookName);
        allBooks.printBook(printNode);
    }
};

int main(){
    // Trie g; 
    // Book myBook1("amin", "w1", "p1", "c1");
    // Book myBook2("aminian", "w2", "p2", "c2"); 
    // Book myBook3("amesterdamn", "w3", "p3", "c3");
    // Book myBook4("amid", "w4", "p4", "c4");
    // Book myBook5("amidbo", "w4", "p4", "c4");
    // Book myBook6("amiddodol", "w4", "p4", "c4");
    // Book myBook7("amidhasan", "w4", "p4", "c4");
    
    // g.insert(myBook1);
    // g.insert(myBook2);
    // g.insert(myBook3);
    // g.insert(myBook4);
    // g.insert(myBook5);
    // g.insert(myBook6);
    // g.insert(myBook7);
    // g.remove("amidd");
    // g.search("amid")->book->print();
    // g.printBook(g.search("amid"));

    // myBook.setWriter("John Doe");
    // myBook.setName("Introduction to Programming");
    // myBook.setPrice("25");
    // g.insert(myBook);
    // // cout<<g.
    // myBook.print();
    // g.printBook(g.root);
    manage g;
    g.addCat("p1", &g.CatsRoot);
    g.addCat("p4", g.CatsRoot.cats.get(0));
    g.addBooks("amin", "w1", "p1", "1", &g.CatsRoot);
    g.addBooks("amid", "w4", "p4", "4", &g.CatsRoot);
    g.addBooks("amidhasan", "w4", "p4", "4", &g.CatsRoot);
    // for(int i=0;i<g.CatsRoot.cats.get(0)->books.getSize();i++){
    //     cout<<g.CatsRoot.cats.get(0)->books.get(i)->getName()<<endl;
    // }
    cat* c1 = g.CatsRoot.cats.get(0);
    cout<<c1->name<<endl;
    cout<<c1->books.get(0)->getName()<<endl;

    // g.printBooks();
    // g.removeCat();
    // cout<<g.CatsRoot.cats.get(0)->books.get(0)->getName()<<endl;

    // g.mainf();
    // string str;
    // getline(str);
    // g.addCat("math", &g.CatsRoot);
    // Book b("cal", "cal", "math", "10");
    // g.addCat("math", &g.CatsRoot);
    // g.addCat("dis", g.CatsRoot.cats.get(0));
    // g.addCat("fd", g.findCat("math", &g.CatsRoot));
    // cout<<g.CatsRoot.cats.get(0)->cats.get(0)->name;
    // g.addBooks("fs", "shah", "fd", "10");
    // cout<<g.CatsRoot.cats.(0)->cats.get(1)->name;
    // cout<<g.CatsRoot.cats.get(0)->books.get(0)->getName();
    // g.addBooks("cal", "cal", "math", "10");
    // g.printByTrie();
    // cout<<g.allBooks.search("h")->book->getName();
    // cout<<(g.allBooks.search("cal")->book->getName());
    // cout<<g.findCat("math", &g.CatsRoot);
    // cout<<g.CatsRoot.cats.get(0)->name<<endl;
    // for(int i=0;i<g.CatsRoot.cats.getSize();i++) cout<<g.CatsRoot.cats.get(i)->name<<endl;
    // Trie boo;
    // boo.insert(b);
    // cout<<(boo.search("cal")==nullptr);
}