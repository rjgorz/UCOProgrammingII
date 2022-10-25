#include <iostream>
#include "checking.h"

using namespace std;

//Checking default constructor
Checking::Checking()
{
    //empty, will implicitly call BankAccount default constructor
}

//Checking constructor with pass in values, calls BankAccount constructor with pass in values
Checking::Checking(double b, double i) : BankAccount(b, i)
{
    //will use passed in values to pass into BankAccount constructor
}

//Checking destructor
Checking::~Checking()
{
    cout << "Checking::~Checking() called : " << this << "\n";

    //empty, Checking does not directly utilize the heap
}

//update function redifiniton: processes yearly interest specific to checking accounts
void Checking::update()
{
    //get current balance and interest rate
    double balance = get_balance();
    double rate = get_interest_rate();

    //only processes yearly interest if the account has a balance greater than $1,000
    if(balance > 1000)
    {
        balance *= (1 + (rate/100));    //calculates new balance with interest added
        set_balance(balance);           //uses setter function to update account balance
    }
}