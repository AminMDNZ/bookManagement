#pragma once

#include "DS.h"
#include "book.h"
#include<bits/stdc++.h>

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
    string name;
    HVector<Book*, cmp> books;
    HVector<cat*> cats;
    cat(string name) : name(name), books(), cats() {}

    void insertBook(Book* book) {
        books.push(book);
    }

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

    void insertCat(cat* Cat) {
        cats.push(Cat);
    }
};
