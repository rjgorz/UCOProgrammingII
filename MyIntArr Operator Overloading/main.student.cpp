#include <iostream>
#include <iomanip>
#include <string>
#include "MyIntArr.h"

/* ALERT!!
 * passing ‘const MyIntArr’ as ‘this’ argument of ‘int& MyIntArr::operator[](int)’ discards qualifiers [-fpermissive]
 * For the error describe above, don't use const MyIntArr&. Use MyIntArr&
 * Just remember, to be able to use arr[i], arr must be passed not as a const object 
 */



void display_testcase(int, string);

int main()
{

	int count = 0;
	const int SIZE = 5;
	display_testcase(count++, "Create a1");
	MyIntArr a1(SIZE);

	display_testcase(count++, "Perform a1[i] = i * 10");
	for(int i = 0; i < a1.get_size(); i++)
		a1[i] = i * 10;

	display_testcase(count++, "Print a1");
	cout << a1;

	display_testcase(count++, "Print a1's second element");
	cout << a1[1] << "\n"; 
	
	display_testcase(count++, "Create a2 using a2(++a1)");
	MyIntArr a2(++a1);
	display_testcase(count++, "Print a2");
	cout << a2;
	display_testcase(count++, "Print a1");
	cout << a1;

	display_testcase(count++, "Create a3");
	MyIntArr a3(5);
	display_testcase(count++, "Get inputs for a3");
	cin >> a3;
	display_testcase(count++, "Print a3");
	cout << a3;

	display_testcase(count++, "Create a4 using a4 = a2 + a3)");
	MyIntArr a4 = a2 + a3;
	display_testcase(count++, "Print a4");
	cout << a4; 


	display_testcase(count++, "Create a5");
	MyIntArr a5;
	display_testcase(count++, "Print a5");
	cout << a5;
	display_testcase(count++, "Perform a5 = a2");
	a5 = a2;
	display_testcase(count++, "Print a5");
	cout << a5;

	display_testcase(count++, "Create a6 using a6(a5++)");
	MyIntArr a6(a5++);
	display_testcase(count++, "Print a6");
	cout << a6;
	display_testcase(count++, "Print a5 after post-inc");
	cout << a5;

	display_testcase(count++, "Perform a4 = a5 - a3");
	a4 = a5 - a3;
	display_testcase(count++, "Print a4");
	cout << a4;

	return 0;
}

void display_testcase(int count, string name)
{

	int len = name.length();
	cout << "\n" << string(15, '-') << " " << to_string(count) << ". " << name << " " << string(40-len, '-') << "\n";  
}
