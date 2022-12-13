/*  10/25-10/27 Operator Overloading
	- define MyIntArr that has a point to an int array in the heap
	- if a class has a pointer, you must provide "the Big-Three":
		- copy constructor
		- operator=(): assignment operator overloading
		- (virtual) destructor
*/

#ifndef MYINTARR_H
#define MYINTARR_H

#include <iostream>

//namespace is required for ostream and istream
// Otherwise, error: 'ostream' does not name a type
using namespace std;

class MyIntArr
{
	private:
		int* pArr;  //pointer to an array of integers in the heap
		int  size;
		void create(int);

	public:
		MyIntArr();  				//default constructor
		MyIntArr(int);				//arg constructor

		/*
			copy constructor
				a. no return, same name as the class, initialize data members
				b. parameter variable: must be const class_name&
					- const: indicates a constant variable, cannot modify the value of the variable
					- &: indicates a reference variable, faster than pass by value, doesn't need to create a local variable (more memory allocation) to copy
				c. usage in main():
					MyIntArr a(10);
					MyIntArr b(a);		//calls the copy constructor, 'a' will be received as const &
					MyIntArr c = b;		//also calls the copy constructor, c is being created and initialized using b
		*/
		MyIntArr(const MyIntArr&);

		virtual ~MyIntArr();  //destructor: if a class has a pointer data member, provide the destructor, it will use the heap memory through the pointer

		/*
			operator=(): assignment operator overloading
				a. function name: operator=
				b. parameter variable: must be the same as that of the copy constructor const class_name&
				c. return type: class_name&
					- why reference?
						- if return type is class_name without reference, you are creating a variable/value copy
						- if return type is class_name&, there is no creation of a variable
				d. usage in main():
					MyIntArr a(10);
					MyIntArr b(5);
					b = a;  //calls operator=(), b already exists and are not creating b here
				f. what is behind the scene of b = a?
					- the compiler changes the code b = a; to b.operator=(a);
						- b is the object that calls the member function operator=() with 'a' as its argument
							- this job of the compiler makes code of the user (main()) simple
		*/
	    MyIntArr& operator=(const MyIntArr&);
		//MyIntArr operator=(const MyIntArr&);  //not used without reference return type, does not align with standard library

		/*
			binary operator+ overloading
				a. function name: operator+()
				b. parameter variables: class_name& or const class_name&
				c. return type: always class_name without reference
				d. usage:
					MyIntArr a(5);
					MyIntArr b(5);
					MyIntArr c = a + b;  //calls a.operator+(b) first, then copy constructor
						The result of a + b, the value of a or b? 
							Neither, will be completely different from both because of the meaning of + we will impose (see f.)
							Then we will have to create a new MyIntArr object, which means the return type must be non-reference type
							You can use & for the variable that already exists --> the variable must occupy memory before being referenced
								& cannot be used with a const value (e.g. &15, &"abc")
				f. meaning of +: element-wise addition of two arrays of two two MyIntArr objects
		*/
		MyIntArr operator+(const MyIntArr&);

		/*
			binary operator- overloading
				a. function name: operator-()
				b. parameter variable: class_name& or const class_name&
				c. return type: always class_name without reference
				d. usage:
					MyIntArr a(5)
					MyIntArr b(5)
					MyIntArr c;
					c = a - b;  //calls a.operator-(b) returning an object of MyIntArr, then c.operator(resulting MyIntArr)
		*/
		MyIntArr operator-(const MyIntArr&);

		/*
			index operator overloading
				a. function name: operator[]
				b. parameter variable: must be an integer that indicates an index of an array
				c. return type: depends on the type of the array
					- int array: int& or int
					- char array: char& or char
					- double array: double& or double
					- when to use &?
				d. usage:
					MyIntArr a(5);
					a[4] = 3;		//a.operator[](4) = 3, changing the value of the element at index 4
														--> need to know the address of that element
														--> operator[](int) must return int&
					cout << a[2];	//a.operator[](2), retrieving the value of the element at index 2, but not changing it
														--> operator[](int) does not have to return int&, just int
					which return value, with & or without?
						it depends on the desired outcome
		*/
		int& operator[](int);
		//int operator[](int);
		
		/*
			pre-increment operator overloading
				a. function name: operator++()
				b. parameter varaibles: none
				c. return type: MyIntArr&
				d. usage:
					MyIntArr a(5);		{10, 20, 30, 40, 50}
					a++;				{11, 21, 31, 41, 51} --> element-wise increment

					MyIntArr b = ++a;  	//increment a then assign a to b
											a.operator++() which returns a, the calling object
											pre-increment must return a, which exists already
											return type must be MyIntArr&
											after executing, b holds {12, 22, 32, 42, 52}
		*/
		MyIntArr& operator++();

		/*
			post-increment operator overloading
				a. function name: operator++()
				b. parameter variables: a dummy parameter variable, int (this is how to distinguish between pre-increment)
				c. return type: class_name without reference
				d. usage:
					MyIntArr a(5);		//{10, 20, 30, 40, 50}
					MyIntArr b = a++;	//a must be assigned to b, THEN increment a
											b = a first --> b.operator=(a);
											a++ next --> a.operator++(int);
											end result: a = {11, 21, 31, 41, 51} and b = {10, 20, 30, 40, 50}
											a == b? NO
										//What if operator++(int) returns MyIntArr&?
											b holds {11, 21, 31, 41, 51} --> error, not what was intended
		*/
		MyIntArr operator++(int);


		int get_size() const;

		//A friend function can access directly private members of the class that the function is a friend with
		//A friend function must be declared in the class definition	
		//It can defined anywhere(before being used) as a regular function
		/*
			stream insertion operator
				MyIntArr a(5);
				cout << a;
		*/
		friend ostream& operator<<(ostream&, const MyIntArr&);
		friend istream& operator>>(istream &, MyIntArr&);
		//friend MyIntArr operator++(const MyIntArr&); NOT USED

};

#endif