#pragma once 

#include<bits/stdc++.h>
#include "DS.h"
#include "book.h"
using namespace std;

class TrieNode {
public:
    char data;
    struct cmp {
        bool operator()(const TrieNode* a, const TrieNode* b) const {
            char c1 = a->data;
            char c2 = b->data;

            return c1 < c2;
        }
    };
    HVector<TrieNode*, cmp> children;
    Book* book;  // Single book associated with the node

    TrieNode(char ch) : data(ch), book(nullptr) {}

    ~TrieNode() {
        for (int i = 0; i < children.getSize(); ++i) {
            delete children.get(i);
        }
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

    void insert(Book* book) {
        TrieNode* current = root;
        string str = book->getName();
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
        current->children.sort();
        current->book = book;
    }

    TrieNode* search(const string& key, TrieNode* curNode = nullptr) {
        TrieNode* current = (curNode == nullptr) ? root : curNode;
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
        
    void printBookBfs(TrieNode* Node){
        TrieNode* cur = Node;
        Queue<TrieNode*> bfsQ;
        bfsQ.enqueue(Node);
        while(!bfsQ.empty()){
            cur = bfsQ.front();
            cur->children.sort();
            bfsQ.dequeue();
            if(cur->book != nullptr) cout<<cur->book->getName()<<endl;
            for(int i=0;i<cur->children.getSize();i++){
                bfsQ.enqueue(cur->children.get(i));
            }
        }
    }

    string reverseStr(string str)
    {
        int n = str.length();
        for (int i = 0; i < n / 2; i++)
            swap(str[i], str[n - i - 1]);

        return str;
    }

    void printBookBfsRev(TrieNode* Node){
        TrieNode* cur = Node;
        Queue<TrieNode*> bfsQ;
        bfsQ.enqueue(Node);
        while(!bfsQ.empty()){
            cur = bfsQ.front();
            cur->children.sort();
            bfsQ.dequeue();
            if(cur->book != nullptr) cout<<reverseStr(cur->book->getName())<<endl;
            for(int i=0;i<cur->children.getSize();i++){
                bfsQ.enqueue(cur->children.get(i));
            }
        }
    }

    Book* select(const string& key) {
        if(search(key) == nullptr) return nullptr;
        return search(key)->book;
    }

    bool remove(string key){
        TrieNode* current = root;
        Stack<TrieNode*> path; 
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
            if (!child) {
                return false;
            }
            
            current = child;
        }

        if (current->book == nullptr) {
            return false;
        }

        current->book = nullptr;

        while (!path.empty()) {
            TrieNode* node = path.reTop();
            path.pop();

            if (node->children.getSize() == 0 && node->book == nullptr) {
                delete node;
            } else {
                break;
            }
        }
        return true;
    }
    
};