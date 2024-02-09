#include "Bookstore.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void displayMenu();
void handleUserInput(Bookstore& library);

int main() {
    ifstream checkFile("books.txt");
    if (!checkFile) {
        std::ofstream createFile("books.txt");
        if (createFile) {
            createFile.close();
        } else {
            cerr << "Error: Failed to create books.txt" << endl;
            return 1; // Return with error code if file creation fails
        }
    } else {
        checkFile.close(); // Close the ifstream if it's open
    }

    // Create a library object
    Bookstore library;

    // Load data from a file
    library.loadData("books.txt");

    // Handle user input
    handleUserInput(library);

    // Save data to a file
    library.saveData("books.txt");

    return 0;
}

void displayMenu() {
    cout << "****************************" << endl;
    cout << "* Bookstore Inventory Menu * " << endl;
    cout << "****************************" << endl;
    cout << "* 1- Display Inventory     *" << endl;
    cout << "* 2- Add Book              *" << endl;
    cout << "* 3- Remove Book           *" << endl;
    cout << "* 4- Process Order         *" << endl;
    cout << "* 5- Exit                  *" << endl;
    cout << "****************************" << endl;
    cout << endl;
}

void handleUserInput(Bookstore& library) {
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
        case 1: {
            cout << "Displaying Inventory:" << endl;
            library.displayInventory();
            break;
        }
        case 2: {
            // Add Book
            string title, author;
            int year, quantity;
            double price;

            cout << "Enter title: ";
            getline(cin, title);
            title += " ,";
            cout << "Enter author: ";
            getline(cin, author);
            author += " ,";
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter price: ";
            cin >> price;

            Book newBook(title, author, year, quantity, price);
            library.addBook(newBook);
            cout << "Book added successfully." << endl;
            break;
        }
        case 3: {
            // Remove Book
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            library.removeBook(title);
            break;
        }
        case 4: {
            // Process Order
            string title;
            int quantity;
            cout << "Enter title of the book to order: ";
            getline(cin, title);
            cout << "Enter quantity: ";
            cin >> quantity;
            Order order{ title, quantity };
            library.processOrder(order);
            break;
        }
        case 5: {
            cout << "Exiting program." << endl;
            return;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }
        cout << endl;
    } while (true);
}