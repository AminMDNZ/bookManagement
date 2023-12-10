#pragma once 

#include<bits/stdc++.h>
#include "trie.h"
#include "cat.h"
#include "book.h"
using namespace std;

bool checkNumerical(string num){
    for(int i=0;i<num.size();i++){
        if(num[i] < '0' || num[i] > '9')  return false;
    }
    return true;
}

class manage{

public:
    Trie allBooks;  // Trie for storing all books
    Trie allBooksRev;   // Trie for storing all books in reverse order
    cat CatsRoot;      // Root of category nodes
    manage() : allBooks(), CatsRoot("all cats"), allBooksRev() {}

    void mainf(){
        string in = "";
        while(in != "exit"){
            cout<<"1.add a category "<<endl;
            cout<<"2.add a book "<<endl;
            cout<<"3.remove a cetegory "<<endl;
            cout<<"4.remove a book "<<endl;
            cout<<"5.search "<<endl;
            cout<<"6.print all books of a cetegory"<<endl;
            cout<<"7.see a book detail"<<endl;
            cout<<"exit"<<endl;

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
                    addingcat = findCat(selCat, &CatsRoot);
                    if(addingcat == nullptr){
                        cout<<"can't find the category"<<endl;
                        continue;
                    }
                }
                
                cout<<"new category : "<<endl;
                if(in != "1") cin.ignore();
                getline(cin, catName); 
                if(findCat(catName, addingcat) != nullptr) {
                    cout<<"category exists"<<endl;
                    continue;
                }       
                addCat(catName, addingcat);
                cout<<"added"<<endl;
            }
            else if(in == "2"){
                string bookName, writer, catName, price;

                cout<<"category : "<<endl;
                cin.ignore();
                getline(cin, catName);
                cout<<"name : "<<endl;
                getline(cin, bookName);
                cout<<"writer : "<<endl;
                getline(cin, writer);
                cout<<"price : "<<endl;
                getline(cin, price);
                
                addBooks(bookName, writer, catName, price, &CatsRoot);
            }
            else if(in == "3"){
                cin.ignore();
                removeCat();
            }
            else if(in == "4"){
                cin.ignore();
                removeBook();
            }
            else if(in == "5"){
                cin.ignore();
                printByTrie();
            }
            else if(in == "6"){
                cin.ignore();
                printBooks();

            }
            else if(in == "7"){
                cin.ignore();
                printAbook(&CatsRoot);       
            }
            else if(in == "exit"){
                break;
            }   
        }
    }






    // Function to check if a book with a given key exists
    bool checkBook(string key){
        return (allBooks.search(key) == nullptr || allBooks.search(key)->book == nullptr);
    }
    
    // Function to check if a category with a given key exists    
    bool checkCat(string key){
        return allBooks.search(key)->book == nullptr;
    }
    
    // Function to find a category with a given key using BFS
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

    // Function to add a category
    void addCat(string catName, cat* addRoot)   {
        cat* addedCat = new cat(catName);
        addRoot->cats.push(addedCat);
    }

    // Function to reverse a string
    string reverseStr(string str)
    {
        int n = str.length();
        for (int i = 0; i < n / 2; i++)
            swap(str[i], str[n - i - 1]);
        return str;
    }

    // Function to add a book
    void addBooks(string bookName, string writer, string catName, string price, cat* start) {
        cat* selecetedCat = findCat(catName, &CatsRoot);
        Book* book = new Book(bookName, writer, price, catName);
        Book* bookRev = new Book(reverseStr(bookName), writer, price, catName);

        if (!checkBook(bookName) || selecetedCat == nullptr || !checkNumerical(price)) {
            cout << "can't add the book" << endl;
            return;
        }
        selecetedCat->books.push(book);
        allBooks.insert(book);
        allBooksRev.insert(bookRev);
        selecetedCat->books.sort();
    }

    // Function to remove a book
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
        int index = -1;
        while(!bfsQ.empty()){
            cur = bfsQ.front();
            bfsQ.dequeue();
            for(int i =0;i<cur->cats.getSize();i++){
                for(int j=0;j<cur->cats.get(i)->books.getSize();j++){
                    if(cur->cats.get(i)->books.get(j)->getName() == bookName){
                        check = true;
                        cur->cats.get(i)->books.pop(j);
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


        allBooks.remove(bookName);
        cout<<"removed."<<endl;
    }

    // Function to find the parent category of a given category
    cat* findParentCat(const string& catName, cat* bfsRoot) {
        Queue<cat*> bfsQ;
        cat* cur = bfsRoot;
        bfsQ.enqueue(cur);

        while (!bfsQ.empty()) {
            cur = bfsQ.front();
            bfsQ.dequeue();

            for (int i = 0; i < cur->cats.getSize(); i++) {
                if (cur->cats.get(i)->name == catName) {
                    return cur;
                }
                bfsQ.enqueue(cur->cats.get(i));
            }
        }

        return nullptr;
    }

    // Function to remove a category
    void removeCat(){
        string catName;
        cout << "Enter category name to remove: \n1. Return" << endl;
        getline(cin, catName);
        if (catName == "1") return;

        // Find the category to be removed
        cat* categoryToRemove = findCat(catName, &CatsRoot);
        if (categoryToRemove == nullptr) {
            cout << "Can't find the category" << endl;
            return;
        }

        // Remove books of the category from allBooks
        for (int i = 0; i < categoryToRemove->books.getSize(); ++i) {
            Book* bookToRemove = categoryToRemove->books.get(i);
            // cout<<bookToRemove->getName()<<endl;
            allBooks.remove(bookToRemove->getName());
        }

        cat* parentCategory = findParentCat(catName, &CatsRoot);
        cout<<parentCategory->name<<endl;
        if (parentCategory != nullptr) {
            parentCategory->removeCat(catName);
            cout << "Category removed." << endl;
        } else {
            cout << "Category has no parent." << endl;
        }
    }

    // Function to print all books
    void printBooks(){
        string catName, in;
        cout<<"1.print all books\n2.print books of an specific category\nelse.return"<<endl;
        cin>>in;
        cat* printRoot = &CatsRoot;
        if(in == "2"){
            cout<<"write the categories name :"<<endl;
            cin.ignore();
            getline(cin, catName); 
            printRoot = findCat(catName, &CatsRoot);
        }
        
        if(printRoot == nullptr){
            cout<<"can't find the category"<<endl;
            return;
        }

        Stack<cat*> dfsSt;
        Stack<int> space;
        cat* dfsRoot = printRoot;
        cat* cur = dfsRoot;
        space.push(0);
        dfsSt.push(cur);
        int sp = 0;
        bool check = false;
        while(!dfsSt.empty()){
            cur = dfsSt.reTop();
            sp = space.reTop();
            space.pop();
            dfsSt.pop();

            for(int i=0;i<sp;i++)  cout<<"  ";
            cout<<"category : "<<cur->name<<endl;
    
            for(int i=0;i<cur->books.getSize();i++){
                for(int i=0;i<sp;i++) cout<<"   ";
                cout<<cur->books.get(i)->getName()<<endl;
            }

            for(int i =0;i<cur->cats.getSize();i++){
                dfsSt.push(cur->cats.get(i));
                space.push(sp+1);
            }
        }

        string in1;
        cout<<"see details of a book : \ny.yes\nelse.no"<<endl;
        cin>>in1;
        if(in1 != "y") return;;
        cin.ignore();
        printAbook(findParentCat(catName, &CatsRoot));
    }

    // void printByTrie() {
    //     cout << "Enter book's name:\n1.Return\n";
    //     string bookName;
    //     getline(cin, bookName);
    //     if (bookName == "1") return;

    //     TrieNode* printNode = allBooks.search(bookName);
    //     // TrieNode* printNodeRev = allBooksRev.search(reverseStr(bookName));

    //     if (printNode == nullptr) {
    //         cout << "No books found.\n";
    //         return;
    //     }

    //     allBooks.printBookBfs(printNode);
    //     // allBooksRev.printBookBfsRev(printNodeRev);

    //     string in1;
    //     cout<<"see details of a book : \ny.yes\nelse.no"<<endl;
    //     cin>>in1;
    //     if(in1 != "y") return;
    //     cin.ignore();
    //     printAbook(&CatsRoot);
    // }
    
    // Function to print books based on Trie search
    void printByTrie() {
        cout << "Enter book's name:\n1.Return\n";
        string bookName;
        getline(cin, bookName);
        if (bookName == "1") return;

        TrieNode* printNode = allBooks.search(bookName);
        TrieNode* printNodeRev = allBooksRev.search(reverseStr(bookName));

        if (printNode == nullptr && printNodeRev == nullptr) {
            cout << "No books found.\n";
            return;
        }

        if (printNode != nullptr) {
            cout << "Books with '" << bookName << "' at the start:\n";
            allBooks.printBookBfs(printNode);
        }

        if (printNodeRev != nullptr) {
            cout << "Books with '" << bookName << "' at the end:\n";
            allBooksRev.printBookBfsRev(printNodeRev);
        }

        string in1;
        cout << "See details of a book:\n1.Yes\nelse.No\n";
        cin >> in1;
        if (in1 != "1") return;
        cin.ignore();
        printAbook(&CatsRoot);
    }   

    // Function to print details of a specific book
    void printAbook(cat* searchRoot){
        string bookName;
        cout<<"eneter the books name : \n1.return"<<endl;
        getline(cin, bookName);
        cout<<bookName<<endl;
        if(bookName == "1") return;
        if(checkBook(bookName)){
            cout<<"can't find the book"<<endl;
            return;
        }
        cat* bfsRoot = searchRoot;
        Queue<cat*> bfsQ;
        cat* cur = bfsRoot;
        bfsQ.enqueue(cur);
        bool check = false;
        int index = -1;
        while(!bfsQ.empty()){
            cur = bfsQ.front();
            bfsQ.dequeue();
            for(int i =0;i<cur->cats.getSize();i++){
                for(int j=0;j<cur->cats.get(i)->books.getSize();j++){
                    cout<<cur->cats.get(i)->books.get(j)->getName()<<" "<<bookName<<endl;
                    if(cur->cats.get(i)->books.get(j)->getName() == bookName){
                        check = true;
                        cur->cats.get(i)->books.get(j)->print();
                        break;
                    }
                }
                bfsQ.enqueue(cur->cats.get(i));
            }
            if(check) break;
        }

        if(!check){
            cout<<"can't find the book"<<endl;
            return;
        }
    }

    
};