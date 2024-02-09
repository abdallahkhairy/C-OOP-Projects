#include "Book.hpp"

Book::Book() : title(""), author(""), year(0), quantity(0), price(0.0) {}

Book::Book(const std::string& title, const std::string& author, int year, int quantity, double price)
    : title(title), author(author), year(year), quantity(quantity), price(price) {}

const std::string& Book::getTitle() const {
    return title;
}

const std::string& Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

int Book::getQuantity() const {
    return quantity;
}

double Book::getPrice() const {
    return price;
}

void Book::setTitle(const std::string& title) {
    this->title = title;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setYear(int year) {
    this->year = year;
}

void Book::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Book::setPrice(double price) {
    this->price = price;
}