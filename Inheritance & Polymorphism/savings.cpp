#include <iostream>
#include "savings.h"

using namespace std;

//Savings default constructor
Savings::Savings()
{
    //empty, will implicitly call BankAccount default constructor
}

//Savings constructor with pass in values, calls BankAccount constructor with pass in values
Savings::Savings(double b, double i) : BankAccount(b, i)
{
    //will use passed in values to pass into BankAccount constructor
}

//Savings destructor
Savings::~Savings()
{
    cout << "Savings::~Savings() called : " << this << "\n";

    //empty, savings does not directly utilize the heap
}

//update function redifiniton: processes yearly interest specific to savings accounts
void Savings::update()
{
    //get current balance and interest rate
    double balance = get_balance();
    double rate = get_interest_rate();

    //processes yearly interest for any given account balance
    balance *= (1 + (rate/100));    //calculates new balance with interest added
    set_balance(balance);           //uses setter function to update account balance
}