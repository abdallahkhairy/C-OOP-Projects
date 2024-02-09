#include "Bookstore.hpp"
#include <iostream>
#include <algorithm>

void Bookstore::loadData(const std::string& filename) {
    database.loadData(filename);
}

void Bookstore::saveData(const std::string& filename) {
    database.saveData(filename);
}

void Bookstore::addBook(const Book& book) {
    database.addBook(book);
}

void Bookstore::removeBook(const std::string& title) {
    database.removeBook(title);
}

void Bookstore::displayInventory() const {
    database.displayBooks();
}



void Bookstore::processOrder(const Order& order) {
    auto it = std::find_if(database.books.begin(), database.books.end(), [&](const Book& book) {
        return book.getTitle() == order.title;
        });

    if (it != database.books.end()) {
        if (it->getQuantity() >= order.quantity) {
            it->setQuantity(it->getQuantity() - order.quantity);
            std::cout << "Order processed successfully." << std::endl;
        }
        else {
            std::cout << "Insufficient quantity available for '" << order.title << "'." << std::endl;
        }
    }
    else {
        std::cout << "Book '" << order.title << "' not found in inventory." << std::endl;
    }
}