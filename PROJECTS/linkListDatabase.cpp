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
	string name;
	double salary;
	int findID;
	employee.seekg(44); // set cursor based on set(w) in file.txt
	cout << "Enter employee's ID: ";
	cin >> findID;
	while(employee >> id >> name >> salary)
	{
	if (findID == id){
	cout << "Name" << setw(20) << "Age" << setw(20) << "Salary" << endl;
	cout << id << setw(20) <<  name << setw(20) << salary << endl;
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
	string name;
	employee.seekg(44);
	cout << "Enter employee's name: ";
	cin.ignore();
	getline(cin, findName);
	while(employee >> id >> name >> salary)
	{
	if (findName == name){
	cout << "Name" << setw(20) << "Age" << setw(20) << "Salary" << endl;
	cout << id << setw(20) <<  name << setw(20) << salary << endl;
	count = 1;
	 }
}	
	if (count == 0) {cout << " Fuck that shit \n";}
	employee.close();
}


void Employee::searchSalary(){
	ifstream employee("database.txt");
	int id;
	double findSalary;
	double salary;
	string name;
	employee.seekg(44);
	cout << "Enter the salary number you wish to search: ";
	cin >> findSalary;
	while(employee >> id >> name >> salary)
	{
	if (findSalary == salary){
	cout << id << " " <<  name << " " << salary << endl;
	 }
	else { cout << "fuck that shit";}	
}
	employee.close();
}

void add();
void search();

main(){
	int choice;
	int index = 0;
	
	cout << "Enter corresponding number: \n";
	cout << "1. Add student's information \n";
	cout << "2. Delete student's information \n";
	cout << "3. Display student's information \n";
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
				// search();
				// searchInformation();
				case 4:
				search();
				break;
				// deleteInformation();
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