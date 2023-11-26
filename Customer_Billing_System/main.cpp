#include <iostream>
#include <vector>
#include <iomanip>

#include "MyCart.h"


using namespace std;

int main() {
    // Sample items in the inventory
    Item item1("Product A", 20.99, 4);
    Item item2("Product B", 15.49, 2);
    Item item3("Product C", 5.99, 10);

    // Creating a shopping cart
    MyCart cart;

    int choice;

    do {
        cout << endl <<"===== Customer Billing System ===== "<< endl;
        cout << "1- Add Item to Your Cart "<< endl;
        cout << "2- View Cart items "<< endl;
        cout << "3- Display The Receipt "<< endl;
        cout << "0- Quit "<< endl;
        cout << "Enter your choice: ";
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
            cout << "Exiting.." << endl;
            break;
        default:
            cout << "Invalid choice" <<endl<< "Please try again" << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}