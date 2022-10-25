/*
queue.cpp: implementation file for queue.h
    1. define the bodies of the member functions within Queue
    2. known only to the Queue data type, not the main()
*/

#include <iostream>
#include <iomanip>
#include "queue.h"

using namespace std;

//Node constructor definition
//  initialize member variables upon object creation
Node::Node()
{
    cout << "Node::Node()\n";
    cout << "\t" << this << "\n";  //displays the address of the first byte for the object the member function is called
    
    //initialize data to zero and set Node pointer next to nullptr
    data = 0;
    next = nullptr;
}

//Node destructor definition
Node::~Node()
{
    cout << "Node::Node()\n";
    cout << "\t" << this << "\n";  //display address of first byte for the object the member function is called

    //empty function, Node does not utilize the heap
}

//setNext() function definition
//  allows modification of the next pointer within Node
//  cannot be accessed directly as the variable is set to private
void Node::setNext(Node* addr)
{
    next = addr;
}

//setNext() function definition
//  allows modification of the data variable within Node
//  cannot be accessed directly as the variable is set to private
void Node::setData(int num)
{
    data = num;
}

//getNext() function definition
//  returns current value of the next pointer
Node* Node::getNext()
{
    return next;
}

//getData() function definition
//  returns current value of the data variable
int Node::getData()
{
    return data;
}

//Queue constructor
//  initialize member variables upon object creation
Queue::Queue()
{
    cout << "Queue::Queue()\n";
    cout << "\t" << this << "\n";  //display address of first byte for the object the member function is called

    //initialize both Node pointers to nullptr, to be updated upon creating data items
    front = nullptr;
    rear = nullptr;
}

//Queue destructor
//  deallocates memory for objects created in the heap by Queue
Queue::~Queue()
{
    cout << "Queue::~Queue()\n";
    cout << "\t" << this << "\n";  //display address of first byte for the object the member function is called

    //exception handler when front == nullptr, there are no nodes left to delete
    //  will cause segmentation fault (attempting to access memory outside of program allocated memory)
    if(front == nullptr)
    {
        cout << "There are no Nodes left to deallocate!\n";
        return;  //exits the function without executing the deletion code
    }

    //while loop to delete items in the queue from front to rear
    //  terminates when front == nullptr, meaning there are no nodes left to delete
    while(front != nullptr)
    {
        Node* temp = front;     //assign temp Node pointer to the front data item
        front = front->getNext();    //reassign front to the next data item in the queue
                                //  utilized ->: front is a pointer pointing to an aggregate
                                //               data type, must access with arrow notation
        delete temp;            //delete the Node now that front has been reassigned properly (FIFO)
    }
}

//enQueue() function definition
//  creates a new Node at the rear of the Queue
void Queue::enQueue(int data)
{
    cout << "Queue::enQueue(" << data << ")\n";
    cout << "\t" << this << "\n"; //display address of first byte for the object the member function is called

    Node* temp = new Node;  //temp Node pointer to assign the address of the new Node allocated in the heap

    temp->setData(data);  //assign passed in data to the Node's data through arrow notation: pointer to an aggregate data type

    //case for first Node into empty Queue
    if(rear == nullptr)
    {
        front = rear = temp;    //set both front and rear to temp (address of new node)
        return;         //return from the function, do not execute the remaining code
    }

    //case for any added Nodes to the rear of an occupied Queue
    rear->setNext(temp);  //link current rear Node to new rear Node through arrow notation: pointer to an aggregate data type
    rear = temp;        //reassign rear to the newly added Node
}

//deQueue() function definition
//  removes the Node in the FRONT of the Queue (First In First Out, FIFO)
void Queue::deQueue()
{
    cout << "Queue::deQueue()\n";
    cout << "\t" << this << "\n"; //display address of first byte for the object the member function is called

    //case when there are no remaining Nodes to be deleted
    //  executing deQueue() with no remaining Nodes will cause a segmentation fault (attempting to access memory outside program memory)
    if(front == nullptr)
    {
        cout << "There is no Node left to be deleted.\n";
        rear = nullptr;
        return;     //return from the function without executing the remaining deQueue() code, prevents segmentation fault
    }

    Node* temp = front;     //temp Node pointer set to the front to perform proper deletion
    front = front->getNext();    //assign front to the next Node in the Queue to free up current front for deletion
    delete temp;            //delete temp now that front has been properly reassigned to the next Node (FIFO)

    
}

//pring() function definition
//  used to print SLL contents for debugging purposes
void Queue::print()
{
    cout << "Queue::print()\n";
    cout << "\t" << this << "\n";  //display address of first byte for the object the member function is called

    //case when there are no more remaining Nodes in the Queue to print
    if(front == nullptr)
    {
        cout << "There is no data in the Queue to print.\n";
        return;     //return from the function without executing the remaining print() code
    }

    Node* temp = front;         //temp Node pointer set to the front to navigate through the SLL
    while(temp != nullptr)      //navigates through the SLL and prints out the contained data until nullptr is hit after the rear is printed
    {
        cout << setw(4) << temp->getData();
        temp = temp->getNext();      //prints out current Node's data and navigates to the next Node in the Queue using the temp Node pointer
    }
    cout << "\n";
}