#include "MyCart.h"
// Function to add an item to the cart
void MyCart::addItem() {
    string item_name;
    double item_price;
    int item_quantity;

    cout << "Enter item name: ";
    cin >> item_name;
    cout << "Enter item price: ";
    cin >> item_price;
    cout << "Enter item Quantity: ";
    cin >> item_quantity;

    Item newItem(item_name, item_price, item_quantity);
    
    cart.push_back(newItem);

    cout << item_name << " added to the cart. "<< endl;
    
}



// Function to calculate the total amount in the cart
double MyCart::calculateTotal() const {
    double total = 0;
    for (const auto& item : cart) {
        total += item.price;
    }
    return total;
}

void MyCart::displayCart() const
{
    if (cart.empty()) {
        cout << endl << ">>> There is no items in your cart <<<" << endl;
        return;
    }

    double total = 0.0;

    cout << endl << "----------------> Items in Your Cart <-----------------" << endl << endl;
    cout << setw(20) << left << "Product" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Total" << endl;
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;

    for (auto& product : cart) {

        double productTotal = product.price * product.quantity;
        total += productTotal;
        cout << setw(20) << left << product.name << setw(10) << product.quantity << '$' << setw(10) << product.price << '$' << setw(15) << productTotal << endl;
    }

    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
    cout << endl << setw(45) << right << "Total Price: " << '$' << total << endl << endl;
    cout << "-----------------> End of Your Cart <------------------" << endl << endl;
}

// Function to display the items in the cart
void MyCart::displayReceipt() const {
    if (cart.empty()) {
        cout << endl << ">>> No items Have been added <<<" << endl;
        return;
    }

    double total = 0.0;

    cout << "==================== Your Receipt =====================" << endl << endl;
    cout << setw(20) << left << "Product" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Total" << endl;
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;

    for (auto& product : cart) {
        double productTotal = product.price * product.quantity;
        total += productTotal;
        cout << setw(20) << left << product.name << setw(10) << product.quantity << '$' << setw(10) << product.price << '$' << setw(15) << productTotal << endl;
    }

    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
    cout << endl << setw(45) << right << "Total Price: " << '$' << total << endl << endl;
    cout << "================ End of Your receipt ==================" << endl << endl;
}