#include <iostream>
#include "MyIntArr.h"

using namespace std;

int main()
{
    //declare testing objects
    MyIntArr a1;
    MyIntArr a2(3);
    MyIntArr b;
    
    //tests operatir<< overloading to print an obj to the console
    cout << "obj a1 : " << a1 << "\n";
    cout << "obj a2 : " << a2 << "\n";

    //testing operator+ overloading to add two objects of differing sizes (larger array + smaller array)
    b = a1 + a2;
    cout << "obj b after a1+a2 : " << b << "\n";

    //testing operator+ overloading to add two objects of differing sizes (smaller array + larger array)
    b = a2 + a1;
    cout << "obj b after a2+a1 : " << b << "\n";

    //testing operator- overloading to subtract two objects of differing sizes  (larger array - smaller array)
    b = a1 - a2;
    cout << "obj b after a1-a2 : " << b << "\n";

    //testing operator- overloading to subtract two objects of differing sizes  (smaller array - larger array)
    b = a2 - a1;
    cout << "obj b after a2-a1 : " << b << "\n";

    //testing operator++ (post-increment) to assign a1++ to b (b = a1, then a1++, they should end up being different)
    cout << "obj a1 before b=a1++ :" << a1 << "\n";
    b = a1++;
    cout << "obj a1 after b=a1++ : " << a1 << "\n";
    cout << "obj b after b=a1++ : " << b << "\n";

    //testing operator++ (pre-increment) to assign ++a2 to b (a2++ then b = a2, they should end up being the same)
    cout << "obj a2 before b=++a2 :" << a2 << "\n";
    b = ++a2;
    cout << "obj a2 after b=++a2 : " << a2 << "\n";
    cout << "obj b after b=++a2 : " << b << "\n";

    //testing operator>> to take in user input for elements of new obj c
    MyIntArr c(3);
    cout << "obj c before cin : " << c << "\n";
    cin >> c;
    cout << "obj c after cin : " << c << "\n";
    
    //testing copy constructor
    MyIntArr d = c;
    cout << "obj d after assignment as c : " << d << "\n";

    //testing operator[] to print obj d element by element
    cout << "printing obj d using d[i] : ";
    for(int i = 0; i < d.get_size(); i++)
        cout << d[i] << " ";
    cout << "\n";
    
    return 0;
}

