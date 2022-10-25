/*
    1. define the bodies of the member functions within Queue
    2. known only to the Queue data type, not to the main
*/

// 1. include Queue.h with "": you are the one who added, not part of the standard library
#include "queue.h"
#include <iostream>
#include <iomanip>

using namespace std;

// :: --> scope resolution operator
// purpose: gives the scope to a function or varialbe (ios::in for example)
//
//this: a. keyword, in general, first byte of an object on which the member function is called
//      b. this is a hidden parameter variable of each member function
Queue::Queue()
{
    cout << "Queue::Queue()\n";
    cout << "\t" << this << "\n";
    capacity = 30;
    size = 0;
    front = 0;
    rear = capacity;
    data = new int[capacity];

    for(int i = 0; i < capacity; i++)
        data[i] = -1;
}

Queue::~Queue()  //deallocate dynamic memory in the heap that is reserved by the object
{                //the SLL is located in the heap, must be deleted by the destructor
    cout << "Queue::~Queue()\n";
    cout << "\t" << this << "\n";

    delete [] data;
}

void Queue::enqueue(int data)
{
    cout << "Queue::enqueue(" << data << ")\n";
    cout << "\t" << this << "\n"; //in the main(), s.enqueue(i * 10), s is the object, this is the address of s

    if(size == capacity)
    {
        cout << "\tQueue Full\n";
        return;
    }
    
    //Ternary operator: A ? B : C
    // 1. number of operands: A, B, C
    // 2. A must be an expression whose value is either true or false --> if condition
    rear = (rear == capacity) ? 0 : (rear + 1);
    this->data[rear] = data;
    size++;

    //rear++: post-increment, rear = rear + 1;
    //   x = rear++; --> x = rear, then rear++

/*
    rear++;
    if(rear == capacity)
        rear = 0;
*/
}

void Queue::dequeue()  //address of the object that calls dequeue() as this, injected by the compiler
{
    cout << "Queue::dequeue()\n";
    cout << "\t" << this << "\n";

    if(size == 0)
    {
        cout << "\tQueue Empty\n";
        return;
    }

    //with circular Queue, no need to remove any data
    front = (front == capacity) ? 0 : (front + 1);
/*
    front++;
    if(front == capacity)
        front = 0;
*/
    size--;
}

void Queue::print()
{

    cout << "Queue::print()\n";
    cout << "\t" << this << "\n";

    if(size == 0)
    {
        cout << "\tQueue Empty\n";
        return;
    }

    int k = front;

    for(int i = 0; i < size; i++)
    {

        k = (k >= capacity) ? (0 + (k - capacity)) : (front + i);
/*
        int k = front + i;
        if(k >= capacity)
            k = 0 + (k - capacity);  //***convert to ternary operator***
*/
        cout << setw(4) << data[k];
    }
    cout << "\n";
}