/*
queue.h: the header file that contains
    1. definition of Queue
    2. only function prototypes, not definitions
    3. file name is .h (header file) becaues there is no code for the bodies of member functions
    4. member function definitions will be in a separate file, each .cpp files
    5. the contract between main() and Stack type
        a. specifically, main() does not need to know how the member functions are implemented, simply call them
    6. the header file is the specification of the Stack type
*/

//class:  aggregate data type
//        data member, member variables: data
//         *member* functions: Queue(), ~Queue(), enqueue(), dequeue()
//definition/declaration of Queue without the complete code for member functions
class Queue
{
    private:  //information hiding from main(), the outside of class Queue
        int capacity;
        int* data;
        int front;
        int rear;
        int size;
        
    public:
    //Stack(): constructor, special member function of Stack
    //         1. no return type
    //         2. function name: must be exactly the same as the struct type, Stack in this case
    //         3. purpose: initialize member variables after an object (variable of this data type) is created
    Queue();

    //~Stack(): destructor, special member function of Stack
    //          1. no return type
    //          2. function name: ~ must precede the name, which must be exactly the same as the struct type, Stack in this case
    //          3. purpose: deallocate memory reserved in the heap: garbage collection
    ~Queue();

    //enqueue(): insert data on the top of the Stack
    //        1. data must be passed to push() to create an intem
    //        2. return type: typically void, but okay to return value if desired to define it that way
    void enqueue(int);

    //dequeue(): removes data from the top of the Stack
    //       1. data must NOT be passed into pop()
    //       2. return type: typically void, but okay to return value if desired to define it that way
    void dequeue();

    //only for debugging purpose
    void print();
};
