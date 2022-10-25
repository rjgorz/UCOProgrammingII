#ifndef CHECKING_H
#define CHECKING_H

#include "account.h"

//derived class Checking, publically inherits members of base class BankAccount
class Checking : public BankAccount
{
    public:
        //new constructors and destructor for derived class
        Checking();
        Checking(double, double);
        virtual ~Checking();  //optionally declared as virtual for potential further expansion of the program

        //update function redefinition
        virtual void update();
};

#endif