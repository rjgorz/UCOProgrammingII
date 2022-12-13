
#include <iostream>
#include "DHeap.h"

using namespace std;


DHeap::DHeap() {
    double not_used = 0;
    elements.push_back(not_used);
}

DHeap::~DHeap() {
}

void DHeap::insert(double new_key) {

    elements.push_back(new_key);  //index 0 is always occupied by the dummy data not_used
                                  //first key inserted will be at index 1 automatically
    //fix the heap
    percolateUp();
}

void DHeap::percolateUp() {

    int cur_idx = elements.size() - 1;  //will always be one more than the actual keys due to the dummy data in index 0
                                        //where the new key is located or supposed to be at
    if(cur_idx == 1) return;  //only one key, no modifications needed

    double new_key = elements[cur_idx];

    // demote parents that are larger than the new element
    bool more = true;
    do {
    	double parent_key = elements[cur_idx / 2];
	    if(new_key < parent_key && cur_idx != 1) { //cur_idx: not yet reach root
        	elements[cur_idx] = parent_key;
            cur_idx /= 2;
	    }
	    else {
		    more = false;
	    }
    } while(more);

    // store the new element into the vacant slot
    elements[cur_idx] = new_key;
}

double DHeap::top() const {
    return elements[1];
}

int DHeap::size() const {
	return elements.size() - 1; // note: elements[0] is not used
}

void DHeap::removeMin() {
    // remove the last element
        //get the last key first
    int last_idx = elements.size() - 1;
    double last_key = elements[last_idx];

    //replace the root key with the last key
    elements[1] = last_key;
    //remove the last key
    elements.pop_back();

    if(last_idx > 1) {  //at least two keys in the minHeap
        percolateDown();
    }
}

void DHeap::percolateDown() {
    double root_key = elements[1];
    int last_idx = elements.size() - 1;
    if(last_idx == 1) return;

    // promote children of removed rootKey while they are smaller than last
    int cur_idx = 1;
    bool more = true;
    while (more) {
        int leftC_idx = cur_idx * 2;
        if (leftC_idx <= last_idx) {
            double smaller_key = elements[leftC_idx];
            int smallerC_idx = leftC_idx;
            int rightC_idx = cur_idx * 2 + 1;

            if (rightC_idx <= last_idx && elements[rightC_idx] < elements[leftC_idx]) { //condition where the right child is smaller
                smallerC_idx = rightC_idx;
                smaller_key = elements[smallerC_idx];
            }

            // check if smaller child is smaller than root key
            if (smaller_key < root_key) {
                // promote child
                elements[cur_idx] = smaller_key;
                cur_idx = smallerC_idx;
            } else {
                // rootKey is larger than both children
                more = false;
            }
        } 
	    else {
            // no children
            more = false;
        }
   }

    // store rootKey element in vacant slot
    elements[cur_idx] = root_key;
}

void DHeap::print()
{
    for(int i = 1; i <= this->size(); i++)  //print out full heap array
    {
        cout << elements[i] << " ";
    }
    cout << "\n";
}