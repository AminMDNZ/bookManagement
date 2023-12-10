#pragma once

#include "DS.h"
#include "book.h"
#include<bits/stdc++.h>

// Comparator struct to define custom comparison for Book pointers
struct cmp {
    bool operator()( Book* a,  Book* b) const {
        string s1 = a->getName();
        string s2 = b->getName();
        for (int i = 0; i < min(s1.size(), s2.size()); i++) {
            if (s1[i] != s2[i])
                return s1[i] < s2[i];
        }
        return s1.size() < s2.size();
    }
};

class cat {
public:
    string name;     // Name of the category
    HVector<Book*, cmp> books;       // Vector to store books in the category sorted
    HVector<cat*> cats;     // Vector to store subcategories
    cat(string name) : name(name), books(), cats() {}

    // Function to insert a book into the category
    void insertBook(Book* book) {
        books.push(book);
    }

    // Function to remove a subcategory by name
    void removeCat(string catName) {
        int index = -1;
        for (int i = 0; i < cats.getSize(); ++i) {
            if (cats.get(i)->name == catName) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            delete cats.get(index);
            cats.pop(index);
            cout << "Subcategory removed." << endl;
        } else {
            cout << "Subcategory not found." << endl;
        }
    }

    // Function to insert a subcategory
    void insertCat(cat* Cat) {
        cats.push(Cat);
    }
};
