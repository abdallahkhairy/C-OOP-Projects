#pragma once
#include <string>

using namespace std;

class CreditCardNumber
{
private:
    
    bool isValidLuhn() const;

public:
    string card_number;

    string cleanCardNumber() const;
    CreditCardNumber(const string& num);
    bool isValid() const;
};