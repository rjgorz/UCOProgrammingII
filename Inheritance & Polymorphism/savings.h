#ifndef SAVINGS_H
#define SAVINGS_H

#include "account.h"

//derived class Savings, publically inherits members of base class BankAccount
class Savings : public BankAccount
{
    public:
        //new constructors and destructor for derived class
        Savings();
        Savings(double, double);
        virtual ~Savings();  //optionally declared as virtual for potential further expansion of the program

        //update function redefinition
        virtual void update();
};

#endif