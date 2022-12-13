#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"
#include <iostream>

using namespace std;

template <class T>
class BinaryTree {
public:
   BinaryTree();
   BinaryTree(const BinaryTree<T>&);
   BinaryTree<T>& operator=(const BinaryTree<T>&);
   virtual ~BinaryTree();  //clear()
   bool empty() const;
   void preorder(void (*visit)(T &));
   void inorder(void (*visit)(T &));
   void postorder(void (*visit)(T &));  //function pointer arguments

   int size() const;
   void clear();  //recursive_clear()
   int height() const;
   int leaf_count() const;

   void print() const; // A method to print out the tree using preorder

   //Add the prototypes of the Big-Three below and add their definitions later

protected:
   // Auxiliary functions
   void recursive_preorder(BinaryNode<T>* sub_root, void (*visit)(T&));
   void recursive_inorder(BinaryNode<T>* sub_root, void (*visit)(T&));
   void recursive_postorder(BinaryNode<T>* sub_root, void (*visit)(T&));
   int recursive_size(BinaryNode<T>* sub_root) const;
   void recursive_clear(BinaryNode<T>*& sub_root);
   int recursive_height(BinaryNode<T>* sub_root) const;
   int recursive_leaf_count(BinaryNode<T>* sub_root) const;
   BinaryNode<T>* recursive_copy(BinaryNode<T>* sub_root);

   void recursive_preorder_print_node(BinaryNode<T>* sub_root) const;

   // Data member
   BinaryNode<T>* root;
};

template <class T>
BinaryTree<T>::BinaryTree()
/*
Post: An empty binary tree has been created.
*/
{
   root = nullptr;
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree)
{
   root = recursive_copy(tree.root);
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
   clear();
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)
{
   BinaryTree local(tree);

   BinaryNode<T>* temp = this->root;
   this->root = local.root;
   local.root = temp;

   return *this;
}

template <class T>
bool BinaryTree<T>::empty() const
/*
Post: A result of true is returned if the binary tree is empty.
      Otherwise, false is returned.
*/
{
   bool result = (root == nullptr) ? true : false;
   return result;
}

template <class T>
void BinaryTree<T>::preorder(void (*visit)(T&))
/*
Post: The tree has been traversed in inorder sequence.
Uses: The function recursive_inorder
*/
{
   recursive_preorder(this->root, visit);  //visit has the starting address of the increment function passed by main
}

template <class T>
void BinaryTree<T>::inorder(void (*visit)(T&))
/*
Post: The tree has been traversed in inorder sequence.
Uses: The function recursive_inorder
*/
{
   recursive_inorder(this->root, visit);
}

template <class T>
void BinaryTree<T>::postorder(void (*visit)(T &))
/*
Post: The tree has been traversed in inorder sequence.
Uses: The function recursive_inorder
*/
{
   recursive_postorder(this->root, visit);
}

template <class T>
int BinaryTree<T>::size() const
/* 
Post: The number of entries in the binary tree is returned.
Uses: The function recursive_size
*/
{
   return recursive_size(this->root);
}


template <class T>
void BinaryTree<T>::clear()
/* 
Post: Dispose of all the nodes of the binary tree.
Uses: The function recursive_clear.
*/
{
   return recursive_clear(this->root);
}

template <class T>
int BinaryTree<T>::height() const
/* 
Post: The height of the binary tree is returned.
Uses: The function recursive_height
*/
{
   return recursive_height(this->root);
}

template <class T>
int BinaryTree<T>::leaf_count() const
{
   return recursive_leaf_count(this->root);
}


template <class T>
void BinaryTree<T>::print() const
/* 
Post: The tree has been traversed in preorder.  Each node and its two children is printed 
Uses: The function recursive_preorder_print_node
*/
{
   cout << endl;
   cout << "++++++++++++++++++++++" << endl;
   if(root == NULL)
      cout << "EMPTY TREE" << endl;
   else{
      if(root->left == NULL && root->right == NULL)
         cout << root->data << ":  -  -" << endl;

      recursive_preorder_print_node(root);
   }
   cout << "++++++++++++++++++++++" << endl;
   cout << endl;
}

// Functions

template <class T>
void BinaryTree<T>::recursive_preorder(BinaryNode<T>* sub_root, void (*visit)(T& ))
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: The subtree has been traversed in preorder sequence.
Uses: The function recursive_preorder recursively
*/
{
   if(sub_root != nullptr)
   {
      //V
      visit(sub_root->data);
      //L
      recursive_preorder(sub_root->left, visit);
      //R
      recursive_preorder(sub_root->right, visit);
   }
}

template <class T>
void BinaryTree<T>::recursive_inorder(BinaryNode<T>* sub_root, void (*visit)(T &))
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: The subtree has been traversed in inorder sequence.
Uses: The function recursive_inorder recursively
*/
{
   if(sub_root != nullptr)
   {
      //L
      recursive_inorder(sub_root->left, visit);
      //V
      visit(sub_root->data);
      //R
      recursive_inorder(sub_root->right, visit);
   }
}

template <class T>
void BinaryTree<T>::recursive_postorder(BinaryNode<T>* sub_root, void (*visit)(T &))
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: The subtree has been traversed in postorder sequence.
Uses: The function recursive_postorder recursively
*/
{
   if(sub_root != nullptr)
   {
      //L
      recursive_postorder(sub_root->left, visit);
      //R
      recursive_postorder(sub_root->right, visit);
      //V
      visit(sub_root->data);
   }
}

template <class T>
int BinaryTree<T>::recursive_size(BinaryNode<T>* sub_root) const
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: The number of entries in the subtree is returned.
Uses: The function recursive_size recursively
*/
{
   if(sub_root == nullptr)
      return 0;
   else
      return (recursive_size(sub_root->left) + 1 + recursive_size(sub_root->right));
}

template <class T>
void BinaryTree<T>::recursive_clear(BinaryNode<T>*& sub_root)
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: All the nodes in the subtree are disposed of in postorder.
Uses: The function recursive_clear recursively
*/
{
   if(sub_root != nullptr)
   {
      recursive_clear(sub_root->left);
      recursive_clear(sub_root->right);
      delete sub_root;
      sub_root = nullptr;
   }
}

template <class T>
int BinaryTree<T>::recursive_height(BinaryNode<T>* sub_root) const 
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: the height of the subtree is returned.
Uses: The function recursive_height recursively
*/
{
   if(sub_root == nullptr)
      return 0;
   
   int lh = recursive_height(sub_root->left);
   int rh = recursive_height(sub_root->right);

   return (lh > rh) ? lh + 1 : rh + 1;
}

template <class T>
int BinaryTree<T>::recursive_leaf_count(BinaryNode<T>* sub_root) const
{
   if(sub_root == nullptr)
      return 0;
   
   if(sub_root->left == nullptr && sub_root->right == nullptr)
      return 1;

   return recursive_leaf_count(sub_root->left) + recursive_leaf_count(sub_root->right);
}

template <class T>
BinaryNode<T>* BinaryTree<T>::recursive_copy(BinaryNode<T>* sub_root) 
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: returns a pointer to the root of a new binary tree that has exactly the same structure and content as those of the subtree.
Uses: The function recursive_copy recursively
*/
{
   if(sub_root == nullptr)
      return nullptr;
   
   BinaryNode<T>* new_node = new BinaryNode(sub_root->data);
   new_node->left = recursive_copy(sub_root->left);
   new_node->right = recursive_copy(sub_root->right);
   return new_node;
}


template <class T>
void BinaryTree<T>::recursive_preorder_print_node(BinaryNode<T>* sub_root) const
/*
Pre:  sub_root is either NULL or points to a subtree of the BinaryTree.
Post: The subtree has been traversed in preorder sequence.
Uses: The function recursive_preorder_print_node recursively
*/
{
   if (sub_root != NULL) {
      if(sub_root->left != NULL || sub_root->right != NULL){
         cout << sub_root->data << ":  ";
         if(sub_root->left != NULL)
            cout << sub_root->left->data << "  ";
         else
            cout << "-  "; // "-" represents no child
         if(sub_root->right != NULL)
            cout << sub_root->right->data << " ";
         else
            cout << "-  "; // "-" represents no child
         //cout << "; ";
         cout << endl;
      }
      recursive_preorder_print_node(sub_root->left);
      recursive_preorder_print_node(sub_root->right);
   }
}

#endif