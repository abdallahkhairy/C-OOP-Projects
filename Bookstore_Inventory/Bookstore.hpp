#pragma once
#include <string>
#include "Database.hpp"

using namespace std;
struct Order {
    string title;
    int quantity;
};


class Bookstore 
{
private:
    Database database;

public:
    void loadData(const string& filename);
    void saveData(const string& filename);
    void addBook(const Book& book);
    void removeBook(const string& title);
    void displayInventory() const;
    void processOrder(const Order& order);
};
