#include <iostream>
#include <fstream>  //for file input
#include <iomanip>  //for table formatting
#include <string>

using namespace std;

//structure to build Employees
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

//function prototypes
void print(Employee*[], int);
void print(Employee*);
void print_header();
int sort_menu();
void bubble_sort(Employee*[], int);
void selection_sort(Employee*[], int);

int main()
{
    //open input file and check if opened successfully, terminates if unsuccessful
    fstream fin("a2-employee.txt", ios::in);
    if (fin.fail())
    {
        cout << "\nCannot open input file!" << endl;
        return 1;
    }

    int count = 0;  //initialize counter to keep track of the number of employees read in

    //loop to count number of employees stored in the file
    while (!fin.eof())
    {
        string line;
        getline(fin, line);
        if (line[0] != 'S' && line[0] != 'H')
        {
            //do not increment count, ignores empty lines read in
        }
        else
            count++;
    }

    fin.close();
    fin.open("a2-employee.txt", ios::in);  //reset file for processing content

    Employee* p[30];  //initializes an array of Employee pointers

    //loops through the file to store Employees in the heap one at a time, utilizing pointers in the established array
    for (int i = 0; i < count; i++)
    {
        p[i] = new Employee;
        fin >> p[i]->type;
        if (p[i]->type == 'S')
        {
            fin >> p[i]->ssn >> p[i]->lastName >> p[i]->firstName >> p[i]->dept >> p[i]->role >> p[i]->salary;            
            p[i]->hours = 0;
            p[i]->rate = 0;  //sets hours and rate to 0 for salaried employees
        }
        else if (p[i]->type == 'H')
        {
            fin >> p[i]->ssn >> p[i]->lastName >> p[i]->firstName >> p[i]->dept >> p[i]->role >> p[i]->hours >> p[i]->rate;
            p[i]->salary = 0;  //sets salary to 0 for hourly employees
        }
    }

    //close input file
    fin.close();

    //print out number of employees read in from the file
    cout << "Number of employees imported: " << count << '\n';

    //prints out the original unsorted data that was read in
    print(p, count);

    //displays the selection menu for which method of sorting to be chosen by the user
    int selection = sort_menu();

    //loops through selection menu until the exit option is entered
    while (selection != 3) {
        //runs bubble sorting algorithm if 1 is entered
        if (selection == 1)
        {
            bubble_sort(p, count);
            print(p, count);  //prints out newly sorted list
        }
        //runs selection sorting algorithm when 2 is entered
        else if (selection == 2)
        {
            selection_sort(p, count);
            print(p, count);
        }
        //error case for any number entered that is not 1/2/3
        else
        {
            cout << "Invalid selection, please try again.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        selection = sort_menu();
    }

    //loop to deallocate the array of pointers
    for (int i = 0; i < count; i++)
    {
        delete p[i];
    }

    return 0;
}

//print() function definition, for passing in the array of pointers
void print(Employee* a[], int b)
{
    //prints the table header and calls the print() funciton for single Employee pointers
    print_header();
    for (int i = 0; i < b; i++)
    {
        print(a[i]);
    }
    return;
}
//print() function definition, overloaded to accept single employee pointers
void print(Employee* e)
{
    //prints the data members for each employee stored in the heap, formats in a table
    cout << fixed << left << setprecision(2) << setw(6) << e->type << setw(15) << e->ssn << setw(10) << e->lastName << setw(15)
        << e->firstName << setw(17) << e->dept << setw(24) << e->role << right << setw(13);

        //cases to print the appropriate data based on employee type
        if (e->salary == 0)
            cout << " " << setw(10);
        else
            cout << e->salary << setw(10);

        if (e->hours == 0)
            cout << " " << setw(10) << " " << endl;
        else
            cout << e->hours << setw(10) << e->rate << endl;
        
    return;
}

//print_header() function definition, prints out the table header for employee data
void print_header()
{
    cout << right << setw(122) << setfill('-') << " " << endl;
    cout << left << setfill(' ') << setw(6) << "Type"
            << setw(15) << "SSN" << setw(10) << "Last Name"
            << setw(15) << "First Name" << setw(17) << "Department"
            << setw(24) << "Role" << right << setw(13) << "Salary" << setw(10) << "Hours"
            << setw(10) << "Rate" << endl;
    cout << right << setw(122) << setfill('-') << " " << setfill(' ') << endl;
    return;
}

//sort_menu() function definition, displays menu to choose which sorting algorithm is to be used
int sort_menu()
{
    cout << "\n[1] Bubble Sort"
        << "\n[2] Selection Sort"
        << "\n[3] Exit"
        << "\nPlease enter the number associated with the desired selection: ";
        int selection;
        cin >> selection;
        return selection;
}

//bubble_sort() funcition definition, sorts the employees by SSN using the bubble sort algorithm
void bubble_sort(Employee* a[], int b)
{
    int i, j;
    Employee* temp;

    for (i = 0; i < b - 1; i++)
    {
        for (j = 0; j < b - i - 1; j++)
        {
            if (a[j]->ssn > a[j + 1]->ssn)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

//selection_sort() funcition definition, sorts the employees by SSN using the selection sort algorithm
void selection_sort(Employee* a[], int b)
{
    int i, j, min;
    Employee* temp;
 
    for (i = 0; i < b - 1; i++)
    {
        min = i;
        for (j = i + 1; j < b; j++)
        {
            if (a[j]->ssn < a[min]->ssn)
            {
                min = j;
            }
 
            if(min != i)
            {
                temp = a[i];
                a[i] = a[min];
                a[min] = temp;
            }
        }
    }
}