#include "CreditCardNumber.hpp"
bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

CreditCardNumber::CreditCardNumber(const std::string& num) : card_number(num) {}

std::string CreditCardNumber::cleanCardNumber() const {
    std::string only_number;
    for (char i = 0; i < card_number.size(); i++) {
        if (isdigit(card_number[i])) {
            only_number += card_number[i];
        }
    }
    return only_number;
}

bool CreditCardNumber::isValidLuhn() const {
    std::string card_number_only = cleanCardNumber();
    int sum = 0;
    int digit = 0;
    bool second_number = false;
    for (int i = card_number_only.length() - 1; i >= 0; i--) {
        digit = card_number_only[i] - '0';
        if (second_number) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        second_number = !second_number;
    }
    return (sum % 10 == 0);
}


bool CreditCardNumber::isValid() const {
    if (cleanCardNumber().length() < 2) {
        return false;
    }
    return isValidLuhn();
}
