#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>

using std::ostream;
using std::istream;
using std::string;

class HugeInt {
private:
    char*   number;
    int     size;
    int     capacity;
    void    compute_size();
    
public:
    HugeInt();
    HugeInt(long);
    HugeInt(const char*);
    HugeInt(const HugeInt&);
    ~HugeInt();

    HugeInt& operator=(const HugeInt&);
    HugeInt operator+(const HugeInt&);
    HugeInt operator-(const HugeInt&);
    HugeInt operator*(const HugeInt&); 
    HugeInt operator/(const HugeInt&);
    HugeInt operator%(const HugeInt&);

    HugeInt& operator++();
    HugeInt operator++(int);
    bool    operator<=(const HugeInt&);
    char&  operator[](int);
    operator long double();

    friend ostream& operator<<(ostream&, const HugeInt &);
    friend istream& operator>>(istream&, HugeInt&);
    
};

#endif
