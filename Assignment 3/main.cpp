//do NOT submit this file

#include <iostream>
#include "shop.h"
#include "bst.h"
#include "hashTable.h"
#include "mall.h"

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& os, const BST<T>& t)
{
    t.printTree(os);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Product& p)
{
	os << "(\"" << p.getName() << "\"," << p.getQuantity() << ",$" << p.getPrice() << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Shop& s)
{
    os << "(" << s.getName() << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Mall& m)
{
    m.print(os);
	return os;
}

template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const HashTable<A,B>& ht)
{
	ht.print(os);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Mode& m)
{
    switch(m)
    {
        case Mode::LINEAR:
            os << "LINEAR";
            break;
            
        case Mode::DOUBLE:
            os << "DOUBLE";
            break;

        case Mode::QUADRATIC:
            os << "QUADRATIC";
            break;
    }
	return os;
}

int main()
{
    //feel free to comment out the part that you have not finished yet
    //and feel free to design your own test cases
    //however, you MUST make sure your submitted code can be compiled with the unmodified original version of this file
    //that is, even you may not be able to finish all the parts, you still should put in dummy (empty) implementations
    //to all parts so that your submitted code can be compiled and graded

    cout << boolalpha;

    cout << "=================== BST Tests ===================" << endl;

    {   //the bracket here is just to create a scope, so that
        //all static objects will be destructed at the end of it

        BST<int> bst1;
        cout << "add (\"e\", 55): " << bst1.add("e", 55) << endl;
        cout << "add (\"a\", 11): " << bst1.add("a", 11) << endl;
        cout << "add (\"c\", 33): " << bst1.add("c", 33) << endl;
        cout << "add (\"g\", 77): " << bst1.add("g", 77) << endl;
        cout << endl << "~bst1~" << endl;
        cout << bst1 << endl;
        cout << endl;
        cout << "add (\"g\", 777): " << bst1.add("g", 777) << endl;
        cout << "remove with key \"z\": " << bst1.remove("z") << endl;
        cout << "remove with key \"a\": " << bst1.remove("a") << endl;
        cout << endl << "~bst1~" << endl;
        cout << bst1 << endl;
        cout << endl;

        BST<int> bst2;
        bst2.add("d", 44);
        bst2.add("b", 22);
        bst2.add("f", 66);
        bst2.add("Z", 1); 
        //note: "Z" is actually smaller than "a" when you do string comparison
        //and that is the order we use for ordering the items in our BST
        //for example:
        //string s1 = "Z";
        //string s2 = "a";
        //cout << boolalpha << (s2>s1) << endl; //prints true

        cout << endl << "~bst2~" << endl;
        cout << bst2 << endl;
        cout << endl;

        cout << endl;
        cout << "After merging..." << endl;

        bst1.merge(bst2);
        cout << endl << "~bst1~" << endl;
        cout << bst1 << endl;
        cout << endl;
        cout << endl << "~bst2~" << endl;
        cout << bst2 << endl;
        cout << endl;
    }

    int (*fun)(int) = [](int n){return n+1;};
    int (*fun2)(int) = [](int n){return n*2;};

    Mode modes[] = {Mode::LINEAR, Mode::QUADRATIC, Mode::DOUBLE};
    for(Mode mode : modes)
    {
        cout << "==================== HashTable Tests: " << mode << " Mode ==================" << endl << endl;

        int keys[] = {6,1,13,20,99999}; //intentionally, there are more keys than values
        int values[] = {66,11,133,200};
        HashTable<int, int> ht(7, fun, fun2, mode, 0.5);

        cout << "empty table:" << endl;
        cout << ht << endl;
        for(int i=0; i<sizeof(values)/sizeof(int); i++)
        {
            cout << "add {" << keys[i] << "," << values[i] << "}: collisions=" << ht.add(keys[i], new int(values[i])) << endl;
            cout << ht << endl;
        }

        for(int k: keys)
        {
            int* p = ht.get(k);
            if(p) 
                cout << "found (" << k << "," << *p << ")" << endl;
            else
                cout << "not found key " << k << endl;
        }
        cout << endl;

        cout << "current table:" << endl;
        cout << ht << endl;
        cout << "remove 1: " << ht.remove(1) << endl;
        cout << "remove 11: " << ht.remove(11) << endl;
        cout << ht << endl;

        cout << "add " << 28 << ": collisions=" << ht.add(28, new int(2800)) << endl;
        cout << ht << endl;
        cout << "add " << 27 << ": collisions=" << ht.add(27, new int(2700)) << endl;
        cout << ht << endl;
    }

    cout << "==================== Hastable operator= Tests ==================" << endl;

    int keys[] = {6,1,13,20};
    int values[] = {66,11,133,200};
    HashTable<int, int>* pht1 = new HashTable<int, int>(7, fun, fun2, Mode::LINEAR, 0.5);
    HashTable<int, int>* pht2 = new HashTable<int, int>(7, fun, fun2, Mode::LINEAR, 0.5);
    for(int i=0; i<sizeof(keys)/sizeof(int); i++)
    {
        cout << "add {" << keys[i] << "," << values[i] << "}: collisions=" << pht1->add(keys[i], new int(values[i])) << endl;
    }
    *pht2 = *pht1;
    cout << "add " << 28 << ": collisions=" << pht1->add(28, new int(2800)) << endl;
    cout << *pht1 << endl;
    delete pht1;
    cout << *pht2 << endl;
    delete pht2;

    cout << "=================== Shop Tests ===================" << endl;
    { 
        int (*fun3)(string) = [](string s){return 5 - ((int)s.length()) % 5;};

        Shop* mcRonald = new Shop("McRonald", 7, fun3, fun3, Mode::LINEAR, 0.5);
        mcRonald->printDetails(cout);
        cout << "addProduct: " << mcRonald->addProduct("Fries", 1000, 10) << endl;
        mcRonald->printDetails(cout);
        cout << "sellProduct: " << mcRonald->sellProduct("Fries", 400) << endl;
        mcRonald->printDetails(cout);
        
        cout << "MAGICAL CLONE!" << endl;
        Shop* mcRonaldTwo = new Shop(*mcRonald);
        mcRonaldTwo->printDetails(cout);

        cout << "Move it!" << endl;
        Shop mcRonaldThree = move(*mcRonald);
        mcRonaldThree.printDetails(cout);
        cout << "mcRonald is " << mcRonald->getName() << "!" << endl;

        delete mcRonald;
        delete mcRonaldTwo;
    }
    
    cout << "=================== Mall Tests ===================" << endl;
    {
        Mall m1("Junk Food Nation");
        cout << "Build KFZ!" << endl;
        cout << m1.buildShop("KFZ") << endl;
        cout << "Build MCR!" << endl;
        cout << m1.buildShop("MCR") << endl;
        cout << endl;
        cout << "Junk Food Union:" << endl;
        cout << m1 << endl;
        cout << "nope = " << m1.getShop("NOPE") << endl;
        cout << endl;
        cout << "Make some rice in KFZ: " << m1.getShop("KFZ")->addProduct("CRice", 33, 8) << endl;
        //(3*37^4 +18*37^3 + 9*37^2 + 3*37^1 + 5) % 7 = 1, so "CRice" will be stored at cell 1
        //by the way, we won't test product names that are so long that makes your hash function overflows
        cout << endl;
        cout << "KFZ:" << endl;
        m1.getShop("KFZ")->printDetails(cout);

        Mall m2("Healthy Food Republic");
        cout << "Build ABC!" << endl;
        cout << m2.buildShop("ABC") << endl;
        cout << "Build ZZZ!" << endl;
        cout << m2.buildShop("ZZZ") << endl;
        cout << "Healthy Food Republic:" << endl;
        cout << m2 << endl;

        m1.mergeMall(m2, "Healthy Junk Food Super Duper GG Empire");
        cout << m1 << endl;
        cout << m2 << endl;
    }

    cout << endl << "Done! Hopefully there is no memory leak..." << endl;

    return 0;
}
