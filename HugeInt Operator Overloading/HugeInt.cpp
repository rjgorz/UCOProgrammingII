#include <cctype>   //isdigit()
#include <cstring>  //strlen
#include <cmath>

#include "HugeInt.h"
using namespace std;


void HugeInt::compute_size()
{
    cout << "HugeInt::compute_size() called\n";
    size = 0;
    int i = 0;

    //while loop to find index of first non-zero number, indicating where the number begins
    while(number[i] == 0)
        i++;
    //loop through remaining elements and incremet size until capacity is reached
    for(int j = i; j < capacity; j++)
        this->size++;
}

//default constructor, initialize all 0's
HugeInt::HugeInt()
{
    cout << "HugeInt::HugeInt() called\n";

    //memory in the heap to store a huge (long) number
    //note: each digit is treated as a char type which is a subset of int type
    capacity = 30;
    size = 0;
    number = new char[capacity];  //number will be a char*

    //initialize the array in the heap
    for(int i = 0; i < capacity; i++)
        number[i] = 0;
}

//long constructor
//HugeInt(long)
//  e.g. HugeInt(765321)
HugeInt::HugeInt(long value)
{
    cout << "HugeInt::HugeInt(long) called\n";

    //memory in the heap to store a huge (long) number
    //note: each digit is treated as a char type which is a subset of int type
    capacity = 30;
    number = new char[capacity];  //number will be a char*

    //initialize the array in the heap
    for(int i = 0; i < capacity; i++)
        number[i] = 0;
    
    //store the value in the array by extracting each digit
    //value = 765321
    //extract 1 --> index 29, extract 2 --> index 28, extract 3 --> index 27, extract 5 --> index 26, extract 6 --> index 25, extract 7 --> index 24
    long dividend = value;
    int count = 0;

    //while loop to perform extraction
    while(dividend > 0)
    {
        int digit = dividend % 10;
        number[capacity - 1 - count] = digit;
        dividend /= 10;
        count++;
    }

    //set size to the total number of digits extracted from the long value
    size = count;
}

//character array constructor
//"9999999999999999999999999999"
HugeInt::HugeInt(const char* s)
{
    //initialize member variables
    capacity = 30;
    size = 0;
    number = new char[capacity];  //number will be a char*

    //initialize the array in the heap with all zeros
    for(int i = 0; i < capacity; i++)
        number[i] = 0;

    cout << "HugeInt::HugeInt(const char*) called\n";
    string str = s;         //string object = const char* --> overloaded constructor within string class to handle this case
    int len = str.length();

    //extract each digit and store into number array
    for(int i = capacity - 1, j = len - 1; i >= capacity - len; i--, j--)
    {
        char c = str[j] - '0';
        number[i] = c;
    }

    compute_size();
}

//copy constructor
HugeInt::HugeInt(const HugeInt& copy)
{
    cout << "HugeInt::HugeInt(const HugeInt&) called\n";

    //copy all member variables of the passed in object to the calling object
    capacity = copy.capacity;
    size = copy.size;

    //declare a new char array in the heap for the calling object, perform element-wise copy of all digits
    number = new char[capacity];
    for(int i = 0; i < capacity; i++)
        number[i] = copy.number[i];
}

//destructor
HugeInt::~HugeInt()
{
    cout << "HugeInt::~HugeInt() called\n";

    //destructor call will delete the number array associated with each object
    delete number;
}

//operator= overload
HugeInt& HugeInt::operator=(const HugeInt& right)
{
    cout << "HugeInt::operator=() called\n";

    //temporary HugeInt object local to copy the passed in object right
    HugeInt local(right);

    //pointer swap operation to assign the calling object all properties of the passed in object
    char* temp = this->number;
    this->number = local.number;
    local.number = temp;

    //ensure size is also properly assigned
    this->size = right.size;

    //return *this, return type is reference
    return *this;
}

//operator+() overload, index by index addition
HugeInt HugeInt::operator+(const HugeInt& right)
{
    cout << "HugeInt::operator+() called\n";

    //declare result object and variables necessary to perform addition
    HugeInt result;
    int carry = 0;
    
    //addition logic loop
    for(int i = capacity - 1; i >= 0; i--)
    {
        //perform element-wise addition, assign to sum variable
        int sum = right.number[i] + this->number[i] + carry;
        //perform modulo 10 on sum to extract the 1's place digit and assign to result object at current index
        result.number[i] = sum % 10;
        //reassign carry to the overflow when sum > 9
        carry = sum / 10;
    }

    //compute correct size of the result object
    result.compute_size();

    //return the result object
    return result;
}

//operator- overload, index by index subtraction
//  no worry about underflow
HugeInt HugeInt::operator-(const HugeInt& right)
{
    cout << "HugeInt::operator-() called\n";

    //declare result object and variables necessary to perform subtraction
    HugeInt result;
    int temp = 0;
    int carry = 0;
    int len = this->size;  //len variable set to the size of the calling object, allows the loop to iterate the proper number of times
                           //this will not work when a small number is subtracting a larger number (disregarding underflow condition)

    //subtraction logic loop
    for(int i = capacity - 1; i >= capacity - len; i--)
    {
        //assign temp to the current digit of the calling object plus any carry if a borrow occurred in the previous loop
        temp = this->number[i] + carry;

        //condition when the current digit is smaller than the digit being subtracted
        if(temp < right.number[i])
        {
            //borrow value from the next digit up by setting carry to -1 and increase temp by 10
            carry = -1;
            temp += 10;
        }
        //normal case, current digit is large enough to lose the digit being subtracted, no carry needed
        else
            carry = 0;

        //assign result object the final figured value of temp minus the corresponding digit of right
        result.number[i] = temp - right.number[i];
    }

    //compute correct size of the result object
    result.compute_size();

    //return the result object
    return result;
}


//HugeInt n(765321);
//HugeInt m(986);
//HugeInt q = n * m;
//operator* overload, performs long multiplication
HugeInt HugeInt::operator*(const HugeInt& right)
{
    cout << "HugeInt::operator*() called\n";

    //declare result object and variables necessary to perform multiplication
    HugeInt result;
    int carry = 0;
    int shift = -1;

    //multiplication logic loops
    //outer loop to iterate through "right"
    for(int i = capacity - 1; i >= capacity - right.size; i--)
    {
        //utilize temporary "steps" object to store result from each step of the multiplication process
        HugeInt steps;
        //increment shift variable in order to align correctly with the magnitude of the multiplying digit from "right"
        shift++;
        //reset carry to 0 for each iteration in the outer loop
        carry = 0;

        //inner loop to iterate through (*this)
        for(int j = capacity - 1; j >= capacity - this->size - shift; j--)
        {
            //perform multiplication of the current digits stored in product variable
            int product = right.number[i] * this->number[j];
            //extract the 1's place digit taking in any previous carries
            int sum = product % 10 + carry;

            //assign sum (modulo division one final time in case adding carry in the prev step pushed sum > 9) to the current index of the inner loop of steps object
            steps.number[j - shift] = sum % 10;
            //reassign carry for the next iteration of the inner loop
            carry = (product + carry) / 10;

            //special case when a carry is still present after the final iteration of the loop, assign to the next index in steps 
            if(j == capacity - this->size)
                steps.number[j - shift - 1] = carry;
        }

        //add the steps object value to the overall result object 
        result = result + steps;
    }

    //return the overall result object
    return result;
}

//HugeInt n(765321);
//HugeInt m(986);
//HugeInt q = n / m;
//change m to an int/long but do not change n to an int/long
//operator/ overload, performs long division
HugeInt HugeInt::operator/(const HugeInt& right)
{
    cout << "HugeInt::operator/() called\n";

    //declare result object and necessary variables to perform division
    HugeInt result;
    long divisor = 0;
    long dividend = 0;
    int k = 0;

    //loop to convert "right" or divisor into an actual long value
    for(int i = capacity - 1; i >= capacity - right.size; i--)
    {
        divisor += right.number[i] * pow(10, k);
        k++;
    }

    //set the dividend initially to the highest order digit of the calling object
    dividend = this->number[capacity - this->size];

    //division logic loop
    for(int i = capacity - this->size; i < capacity; i++)
    {
        //case where divisor is too large, pull down next digit from dividend
        if(dividend < divisor)
            //result object initialized with all 0's, no need to set current index to 0 in this case
            dividend = (dividend * 10) + this->number[i + 1];

        //case where division is possible
        else
        {
            //assign current index of the result object the resulting value from integer division
            result.number[i] = dividend / divisor;
            //reassign dividend to the remainder of the operation, pull down next digit for next iteration
            dividend = ((dividend % divisor) * 10) + this->number[i + 1];
        }
    }

    //computes correct size of result object
    result.compute_size();

    //return result object
    return result;
}

//operator% overload, performs long modulo division
HugeInt HugeInt::operator%(const HugeInt& right)
{
    cout << "HugeInt::operator%() called\n";

    //declare variables necessary to perform division
    long divisor = 0;
    long dividend = 0;
    int k = 0;

    //loop to convert "right" or divisor into an actual long value
    for(int i = capacity - 1; i >= capacity - right.size; i--)
    {
        divisor += right.number[i] * pow(10, k);
        k++;
    }

    //set the dividend initially to the highest order digit of the calling object
    dividend = this->number[capacity - this->size];

    //division logic loop
    for(int i = capacity - this->size; i < capacity; i++)
    {
        //case where divisor is too large, pull down next digit from dividend
        if(dividend < divisor)
            dividend = (dividend * 10) + this->number[i + 1];
            
        //case where division is possible
        else
        {
            //final case when final digit is pulled down to obtain overall remainder, assign to dividend
            if(i == capacity - 1)
                dividend %= divisor;

            //intermediate cases, perform modulo division to store remainder, pull down next digit for next iteration
            else
                dividend = ((dividend % divisor) * 10) + this->number[i + 1];
        }
    }

    //create a new HugeInt object with the overall remainder results using the final dividend value
    HugeInt remainder(dividend);

    //returns the remainder object
    return remainder;
}

//operator++ overload (pre-increment)
HugeInt& HugeInt::operator++()
{
    cout << "HugeInt::operator++() called\n";

    //initialize carry to 1 to perform the incrementation
    int carry = 1;
    //initialize for while loop, starting at capacity - 1 (index 29)
    int i = capacity - 1;

    //loop until the incrementation no longer produces a carry to the next highest digit (typically with repeating 9's)
    while(carry == 1)
    {
        int sum = this->number[i] + carry;
        this->number[i] = sum % 10;
        carry = sum / 10;
        i--;
    }

    //compute correct size of the calling object in case it increased due to incrementation
    this->compute_size();

    //return *this, return type is reference
    return *this;
}

//operator++ overload (post increment)
HugeInt HugeInt::operator++(int)
{
    cout << "HugeInt::operator++(int) called\n";

    //declare temp object, uses copy constructor to copy the calling object
    HugeInt temp(*this);
    //initialize carry to 1 to perform the incrementation
    int carry = 1;
    //initialize for while loop, starting at capacity - 1 (index 29)
    int i = capacity - 1;

    //loop until the incrementation no longer produces a carry to the next highest digit (typically with repeating 9's)
    while(carry == 1)
    {
        int sum = this->number[i] + carry;
        this->number[i] = sum % 10;
        carry = sum / 10;
        i--;
    }
    
    //compute correct size of the calling object in case it increased due to incrementation
    this->compute_size();
    
    //return unchanged temp object for proper assignment
    return temp;
}

//operator<= overload, compares two numbers
bool HugeInt::operator<=(const HugeInt& right)
{
    cout << "HugeInt::operator<=() called" << "\n";

    //loop through each digit of both objects
    for(int i = 0; i < capacity - 1; i++)
    {
        //returns true at the first instance that the left's digit is smaller than the right's
        if(this->number[i] < right.number[i])
            return true;
        //returns false at the first instance that the left's digit is larger than the right's
        else if(this->number[i] > right.number[i])
            return false;
    }
    //if both numbers are equal, this statement will be reached that returns true
    return true;
}

//operator[] overload, retrieves value at specified index
char& HugeInt::operator[](int index)
{
    cout << "HugeInt::operator[](int) called\n";

    //error case for attempting to access an element that is out of bounds
    if(index >= this->capacity || index < 0)
    {
        cout << "Array index out of bound, exiting.\n";
        exit(0);
    }

    //return the element of the desired passed in index
    return this->number[index];
}

//operator long double overload, converts the object's number into type long double
HugeInt::operator long double()
{
    cout << "HugeInt::operator long double() called\n";

    int k = 0;
    long double result = 0;

    //loops through the number array to convert each digit and add to the resultint long double variable
    for(int i = capacity - 1; i >= capacity - this->size; i--)
    {
        result += this->number[i] * pow(10, k);
        k++;
    }

    //returns variable result that is of type long double
    return result;
}

//operator<< overload, allows printing of the number stored in the object
ostream& operator<<(ostream& out, const HugeInt& obj)
{
    cout << "HugeInt::operator<<() called\n";

    //print out each non-leading zero digit stored in the number array of the object
    for(int i = obj.capacity - obj.size; i < obj.capacity; i++)
        out << (int)obj.number[i];

    //case size is 0 and the object's number array holds all 0's, print out one 0 instead of nothing
    if(obj.size == 0)
        out << (int)obj.number[obj.capacity - 1];
    
    out << "\n";

    //returns out in case of cascading call
    return out;
}


istream& operator>>(istream& in, HugeInt& obj)
{
    cout << "HugeInt::operator>>() called\n";

    //initialize a temp input char array and prompt for input
    char input[30];
    cout << "Enter an integer: ";
    in >> input;

    //use a temp string object to determine the size of the input number
    string str = input;
    int len = str.length();
    int i, j;

    //loop through to store the input number into the array
    for(i = obj.capacity - 1, j = len - 1; i >= obj.capacity - len; i--, j--)
        obj.number[i] = input[j] - '0';

    //loop through the remaining elements of the array and assign 0's in case it is overwriting an old number
    for(i = obj.capacity - len - 1; i >= 0; i--)
        obj.number[i] = 0;

    //compute correct size of the object
    obj.compute_size();

    //returns in in case of cascading call
    return in;
}