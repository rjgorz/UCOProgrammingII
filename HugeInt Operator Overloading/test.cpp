#include <iostream>
#include "HugeInt.h"

using namespace std;

int main()
{
    HugeInt n1(765320);
    HugeInt n2(765321);

    long double value = n2; //==> n5.operator long double();
    cout << sizeof(long double) << "\n";
    cout << "Convert n5 to long double : " << value << "\n";

    return 0;
}