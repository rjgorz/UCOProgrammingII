#include <iostream>
#include <string>
#include "BinaryNode.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace std;

template <typename T>
void print(T& data)
{
   cout << data << endl;
}

void menu();
void insert_msg();
void delete_msg();

int main()
{
   string input = "";
   bool exit_now = false;
   BinarySearchTree<int> stree;
   while (!exit_now)
   {
      menu();
      getline(cin, input);
      if (input == "i")
      {
         insert_msg();
         getline(cin, input);
         while (input != "q")
         {
            stree.insert(stoi(input));
            stree.print();
            getline(cin, input);
         }
      }
      else if (input == "r")
      {
         delete_msg();
         getline(cin, input);
         while (input != "q")
         {
            stree.remove(stoi(input));
            stree.print();
            getline(cin, input);
         }
      }
      else if (input == "c")
         stree.clear();
      else if (input == "t")
         stree.print();
      else if (input == "h")
         cout << "\nThe height of the binary tree is " << stree.height() << endl;
      else if (input == "s")
         cout << "\nThe size (node count) of the binary tree is " << stree.size() << endl;
      else if (input == "m")
      {
         cout << "\nPre-order traversal: " << endl;
         stree.preorder(print);  //increment is the address of the start of the increment function
      }
      else if (input == "n")
      {
         cout << "\nIn-order traversal: " << endl;
         stree.inorder(print);  //increment is the address of the start of the increment function
      }
      else if (input == "p")
      {
         cout << "\nPost-order traversal: " << endl;
         stree.postorder(print);  //increment is the address of the start of the increment function
      }
      else if (input == "l")
      {
         cout << "\nThe leaf count of the binary tree is " << stree.leaf_count() << endl;
      }
      else if (input == "e")
      {
         cout << "\nCreating a new bst named bst_copy" << endl;

         BinarySearchTree<int> bst_copy;
         insert_msg();
         getline(cin, input);
         while (input != "q")
         {
            bst_copy.insert(stoi(input));
            bst_copy.print();
            getline(cin, input);
         }
         
         bst_copy = stree;
         cout << "\nNow, bst_copy = stree\n";
         bst_copy.print();
      }
      else if (input == "x")
         exit_now = true;
   }
}

void menu()
{
   cout << "\n";
   cout << "========== MENU ==========\n";
   cout << "i. Incremental Insert\n";
   cout << "r. Incremental Remove\n";
   cout << "c. Clear tree\n";
   cout << "t. Print tree\n";
   cout << "h. Print tree height\n";
   cout << "s. Print tree size\n";
   cout << "m. Pre-order traversal\n";
   cout << "n. In-order traversal\n";
   cout << "p. Post-order traversal\n";
   cout << "l. Leaf count\n";
   cout << "e. operator=()\n";
   cout << "x. Exit\n";
   cout << "========== MENU ==========\n";
   cout << "Select an option: ";
}

void insert_msg()
{
   cout << "\nEnter new integer keys to insert.  Enter \"q<Enter>\" to quit.\n\n";
}

void delete_msg()
{
   cout << "\nEnter integer keys to delete.  Enter \"q<Enter>\" to quit.\n\n";
}
