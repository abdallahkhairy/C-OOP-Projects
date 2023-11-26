#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "Item.h"

using namespace std;

class MyCart
{
private:
    // Create array of items and naming it cart
    vector<Item> cart;
public:

    // Function to add an item to the cart
    void addItem();

    // Function to calculate the total amount in the cart
    double calculateTotal() const;

    // Function to display the items in the cart
    void displayCart() const;

    // Function to display The receipt
    void displayReceipt() const;
    
  
};

