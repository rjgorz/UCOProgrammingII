/*
queue.h: header file containing:
    definition of Queue and Node
    member function prototypes
    member variables
*/

//Node class definition
class Node
{
    private:
        //member variables for Node
        int data;
        Node* next;

    public:
        //Node constructor, initializes member variables when an object is created
        Node();
        //Node destructor, deletes allocated memory in the heap that Node created
        ~Node();

        //Node setter functions, allows access to modify private member variables 
        void setNext(Node*);
        void setData(int);

        //Node getter functions, allows access to read current value of private member variables
        Node* getNext();
        int getData();
};

//Queue class definition
//  First In First Out behavior
class Queue
{
    private:
        //member variables for Queue
        //  Node pointer front: designates the front item in the queue
        //  Node pointer rear: designates the rear item in the queue
        Node* front;
        Node* rear;

    public:
        
        //Queue constructor
        //  1. initializes member variables when an object is created
        //  2. no return type
        //  3. name must match class name
        Queue();

        //Queue destructor
        //  1. deletes allocated memory in the heap that Queue created
        //  2. no return type
        //  3. name must match class name with ~ preceding the name
        ~Queue();

        //function prototype enQueue()
        //  1. adds new data to the REAR of the queue
        //  2. data must be passed into enqueue() to create a new item
        //  3. return type void
        void enQueue(int);

        //function prototype deQueue()
        //  1. removes data from the FRONT of the queue
        //  2. data must NOT be passed into dequeue()
        //  3. return type void
        void deQueue();

        //function prototype print()
        //  for debugging purposes only
        //  prints current contents of SLL
        void print();
};