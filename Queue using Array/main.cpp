#include <iostream>
#include "queue.h"  //do not add stack.cpp, only include the header file (.h)

using namespace std;

int main()
{
  Queue q;  //s is an object of Stack, automatically/implicitly calls the constructor
            //undefined reference to `Stack::Stack()': constructor call, but the definition is in a different .cpp file
              //main() has no code reference to the constructor definition
            //s is located in the STACK of the virtual address space of the program
              //why no heap? no "new" keyword calls
  cout << sizeof(Queue) << "\n";
  cout << sizeof(q) << "\n";
  cout << "address of the first byte of q = " << &q << "\n";

  const int SIZE = 5;

  for(int i = 0; i < SIZE; i++)
  {
    q.enqueue(i * 10);  //object.member_function(), first enqueue -> 0/10/20/30/40 -> last enqueue
    q.print();
  }

  for(int i = 0; i < SIZE; i++)
  {
    q.dequeue();  //object.member_function(), first dequeue -> 40/30/20/10/0 -> last dequeue
    q.print();
  }

  //exception because no data in the stack
  q.dequeue();

  return 0;  //activation frame of the main: wiped out, all local variables automatically destroyed
            
            //s is now out of scope, automatic destructor call  
}

/*
  - compiling g++ -c ./main.cpp creates "main.o": binary file that must be linked to other binary files
    together (link main.o and stack.o) to make one a.exe executable
  - -c option is compile only command
*/