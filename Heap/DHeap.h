
/* This file Implements of a Min Heap for 'double' type elements
   by using vector
*/
#ifndef D_HEAP_H
#define	D_HEAP_H

#include <vector>
using namespace std;

class DHeap {
private:
    vector<double> elements;    //instantiation of a template class vector<T>
                                //elements.size() is 0
                                //use push_back or pop_back to insert to and delete from the vector
                                //vector is fundamentally a Stack (LIFO)
                                //e.g., elements.push_back(10)  -->  10 goes to the index 0
                                //      elements.push_back(20)  -->  20 goes to the index 1
                                //      elements.pop_back()     -->  20 is removed
    
public:
    DHeap();
    ~DHeap();
    void   insert(double e); // adds a new element to this heap
    double top() const;	     // gets the min element in the heap without removal
    void   removeMin();      // removes the min element from the heap
    int    size() const;     // returns the # of elements in the heap
    void   print();
    
private: // utility functions called by insert and removeMin

    void   percolateDown();
    void   percolateUp();
};

#endif	
