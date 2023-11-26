#pragma once
#include <string>
using namespace std;


class Item
{
    public:
    string name;
    double price;
    int quantity;

    Item(string item_name, double item_price, int item_quantity);
};

