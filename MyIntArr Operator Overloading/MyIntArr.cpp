#include <iostream>
#include <iomanip>
#include "MyIntArr.h"

using namespace std;

//default constructor
MyIntArr::MyIntArr()
{
    cout << "MyIntArr() called\n";
    size = 5;
    pArr = new int[size];
    for(int i = 0; i < size; i++)
        *(pArr + i) = rand() % 100;  //same as pArr[i] = -1;
}

//argument constructor, new object with specified size
MyIntArr::MyIntArr(int n)
{
    cout << "MyIntArr(int) called\n";
    size = n;
    pArr = new int[size];
    for(int i = 0; i < size; i++)
        *(pArr + i) = rand() % 100;  //same as pArr[i] = -1;
}

//copy constructor, create new object based on an existing object
MyIntArr::MyIntArr(const MyIntArr& right)
{
    cout << "MyIntArr(const MyIntArr&) called\n";
    size = right.size;
    pArr = new int[size];
    for(int i = 0; i < size; i++)
        *(pArr + i) = right.pArr[i];
}

//destructor function
MyIntArr::~MyIntArr()
{
    cout << "~MyIntArr() called\n";
    delete [] pArr;
}

/*use a pointer swapping technique
    1. create a local MyIntArr object using the copy constructor to create an identical copy of right
    2. swap the pointers of local and the calling object (*this) that is calling this function now
    3. update the size of the calling object
        - if the class has other data members, update them as well
    4. return *this for cascaded assignments

    return type muse be a reference because we are returning an object that existed before the function call
    return statement always with *this
*/
MyIntArr& MyIntArr::operator=(const MyIntArr& right)
{
    cout << "operator=(const MyIntArr&) called\n";

    MyIntArr local(right);  //local object creation

    //pointer swap operation
    int* temp = this->pArr;
    this->pArr = local.pArr;
    local.pArr = temp;

    size = right.size;  //update size (and other members)

    //returns updated calling object
    return *this;  //the object named local is out of scope because it is local to the function stack
                   //local will call destructor here, deleting the memory originally used by the calling object
}

/*
    binary addition of two objects of MyIntArr type
    1. function name: operator+
    2. if the function is a member, then only right operand is passed to this function
        - only one argument in the funciton call/definition
    3. return type: MyIntArr without reference, the result is creating a new object, not the left or right operand
*/
MyIntArr MyIntArr::operator+(const MyIntArr& a)
{
    cout << "operator+(const MyIntArr&) called\n";

    //create and set length of result array to the longer of the calling object and the passed in object
    int length = this->size < a.size ? a.size : this->size;
    MyIntArr result(length);

    //loop to perform element-wise addition
    for(int i = 0; i < length; i++)
    {
        //condition when calling object size is smaller, assigns remaining elements to the passed in object's elements as if they were added to 0
        if(i > (this->size) - 1)
        {
            for(int k = i; k < a.size; k++)
                result.pArr[k] = a.pArr[k];
            break;

        //condition when passed in object size is smaller, assigns remaining elements to the calling object's elements as if they were adding onto 0
        } else if(i > (a.size) - 1)
        {
            for(int k = i; k < this->size; k++)
                result.pArr[k] = this->pArr[k];
            break;
        }

        //normal condition, performs element-wise addition of the corresponding elements of the calling and passed in objects and assigns to result
        result.pArr[i] = this->pArr[i] + a.pArr[i];
    }

    return result;
}


MyIntArr MyIntArr::operator-(const MyIntArr& a)
{
    cout << "operator-(const MyIntArr&) called\n";

    //create and set length of result array to the longer of the calling object and the passed in object
    int length = this->size < a.size ? a.size : this->size;
    MyIntArr result(length);

    //loop to perform element-wise subtraction
    for(int i = 0; i < length; i++)
    {
        //condition when calling object size is smaller, assigns remaining elements to the passed in object's elements as if they were subtracted from 0
        if(i > (this->size) - 1)
        {
            for(int k = i; k < a.size; k++)
                result.pArr[k] = -a.pArr[k];
            break;

        //condition when passed in object size is smaller, assigns remaining result elements to the calling object's elements as if subtracting 0 
        } else if(i > (a.size) - 1)
        {
            for(int k = i; k < this->size; k++)
                result.pArr[k] = this->pArr[k];
            break;
        }

        //normal condition, performs element-wise addition of the corresponding elements of the calling and passed in objects and assigns to result
        result.pArr[i] = this->pArr[i] - a.pArr[i];
    }

    return result;
}

//overload to access individual elements of an object using obj[i] notation
int& MyIntArr::operator[](int index)
{
    cout << "operator[](int) called\n";

    //error case for attempting to access an element that is out of bounds
    if(index >= this->size || index < 0)
    {
        cout << "Array index out of bound, exiting.\n";
        exit(0);
    }

    //return the element of the desired passed in index
    return this->pArr[index];
}

//pre-increment
MyIntArr& MyIntArr::operator++()
{
    cout << "operator++() called\n";

    //element-wise incrementation
    for(int i = 0; i < this->size; i++)
        this->pArr[i]++;

    //returns the calling object back with incremented elements
    return *this;
}


//post-increment
MyIntArr MyIntArr::operator++(int)
{
    cout << "operator++(int) called\n";

    //temp object to hold values
    MyIntArr temp(this->size);

    //loop through and assign temp object incremented calling object values
    for(int i = 0; i < this->size; i++)
        temp.pArr[i] = this->pArr[i]++;

    //return temp back to replace the calling object
    return temp;
}

//simple get_size function, returns current size of the array for the calling object
int MyIntArr::get_size() const
{
    return this->size;
}


/*
    stream insertion operator
    0. it cannot be a direct member of a defined class
        - in order for an operator overloading function to be a member of a class you define, the type of the first parameter variable must be of the class that you define
            - this cannot be the case because this function MUST have ostream& as its first parameter variable
    1. it can be a friend or non-friend of a defined class
    2. function name: operator<<
    3. parameter variables: 2
        - first paramater variable: ostream&
        - second parameter variable: const class_name&
    4. return type: always ostream&, the first parameter variable
*/
ostream& operator<<(ostream& out, const MyIntArr& a)
{
    cout << "operator<<() called\n";

    for(int i = 0; i < a.size; i++)  //size is a private member, but directly accessed using the dot operator as it is a friend function
        out << setw(3) << a.pArr[i] << " ";
    out << "\n";

    return out;
}

/*
    stream extraction operator
    0. it cannot be a direct member of a defined class
        - in order for an operator overloading function to be a member of a class you define, the type of the first parameter variable must be of the class that you define
            - this cannot be the case because this function MUST have istream& as its first parameter variable
    1. it can be a friend or non-friend of a defined class
    2. function name: operator>>
    3. parameter variables: 2
        - first paramater variable: always istream&
        - second parameter variable: class_name&
    4. return type: always istream&, the first parameter variable
*/
istream& operator>>(istream & in, MyIntArr& a)
{
    cout << "operator>>() called\n";

    cout << "Enter " << a.size << " integers: ";  //size is a private member, but directly accessed using the dot operator as it is a friend function
    for(int i = 0; i < a.size; i++)
        in >> a.pArr[i];

    return in;
}

/*
MyIntArr operator++(const MyIntArr&)
{
    NOT USED
}
*/