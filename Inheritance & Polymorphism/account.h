#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
using namespace std;

//base class
class BankAccount
{
private:
	//member variables that all accounts possess, private to the base class
	double* balance;
    double* interestRate;
	static int count;
     
public:
	//constructors and destructor functions
	BankAccount();
	BankAccount(double, double);
	virtual ~BankAccount();  //virtual destructor to ensure all necessary destructor calls are made to delete memory in the heap

	//getter and setter functions to access private variables outside the base class
	double get_balance() const;
	double get_interest_rate() const;
	void set_balance(double);
	void set_interest_rate(double);

	//other member functions
    void print(ostream&);
	void deposit(double);
	void withdraw(double);
	static int get_count();
	virtual void update() = 0;  //pure virtual function with = 0, not going to give the body to this function in this class
};

//Node struct to build Nodes in the Queue
struct Node
{
	//each Node contains a BankAccount* to point to its account in the heap and the Node* next to link the list
    BankAccount* account;
    Node* next;

	//constructor and destructor funcitons
    Node();
    virtual ~Node();
};

//Queue class
class Queue
{
    private:
		//front and rear Node*'s to track the status of the Queue
        Node* front;
		Node* rear;
        
    public:
		//constructor and destructor functions
        Queue();
        virtual ~Queue();

		//Queue manipulation functions
        void enqueue(BankAccount*);
        void dequeue();

		//getter functions
		Node* get_front() const;
		Node* get_rear() const;
};

#endif