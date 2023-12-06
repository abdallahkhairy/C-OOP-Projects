#include <iostream>
#include <vector>
#include <iomanip>

#include "MyCart.hpp"

using namespace std;

int main() {
    MyCart cart;

    int choice;

    do {
        cout << endl <<"===== Customer Billing System ===== "<< endl<<endl;
        cout << "1- Add Item to Your Cart "<< endl;
        cout << "2- View Cart items "<< endl;
        cout << "3- Display The Receipt "<< endl;
        cout << endl << "To Quit Press 0 "<< endl;
        cout << endl << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cart.addItem();
        break;
        case 2:
            cart.displayCart();
            break;
        case 3:
            cart.displayReceipt();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" <<endl<< "Please try again" << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}