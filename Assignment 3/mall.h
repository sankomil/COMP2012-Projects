//do NOT submit this file
//do NOT modify this file

#ifndef MALL_H
#define MALL_H

#include "bst.h"
#include "shop.h"

//a mall
//a BST is usd to store the shops
class Mall 
{
private:
    string name; //the mall name
    BST<Shop> shops; //the shops

public:
    //constructor
    Mall(string name);

    //add a shop given the name
    //if an existing shop has the same name as the given name, do nothing and return false
    //otherwise, add the shop and return true
    //all shops use LINEAR mode for collision resolving and have initial hash table sizes of 7
    //and they should use the hash function shown in "How to Deal with String Keys: Method 3" 
    //(page 14 of the Hashing lecture slides)
    //you can assume the given name has English letters only,
    //and that we would treat lowercase letters and uppercase letters the same
    //in the calculation, we use natural numbers (instead of ASCII codes) to represent the letters
    //that means we will use 1, 2, 3, ..., 25, 26 to denote, respectively,
    //'a' or 'A', 'b' or 'B', 'c' or 'C', ..., 'y' or 'Y', 'z' or 'Z'
    //you may find a calculation example in a comment in main.cpp for you to verify your understanding
    bool buildShop(string name);

    //remove a shop given the name
    bool demolishShop(string name);

    //return a shop given the name
    Shop* getShop(string name);

    //merge this mall's shops with another's shops with BST<Shop>::merge, and then change this mall's name to newName
    void mergeMall(Mall& another, string newName);

    //print the mall to the ostream
    //given; just like the rest of this file, do not modify
    void print(std::ostream& os) const
    {
        os << "Mall Name: " << name << std::endl;
        os << "Shops: " << std::endl;
        shops.printTree(os);
    }
};

#endif