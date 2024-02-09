#include <iostream>
#include <string>
#include "CreditCardNumber.hpp"

using namespace std;

int main() {
    string card_no;

    while (true) {
        cout << "Enter credit card number (or 'exit' to quit): ";
        getline(cin, card_no);

        if (card_no == "exit") {
            break;
        }

        CreditCardNumber card(card_no);

        if (card.isValid()) {
            cout << "Valid credit card number." << endl;
        }
        else {
            cout << "Invalid credit card number." << endl;
        }
    }

    return 0;
}
