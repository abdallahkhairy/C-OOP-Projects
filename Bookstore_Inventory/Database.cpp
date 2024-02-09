#include "Database.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

void Database::loadData(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        books.clear(); // Clear existing data
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string title, author;
            int year, quantity;
            double price;
            getline(iss, title, ',');
            if (!title.empty() && title.back() == ',') {
                title.pop_back();
            }
            // Trim leading whitespaces from title
            title.erase(0, title.find_first_not_of(" \t\r\n"));
            // Trim trailing whitespaces from title
            title.erase(title.find_last_not_of(" \t\r\n") + 1);

            getline(iss, author, ',');
            if (!author.empty() && author.back() == ',') {
                author.pop_back();
            }
            // Trim leading whitespaces from author
            author.erase(0, author.find_first_not_of(" \t\r\n"));
            // Trim trailing whitespaces from author
            author.erase(author.find_last_not_of(" \t\r\n") + 1); 
            iss >> year >> quantity >> price;
            Book book(title, author, year, quantity, price);
            books.push_back(book);
        }
        file.close();
    }
    else {
        cerr << "Error: Unable to open file " << filename << endl;
    }
}

void Database::saveData(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.getTitle() << " " << book.getAuthor() << " " << book.getYear() << " " << book.getQuantity() << " " << book.getPrice() << endl;
        }
        file.close();
    }
    else {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
    }
}

void Database::addBook(const Book& book) {
    books.push_back(book);
    saveData("books.txt");
}

void Database::removeBook(const string& title) {
    auto it = find_if(books.begin(), books.end(), [&](const Book& book) {
        return book.getTitle() == title;
        });

    if (it != books.end()) {
        books.erase(it);
        cout << "Book '" << title << "' removed from database." << endl;
        saveData("books.txt"); // Save the updated data to the file
    }
    else {
        cout << "Book '" << title << "' not found in database." << endl;
    }
}


void Database::displayBooks() const {
    cout << "Inventory: " << books.size() << endl;
    for (char i = 0; i < books.size(); ++i) {
        cout << " => Title: " << books[i].getTitle() << endl << "     Author: " << books[i].getAuthor() << endl << "     Year: " << books[i].getYear() << endl << "     Quantity: " << books[i].getQuantity() << endl << "     Price: " << books[i].getPrice() <<"LE" << endl;
    }
}
