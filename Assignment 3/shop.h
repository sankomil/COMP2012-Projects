//do NOT submit this file
//do NOT modify this file

#ifndef SHOP_H
#define SHOP_H

#include "product.h"
#include "hashTable.h"

#include <string>
using std::string;

//a shop 
//it uses a hash table as its inventory
class Shop
{
private:
    string name; //name of the shop
    int profit; //profit made by the shop so far; 0 initially
    HashTable<string, Product>* inventory; //inventory of products listed in the shop

public:
    //constructor
    //except for the first parameter which is the shop name
    //all other parameters will be used to construct the hash table
    Shop(string name, int m, int (*h)(string), int (*h2)(string), Mode mode, double loadLimit);

    //deep copy constructor
    Shop(const Shop& another);

    //move constructor
    //do all you should do in a move constructor
    //also set another.name to "moved" afterward
    Shop(Shop&& another);

    //destructor
    ~Shop();

    //deep assignment
    Shop& operator=(const Shop& another);

    //add an amount (quantity) of a product specified by the name
    //there are two cases
    //1. if the product is already in the inventory, simply add the quantity to the inventory 
    //by updating the existing product entry in the inventory, the given price can be ignored in this case
    //return true at the end
    //2. otherwise, add the new product to the inventory with the given quantity and price
    //however, adding a new product to the hashtable may or may not be successful
    //if the hashtable's add function succeeds, return true
    //if the hashtable's add function fails (i.e. it returns -1, see the comment in hashTable.h), return false
    bool addProduct(string name, int quantity, int price);

    //sell an amount (quantity) of product specified by the name
    //first of all, check if the product exists by the given name
    //if it doesn't exist, do nothing and return false
    //otherwise, proceed with the sale as follows
    //if there is not enough stock to sell in the inventory, simply return false
    //if there is enough stock to sell in the inventory, sell it
    //selling it means to remove "quantity" of the product from the inventory
    //and add price*quantity to the shop's profit as the shop profits from the sale
    //when the quantity of the product reaches zero, remove the product altogether from the inventory
    //i.e. remove the product entry from the hash table
    //lastly, return true as the sale is done successfully
    bool sellProduct(string name, int quantity);

    //returns the shop name
    //given
    string getName() const {return name;};

    //print the shop to the ostream
    //given; just like the rest of this file, do not modify
    void printDetails(std::ostream& os) const
    {
        os << "Shop Name: " << name << std::endl;
        os << "Profit:    $" << profit << std::endl;
        os << "Inventory: ";
        inventory->print(os);
    }
};

//the definition of the following is given in the main.cpp
std::ostream& operator<<(std::ostream& os, const Shop& s);

#endif