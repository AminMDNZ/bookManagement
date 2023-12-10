#pragma once
#include "DS.h"
#include "cat.h"
#include<bits/stdc++.h>
using namespace std;

// Class definition for Book
class Book {
    string writer, name, price, catName;

public:
    // constructor
    Book() : writer(""), name(""), price(""), catName("") {}

    Book(string name, string writer, string price, string catName)
        : name(name), writer(writer), price(price), catName(catName) {}

    // Function to print book details
    void print() const {
        cout << std::setw(20) << std::left << "Name:" << name << std::endl;
        cout << std::setw(20) << std::left << "Price:" << price << std::endl;        
        cout << std::setw(20) << std::left << "Writer:" << writer << std::endl;
        cout << std::setw(20) << std::left << "Category:" << catName << std::endl;
    }

    // Setter functions
    void setWriter(const std::string& writer) { this->writer = writer; }
    void setName(const std::string& name) { this->name = name; }
    void setPrice(const std::string& price) { this->price = price; }
    void setCatName(const std::string& catName) { this->catName = catName; }

    // Getter functions
    string getWriter() { return writer; }
    string getName()  { return name; }
    string getPrice()  { return price; }
    string getCatName()  { return catName; }
};
