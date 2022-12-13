#include <cstdlib>
#include <iostream>
#include "DHeap.h"

using namespace std;


int main(int argc, char** argv) {
    
    DHeap h;
    //make a for loop to test insertion
    int num;
    cout << "How many data items would you like to input? ";
    cin >> num;

    double input;
    while(num > 0)
    {
        cout << "Enter a number to insert to the Heap: ";
        cin >> input;
        h.insert(input);
        h.print();
        num--;
    }

    //test removeMin and make the heap empty
    double value;
    int idx = h.size();   
    while (idx > 0) {
        value = h.top();
        h.removeMin();
        cout << "\n" << value << " removed." << endl;
        cout << "Current Heap:\n";
        h.print();
        idx--;
    }

    return 0;
}

