#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
    Queue q;  //q is a new object of Queue, will implicitly call the Queue() constructor to initialize
              //    q will be located in the STACK portion of the virtual address space of the program (no new call)
              //    Node pointers front and rear initialized in the STACK
    cout << "Size of Queue = " << sizeof(Queue) << "\n";  //size of Queue is 16 bytes to account for two Node pointers at 8 bytes each
    cout << "Address of the first byte of q = " << &q << "\n";

    const int SIZE = 5;

    //loop to add 5 total data items to the Queue
    //  utilizes the enQueue() function call to process
    for(int i = 0; i < SIZE; i++)
    {
        q.enQueue(i * 10);  //object q calling the Queue member function enQueue()
                            //  will add data in order of --> 0/10/20/30/40
        q.print();          //print out SLL contents to show progression of data being added
    }

    //loop to delete 5 total data items from the Queue
    //  utilizes deQueue() function call to process
    for(int i = 0; i < SIZE; i++)
    {
        q.deQueue();        //object q calling the Queue member function deQueue()
                            //  will remove the FRONT data member first, order --> 0/10/20/30/40
        q.print();          //print out SLL contents to show progression of data being removed
    }

    q.deQueue();  //should cause exception case, no more data left in the Queue

    return 0;  //activation frame of the main() wiped out, all local variables automatically destroyed

               //q no longer in scope, automatic call to destructor to clear memory reservation in the heap
               //   should cause exception when destructor is implicitly called because all data items were deleted prior to returning main()
}