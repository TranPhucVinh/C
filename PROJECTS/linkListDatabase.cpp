#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class Employee {
	public:
	void setID(int id);	
	int getID();
	void setName(string name);
	string getName();
	void setMark(double salary);
	double getMark();
	void addInformation();
	void searchID();
	void searchName();
	void searchSalary();
	void edit();

	private: 
	string _name;
	int _id;
	double _salary;
};

void Employee::setID(int id) {
	_id = id;
}

int Employee::getID() {
	return _id;
}

void Employee::setName(string name) {
	_name = name;
}

string Employee::getName() {
	return _name;
}

void Employee::setMark(double salary) {
	_salary = salary;
}

double Employee::getMark() {
	return _salary;
}

void Employee::addInformation(){

	ofstream myFile;
	myFile.open("database.txt", ios::app);
	cin.ignore();
	cout << "Enter employee's ID: ";
	cin >> _id;
	cout << "Enter employee's name: ";
	cin.ignore(1);
	getline(cin, _name);
	cout << "Enter employee's salary: ";
	cin >> _salary;
	myFile << _id << setw(20) << _name << setw(20) << _salary << endl;
	myFile.close();
}

void Employee::searchID(){
	ifstream employee("database.txt");
	int id, count = 0;
	string firstName, lastName;
	double salary;
	int findID;
	employee.seekg(44); // set cursor based on set(w) in file.txt
	cout << "Enter employee's ID: ";
	cin >> findID;
	while(employee >> id >> firstName >> lastName >> salary)
	{
	if (findID == id){
	cout << "ID" << setw(20) << "Name" << setw(20) << "Salary" << endl;
	cout << id << setw(20) <<  firstName << " " << lastName << setw(20) << salary << endl;
	count = 1;
	}
	}
	if (count == 0) {cout << " Fuck that shit \n";}
	employee.close();
           }

void Employee::searchName(){
	ifstream employee("database.txt");
	int id, count = 0;
	string findName;
	double salary;
	string firstName, lastName;
	employee.seekg(44);
	cout << "Enter employee's name: ";
	cin.ignore();
	getline(cin, findName);
	while(employee >> id >> firstName >> lastName >> salary)
	{
	if (findName == firstName){
	cout << "ID" << setw(20) << "Name" << setw(20) << "Salary" << endl;
	cout << id << setw(20) <<  firstName << " " << lastName << setw(20) << salary << endl;
	count = 1;
	 }
}	
	if (count == 0) {cout << " Fuck that shit \n";}
	employee.close();
}


void Employee::searchSalary(){
	ifstream employee("database.txt");
	int id, count;
	double findSalary;
	double salary;
	string firstName, lastName;
	employee.seekg(44);
	cout << "Enter the salary number you wish to search: ";
	cin >> findSalary;
	while(employee >> id >> firstName >> lastName >> salary)
	{
	if (findSalary == salary){
	cout << id << " " <<  firstName << " " << lastName << " " << salary << endl;
	count = 1;
	 }
}
	if (count == 0) {cout << " Fuck that shit \n";}
	employee.close();
}

void add();
void search();
void display();

main(){
	int choice;
	int index = 0;
	
	cout << "Enter corresponding number: \n";
	cout << "1. Add employee's information \n";
	cout << "2. Edit employee's information \n";
	cout << "3. Display employee's information \n";
	cout << "4. Search \n";
	cout << "5. Exit \n";
	cout << "Your choice ";

	cin >> choice;
	if ( choice >0 && choice < 6){
		switch (choice)
			{
				case 1:
				add();
				// loop();
				case 2:
				// edit();
				// loop();
				break;
				case 3:
				{
				cout << "ID" << setw(20) << "Name"<< setw(20) << "Salary" << endl;
				display();
				}
				case 4:
				search();
				case 5:
				break;
			}
	}	
	else 	{
		cout << "You fool, entering wrong number \n";
		}
}

void add() {
	int employeeNum;
	cout << "Number of employee you wish to enter: ";
	cin >> employeeNum;
	for (int i = 0; i < employeeNum; i++) {
	Employee employee;
	employee.addInformation();
			}
}

void search(){
	int choice;
	Employee employee;
	cout << "Enter the corresponding number \n";
	cout << "1. Search by ID \n";
	cout << "2. Search by name \n";
	cout << "3. Search by salary \n";
	cout << "Your choice: ";
	cin >> choice;
	switch (choice){
	case 1:
	employee.searchID();
	break;
	case 2:
	employee.searchName();
	break;
	case 3:
	employee.searchSalary();
	break;
	}
}

void display(){
	ifstream employee("database.txt");
	ifstream employee0("database.txt");
	int id;
	string firstName;
	string lastName;
	double salary;
	employee.seekg(44);
	employee0.seekg(44);
	while (employee >> id >> firstName >> lastName >> salary)
	{
		cout << id << setw(20) <<  firstName << " " << lastName << setw(20) << salary << endl;
	}
	cout << "Enter name hello \n";
}

