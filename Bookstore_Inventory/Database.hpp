#pragma once

#include "book.hpp"
#include <vector>
#include <string>

class Database 
{
public:
    std::vector<Book> books;

    void loadData(const std::string& filename);
    void saveData(const std::string& filename);
    void addBook(const Book& book);
    void removeBook(const std::string& title);
    void displayBooks() const;
};


