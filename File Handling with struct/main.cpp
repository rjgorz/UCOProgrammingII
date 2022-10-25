#include <iostream>
#include <fstream>  //for input and output
#include <iomanip>
#include <string>

using namespace std;

//structure to build employees
struct Employee
{
    char type;
    string ssn;
    string lastName;
    string firstName;
    string dept;
    string role;
    double salary;
    double hours;
    double rate;
};

int main()
{
    Employee e[100];  //initializes an array of Employee data types to store from input file

    //open input file and check if opened successfully, terminates if unsuccessful
    fstream fin("a1-employee.txt", ios::in);
    if (fin.fail())
    {
        cout << "Cannot open input file!" << endl;
        return 1;
    }

    int i = 0;  //initialize counter to keep track of the number of employees read in from the input file

    //reads through the file contents line by line until end of the file is reached
    while(!fin.eof())
    {
        fin >> e[i].type;  //initially read in type

        //reads in remaining details based on salaried type
        if (e[i].type == 'S')
        {
            fin >> e[i].ssn >> e[i].lastName >> e[i].firstName >> e[i].dept >> e[i].role >> e[i].salary;
        }
        //reads in remaining details based on hourly type
        else if (e[i].type == 'H')
        {
            fin >> e[i].ssn >> e[i].lastName >> e[i].firstName >> e[i].dept >> e[i].role >> e[i].hours >> e[i].rate;
        }

        i++;  //increases counter for each employee read in
    }

    //print out header for all salaried employees
    cout << fixed << setprecision(2) << right << setw(102) << setfill('-') << " " << endl;
    cout << left << setfill(' ') << setw(6) << "Type"
            << setw(15) << "SSN" << setw(10) << "Last Name"
            << setw(15) << "First Name" << setw(17) << "Department"
            << setw(24) << "Role" << right << setw(13) << "Salary" << endl;
    cout << right << setw(102) << setfill('-') << " " << setfill(' ') << endl;

    //loops through to print out all salaried employees only
    for (int j = 0; j < i; j++)
    {
        if (e[j].type == 'S')
        {
            cout << left << setw(6) << e[j].type
                << setw(15) << e[j].ssn << setw(10) << e[j].lastName
                << setw(15) << e[j].firstName << setw(17) << e[j].dept
                << setw(24) << e[j].role << right << setw(13) << e[j].salary << endl; 
        }
    }

    //prints out header for all hourly employees
    cout << "\n" << right << setw(102) << setfill('-') << " " << endl;
    cout << left << setfill(' ') << setw(6) << "Type"
            << setw(15) << "SSN" << setw(10) << "Last Name"
            << setw(15) << "First Name" << setw(17) << "Department"
            << setw(24) << "Role" << right << setw(7) << "Hours"
            << setw(6) << "Rate" << endl;
    cout << right << setw(102) << setfill('-') << " " << setfill(' ') << endl;

    //loops through to print out all hourly employees only
    for (int j = 0; j < i; j++)
    {
        if (e[j].type == 'H')
        {
            cout << left << setw(6) << e[j].type
                << setw(15) << e[j].ssn << setw(10) << e[j].lastName
                << setw(15) << e[j].firstName << setw(17) << e[j].dept
                << setw(24) << e[j].role << right << setw(7) << e[j].hours
                << setw(6) << e[j].rate << endl;
        }
    }

    //close input file
    fin.close();

    //prompts user to enter a SSN to search for and display employee details
    cout << "\n" << "Enter an Employee's SSN (XXX-XX-XXXX) to display details, or Q to exit: ";
    string social;
    getline(cin, social);

    bool found;  //initialize boolean to track if the entered SSN is found in the system or not

    //loops through all employees to search for a matching SSN
    //re-prompts user to enter another SSN until the sentinel 'Q' is entered
    while (social != "Q") {
        found = false;
        for (int k = 0; k < i; k++)
        {
            if (e[k].ssn == social)
            {
                //displays employee details if SSN is for a salaried employee
                if (e[k].type == 'S')
                {
                    cout << "\n" << left << setw(6) << e[k].type
                        << setw(15) << e[k].ssn << setw(10) << e[k].lastName
                        << setw(15) << e[k].firstName << setw(17) << e[k].dept
                        << setw(24) << e[k].role << right << setw(13) << e[k].salary << endl;
                }
                //displays employee details if SSN is for an hourly employee
                else if (e[k].type == 'H')
                {
                    cout << "\n" << left << setw(6) << e[k].type
                        << setw(15) << e[k].ssn << setw(10) << e[k].lastName
                        << setw(15) << e[k].firstName << setw(17) << e[k].dept
                        << setw(24) << e[k].role << right << setw(7) << e[k].hours
                        << setw(6) << e[k].rate << endl;
                }

                found = true;  //sets boolean check to true, SSN was found
            }
        }

        //specific prompt for user if the original entered number was not found
        if (found == false)
        {
            cout << "SSN not found! Please enter a valid SSN, or Q to exit: ";
            getline(cin, social);
        }
        //specific prompt for user if the original entered number was found
        else
        {
            cout << "\n" << "Enter another Employee's SSN (XXX-XX-XXXX) to display details, or Q to exit: ";
            getline(cin, social);
        }
    }
    return 0;
}