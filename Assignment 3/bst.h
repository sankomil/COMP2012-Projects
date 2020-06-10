//do NOT submit this file
//do NOT modify this file

#ifndef BST_H_
#define BST_H_

#include <typeinfo>
#include <iostream>
#include <string>

using std::string;

//BST is a Binary Search Tree class
//
//It is basically what you have learned in the lecture, with some minor differences:
//- instead of storing a value (and use that value for determining where to put it in the tree)
//  a key-value pair will be stored
//- Key is always a std::string, its sole purpose is to determine where the item will be put in the tree
//  In other words, the items are arranged by their keys (instead of their values)
//- For comparing keys, simply use C++ std::string's built-in comparison
//  e.g. "s1 > s2" is the expression to check if string s1 is larger than string s2
//- Value to be stored in each node is of type T
//- Some common functions may have different requirements than those in the lecture notes, please read
//  their description comment carefully. For example, some functions have return values
//
//Notes:
//- Keys are unique (to be made sure whenever we add a new item to the tree)
//- You may assume T supports proper operator= and copy construction (i.e. deep copy will be used if necessary)

template <typename T>
class BST
{
private:
	struct BSTNode
	{
		string key; //key

		T value; //value
				//For your information: note that when a BST tree is destructed
				//the root's value will also be destructed as the
				//root BSTNode itself will be deleted in the BST destructor
				//if the type T has a destructor, that destructor will also be called

		BST<T> left; // left sub-tree (left child)

		BST<T> right; // right sub-tree (right child)

		BSTNode(string key, T value) : key(key), value(value) {}; //constructor
	};

	BSTNode *root = nullptr; //the root node; empty tree's root is nullptr

public:
	//constructor
	BST() = default;

	//destructor
	//given; do not modify
	~BST() { delete root; }

	//deep copy constructor
	BST(const BST &another);

	//return true if the tree is empty (i.e. no node at all)
	//return false otherwise
	bool isEmpty() const;

	//add a node to the tree, according to the given key and value
	//you have to use the exact algorithm described in the lecture notes
	//you should have the exact same result as our sample output
	//it should do nothing to the tree and return false when there is already a node that has the same key
	//otherwise, it should add the node and return true
	//again, assume T supports proper operator= and copy construction (i.e. deep copy will be used if necessary)
	bool add(string key, T value);

	//remove a node from the tree, according to the given key
	//if the key is found, it should remove the node and return true
	//otherwise, return false
	//note: you have to use the exact algorithm described in the lecture notes
	//when you need to delete a node that has 2 children,
	//you must replace the deleted node with the minimum node in its right sub-tree
	//note: as you delete a BSTNode, its value will also be destructed automatically
	bool remove(string key);

	//return the pointer to the node's value (i.e., T*) given a key
	//if the key is not found in the tree, return nullptr
	T *get(string key) const;

	//return the subtree that has the minimum-value node as its root node
	//return nullptr if the tree is empty
	const BST *findMin() const;

	//merge this tree with another
	//see webpage for description and example
	void merge(BST &another);

	//print the tree to the ostream
	//note that displayed tree is rotated 90 degree clockwise
	//given; just like the rest of this file, do not modify
	void printTree(std::ostream& os, int depth = 0) const
	{
		if (isEmpty())
		{
			if (depth == 0)
				os << "Nothing to see here!" << std::endl;
			return;
		}

		root->right.printTree(os, depth + 1);

		for (int j = 0; j < depth; j++)
			os << "\t\t";
		os << "(" << root->key << "," << root->value << ")" << std::endl;

		root->left.printTree(os, depth + 1);
	}
};

#include "bstImplementation.h"

#endif
