#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "enum.h"
#include <iostream>

using namespace std;

template <class T>
class BinarySearchTree : public BinaryTree<T>
{
public:
   Error_code insert(const T &);
   Error_code remove(const T &);

protected:
   // Auxiliary functions
   Error_code search_and_insert(BinaryNode<T> *&sub_root, const T &new_data);
   Error_code search_and_delete(BinaryNode<T> *&sub_root, const T &target);
};

template <class T>
Error_code BinarySearchTree<T>::insert(const T &new_data)
{
   return search_and_insert(this->root, new_data);
}

template <class T>
Error_code BinarySearchTree<T>::search_and_insert(BinaryNode<T> *&sub_root, const T &new_data)
{
   Error_code result;

   if (sub_root == nullptr)
   { // sub_root: a variable of BinaryNode<T>*
      // time to insert a Node, stopping condition
      BinaryNode<T> *new_node = new BinaryNode<T>(new_data);
      sub_root = new_node; // changing Node(32)’s left pointer to new_node by passing the sub_root by reference
      result = success;
   }
   else if (sub_root->data == new_data)
   { // base case, stopping condition
      // approach 1: does not allow duplicate data
      cout << "Duplicate data." << "\n";
      // approach 2: does allow duplicate data
      // the node structure must have another data member to count number of duplicates
      // increase the count by 1, this way each Node has a unique value for data (key)
      result = duplicate_error;
   }
   else if (sub_root->data < new_data)
   { // recursive case 1: insert to right subtree
      result = search_and_insert(sub_root->right, new_data);
   }
   else if (sub_root->data > new_data)
   { // recursive case 2: insert to left subtree
      result = search_and_insert(sub_root->left, new_data);
   }
   return result;
}

template <class T>
Error_code BinarySearchTree<T>::remove(const T &target)
/*
Post: If a T with a key matching that of target belongs to the
      BinarySearchTree, a code of success is returned, and the corresponding node
      is removed from the tree.  Otherwise, a code of not_present is returned.
Uses: Function search_and_delete
*/
{
   return search_and_delete(this->root, target);
}

template <class T>
Error_code BinarySearchTree<T>::search_and_delete(BinaryNode<T> *&sub_root, const T &target)
/*
Pre:  sub_root is either NULL or points to a subtree of the BinarySearchTree.
Post: If the key of target is not in the subtree, a code of not_present
      is returned.  Otherwise, a code of success is returned and the subtree
      node containing target has been removed in such a way that
      the properties of a binary search tree have been preserved.
Uses: Functions search_and_delete recursively
*/
{
   
   if (sub_root == nullptr)  //target is not found
   {
      return not_present;
   }

   Error_code result = success;
   if(sub_root->data == target)  //target is found
   {
      BinaryNode<T>* temp = sub_root;
      if(sub_root->left == nullptr)  //target in leaf or internal node with only right child
      {
         //if sub_root is a leaf, then sub_root->right is nullptr
         //if sub_root is an internal node with non-null right child, the right child takes the position of the sub_root in relation to the parent of the sub_root
         sub_root = sub_root->right;
         delete temp;
      }
      else if(sub_root->right == nullptr) //target in leaf or internal node with only left child
      {
         //if sub_root is a leaf, then sub_root->left is nullptr
         //if sub_root is an internal node with non-null left child, the left child takes the position of the sub_root in relation to the parent of the sub_root
         sub_root = sub_root->left;
         delete temp;
      }
      else  //target in an internal node with two children, use immediate predecessor or successor (successor in this case)
      {
         BinaryNode<T>* successor = sub_root->right;
         while(successor->left != nullptr)
            successor = successor->left;

         sub_root->data = successor->data;
         result = search_and_delete(sub_root->right, successor->data);
      }
   }
   else
   {
      if(target > sub_root->data)
         result = search_and_delete(sub_root->right, target);
      else
         result = search_and_delete(sub_root->left, target);
   }

   return result;
}

#endif