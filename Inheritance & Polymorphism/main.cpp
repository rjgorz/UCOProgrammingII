#include <iostream>
#include "account.h"
#include "checking.h"
#include "savings.h"

using namespace std;

//global variable declarations for all required initial balances and interest rates
const double bal[6] = {500.5, 700.7, 900.9, 200.1, 400.3, 600.6};
const double rate[2] = {3, 1.5};

int main()
{
    Queue q;  //create a new Queue object to store accounts

    //loop to create all three savings accounts and add them to the queue
    for(int i = 0; i < 3; i++)
    {
        BankAccount* newAcc = new Savings(bal[i], rate[0]);  //pulls balance and interest rate from global arrays
        q.enqueue(newAcc);  //add the new account to the Queue
    }

    //loop to create all three checking accounts and add them to the queue
    for(int i = 3; i < 6; i++)
    {
        BankAccount* newAcc = new Checking(bal[i], rate[1]);  //pulls balance and interest rate from global arrays
        q.enqueue(newAcc);  //add the new account to the Queue
    }

    Node* temp = q.get_front();  //set temp to the front Node to start
    //loop to process all account changes for each year and update account balances
    for(int i = 1; i <= 5; i++)
    {
        //process through the entire Queue until the end is reached
        while(temp != nullptr)
        {
            //process three deposits of $300 and one withdrawal of $150.50, update balance with interest for the given year
            for(int j = 1; j <= 3; j++)
                temp->account->deposit(300);
            
            temp->account->withdraw(150.5);
            temp->account->update();

            temp = temp->next;  //progress to the next Node in the SLL
        }

        temp = q.get_front();  //reset temp to the front Node to cycle through the SLL for the next year
    }

    //print output header with title and total number of accounts created
    cout << "\nAt the end of the 5th year:\n";
    cout << "Number of accounts: " << BankAccount::get_count() << "\n\n";

    int k = 1;  //counter to properly display the correct numbered account (eg. Savings Account #1, then Savings Account #2, etc.)
    //loop to run through the Queue to print final end balances of Savings accounts first
    while(temp != nullptr)
    {
        //check condition to confirm the current account is Savings by verifying the correct interest rate for savings accounts
        if(temp->account->get_interest_rate() == 3)
        {
            cout << "Savings Account #" << k << ":\n\t";
            temp->account->print(cout);  //prints formatted output of the account name and final balance
            k++;  //increment counter when an account is found/printed
        }
        temp = temp->next;  //progress to the next Node in the SLL
    }

    cout << "\n";  //formatting line break

    temp = q.get_front();  //reset temp to the front Node to cycle through the SLL
    k = 1;  //counter to properly display the correct numbered account (eg. Checking Account #1, then Checking Account #2, etc.)
    //loop to run through the Queue to print final end balances of Checking accounts next
    while(temp != nullptr)
    {
        //check condition to confirm the current account is Checking by verifying the correct interest rate for checking accounts
        if(temp->account->get_interest_rate() == 1.5)
        {
            cout << "Checking Account #" << k << ":\n\t";
            temp->account->print(cout);  //prints formatted output of the account name and final balance
            k++;  //increment counter when an account is found/printed
        }
        temp = temp->next;  //progress to the next Node in the SLL
    }

    cout << "\n";  //formatting line break

    //loop to clear the queue of all created accounts
    for(int i = 0; i < BankAccount::get_count(); i++)
        q.dequeue();  //properly deletes all Nodes and accounts, calls proper destructors

    return 0;

    //q out of scope, destructor calls implicitly
}