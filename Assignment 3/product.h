//do NOT submit this file
//do NOT modify this file

#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
using std::string;

//a product in a shop's inventory
//it stores the name, quantity, and price of the product
class Product
{
private:
    string name; //name of the product
    int quantity; //quantity in the inventory
    int price; //price of the product; we assume all prices are positive integers

public:

    //constructor
    Product(string name, int quantity, int price) : name(name), quantity(quantity), price(price)
    {
    };

    //return the name
    string getName() const
    {
         return name; 
    };

    //return the quantity
    int getQuantity() const
    {
         return quantity; 
    };

    //return the price
    int getPrice() const
    {
         return price; 
    };

    //add n unit of the product to the inventory
    void add(int n)
    {
        quantity+=n; 
    };

    //take n of the product
    //adjust the quantity and return true if there is enough stock of this product
    //otherwise, do nothing and return false
    bool take(int n) 
    {
        if(quantity-n<0)
            return false;
        else 
        {
            quantity-=n; 
            return true;
        }
    };
};

//the definition of the following is given in the main.cpp
std::ostream& operator<<(std::ostream& os, const Product& p);

#endif