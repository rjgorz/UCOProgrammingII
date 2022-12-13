#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "1234";
    //extracting each character from the string
    for (int i = 0; i < s.size(); i++)
    {
        cout << s[i] << ", "; //treat a string like an array, s[i]: char type
    }
    cout << "\n";

    cout << "Printing ASCII value of each character....\n";
    for (int i = 0; i < s.size(); i++)
    {
        cout << (int)(s[i]) << ", "; //treat a string like an array, type conversion from char to int
    }
    cout << "\n";

    cout << "Printing decimal value of each character....\n";
    cout << "For example, \'1\' will be printed as a decimal...\n";
    for (int i = 0; i < s.size(); i++)
    {
        cout << (int) s[i] - '0' << ", "; //subtract 48, which is the ASCII code for '0'
    }
    cout << "\n";

    return 0;
}