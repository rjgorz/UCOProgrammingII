#include <iostream>
#include <iomanip>
#include "account.h"

using namespace std;

int BankAccount::count = 0;  //declares initial account count to 0

//BankAccount default constructor
BankAccount::BankAccount()
{
    //cout << "BankAccount() called : " << this << "\n";

    balance = new double;
    interestRate = new double;

    *balance = 0;       //initialize balance of new account to 0 (default constructor)
    *interestRate = 0;  //initialize interest rate of new account to 0 (default constructor)

    count++;  //increments account count
}

//BankAccount constructor with passed in values
BankAccount::BankAccount(double b, double r)
{
    //cout << "BankAccount(" << b << ", " << r << ") called : " << this << "\n";

    balance = new double;
    interestRate = new double;  //new memory reservation in the heap to store balance and interest rate

    *balance = b;       //initialize balance to the passed in value b
    *interestRate = r;  //initialize interest rate to the passed in value r

    count++;  //increments account count
}

//BankAccount desturctor
BankAccount::~BankAccount()
{
    //cout << "~BankAccount() called : " << this << "\n";

    delete balance;         //delete memory reservation in the heap for balance value
    delete interestRate;    //delete memory reservation in the heap for interest rate value
}

//get_balance function definition: returns the current balance of the given account
double BankAccount::get_balance() const
{
    //cout << "get_balance() called : " << this << "\n";

    return *balance;
}

//get_interest_rate function definition: returns the current interest rate of the given account
double BankAccount::get_interest_rate() const
{
    //cout << "get_interest_rate() called : " << this << "\n";

    return *interestRate;
}

//set_balance function declaration: sets the balance of the given account to the passed in value
void BankAccount::set_balance(double b)
{
    //cout << "set_balance(" << b << ") called : " << this << "\n";

    *balance = b;
}

//set_interest_rate function definition: sets the interest rate of the given account to the passed in value
void BankAccount::set_interest_rate(double i)
{
    //cout << "set_interest_rate(" << i << ") called : " << this << "\n";

    *interestRate = i;
}

//print function declaration: prints a formatted statement showing the current balance of the given account
void BankAccount::print(ostream& out)
{
    out << fixed << setprecision(2);
    out << "Balance = $" << *balance << "\n";
}

//deposit function definition: applies a deposit to the current account given an amount passed in
void BankAccount::deposit(double amt)
{
    //cout << "deposit(" << amt << ") called : " << this << "\n";

    *balance += amt;  //add the passed in amount to the current balance
}

//withdraw function definition: applies a withdrawal to the current account given an amount passed in
void BankAccount::withdraw(double amt)
{
    //cout << "withdraw(" << amt << ") called : " << this << "\n";

    //error check to confirm there is a sufficient balance in the account to make the withdrawal
    if(*balance < amt)
    {
        cout << "Invalid withdrawal, insufficient balance.";
        return;
    }

    *balance -= amt;  //deduct the passed in amount from the current balance
}

//get_count function definition: returns the current number of BankAccounts created
int BankAccount::get_count()
{
    return count;
}

//Node default constructor
Node::Node()
{
    //cout << "Node::Node() called : " << this << "\n";
    
    account = nullptr;
    next = nullptr;     //set both pointers to nullptr
}

//Node destructor
Node::~Node()
{
    //cout << "Node::~Node() called : " << this << "\n";

    delete account;  //deletes the account associated with the Node, will implicitly call destructors for Checking/Savings and BankAccount to fully clear memory reserves
}

//Queue default constructor
Queue::Queue()
{
    //cout << "Queue::Queue() called : " << this << "\n";

    front = nullptr;
    rear = nullptr;     //set both pointers to nullptr
}

//Queue destructor
Queue::~Queue()
{
    //cout << "Queue::~Queue() called : " << this << "\n";

    //condition for no items left in the queue, print error and return
    if(front == nullptr)
    {
        cout << "There is no Node left to delete.\n";
        return;
    }

    //runs through the SLL to delete each Node starting from the front until the end is reached using temp Node*
    while(front != nullptr)
    {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

//enqueue function declaration: creates a new Node at the rear of the Queue and assigns an account to it
void Queue::enqueue(BankAccount* acc)
{
    //cout << "Queue::enqueue() called : " << this << "\n";

    //create the new Node in the heap and assign the passed in account to the Node
    Node* temp = new Node;
    temp->account = acc;

    //case for the first Node in the Queue
    if(rear == nullptr)
    {
        front = rear = temp;  //sets both front and rear to the new Node, it is the only item in the Queue
        return;
    }

    //case for an already occupied Queue, appends and links the new Node to the rear of the Queue
    rear->next = temp;
    rear = temp;
}

//dequeue function definition: deletes the front Node in the Queue
void Queue::dequeue()
{
    //cout << "Queue::deueue() called : " << this << "\n";

    //check if there's any data in the Queue, print error if empty
    if(front == nullptr)
    {
        cout << "There are no Nodes left in the Queue! dequeue() failed.\n";
        return;
    }

    Node* temp = front;     //temp pointer to preserve address of the current front
    front = front->next;    //reassigns the front to the next Node in the Queue
    delete temp;            //uses the temp pointer to delete the former front Node

    //if the current dequeue call deleted the last Node, also set rear to nullptr to avoid dangling pointer
    if (front == nullptr)
        rear = nullptr;
}

//get_front function declaration: returns the address of the current front Node in the Queue
Node* Queue::get_front() const
{
    //cout << "Queue::get_front() called : " << this << "\n";

    return front;
}

//get_rear function declaration: returns the address of the current rear Node in the Queue
Node* Queue::get_rear() const
{
    //cout << "Queue::get_rear() called : " << this << "\n";

    return rear;
}