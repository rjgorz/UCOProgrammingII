#ifndef BINARYNODE_H
#define BINARYNODE_H

#include "enum.h"

template <class T>
struct BinaryNode{
//    data members:
   T data;
   BinaryNode<T>* left;
   BinaryNode<T>* right;
//    constructors:
   BinaryNode();
   BinaryNode(const T&);

   // virtual methods:
   virtual void set_balance(Balance_factor b);
   virtual Balance_factor get_balance() const;
};

template <class T>
BinaryNode<T>::BinaryNode() {
   data = NULL;
   left = nullptr;
   right = nullptr;
}

template <class T>
BinaryNode<T>::BinaryNode(const T &x) {
   data = x;
   left = nullptr;
   right = nullptr;
}

// Dummy functions
template <class T>
void BinaryNode<T>::set_balance(Balance_factor b) {
}

template <class T>
Balance_factor BinaryNode<T>::get_balance() const {
	return equal_height;
}

#endif