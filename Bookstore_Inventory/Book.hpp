#pragma once

#include <string>

using namespace std;

class Book
{
public:
    string title;
    string author;
    int year;
    int quantity;
    double price;


    Book();
    Book(const string& title, const string& author, int year, int quantity, double price);

    const string& getTitle() const;
    const string& getAuthor() const;
    int getYear() const;
    int getQuantity() const;
    double getPrice() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setYear(int year);
    void setQuantity(int quantity);
    void setPrice(double price);

};

