#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void addInformation();
// void editInformation();
void search();
// void deleteInformation();
	

main(){
	int choice;
	cout << "Employee management program \n";
	cout << "Enter the corresponding number  \n";
	cout << "1. Add employee's information: \n";
	cout << "2. Edit employee's information: \n";
	cout << "3. Search employee's information: \n";
	cout << "4. Delete employee\n";
	cout << "5. Exit \n";
	cout << "Your choice: ";
	cin >> choice;

	
		if (choice >0 && choice < 6)
		{
			switch (choice)
			{
				case 1:
				addInformation();
				case 2:
				// editInformation();
				case 3:
				search();
				// searchInformation();
				case 4:
				break;
				// deleteInformation();
			}			
		}
		else {
		cout << "You fool, entering wrong number \n";
		}
}
void addInformation(){
	ofstream myFile;
	myFile.open("employee.txt", ios::app);
	int employeeNum;
	int id;
	string name;
	double salary;
	cout << "Number of employee you wish to enter: ";
	cin >> employeeNum;
	for (int i = 0; i < employeeNum; i ++) {
	cin.ignore();
	cout << "Enter employee's ID: ";
	cin >> id;
	cout << "Enter employee's name: ";
	cin.ignore(1);
	getline(cin, name);
	cout << "Enter employee's salary: ";
	cin >> salary;
	myFile << id << setw(20) << name << setw(20) << salary << endl;
	myFile.close();
}
}
void searchID(){
	ifstream employee("employee.txt");
	int id;
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
	}
	}
	employee.close();
           }

void searchName(){
	ifstream employee("employee.txt");
	int id;
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
	 }
	else if (findName != name) { cout << "fuck that shit";}	
}
	employee.close();
}


void searchSalary(){
	ifstream employee("employee.txt");
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

void search(){
	int choice;
	cout << "Enter the corresponding number \n";
	cout << "1. Search by ID \n";
	cout << "2. Search by name \n";
	cout << "3. Search by salary \n";
	cout << "Your choice: ";
	cin >> choice;
	switch (choice){
	case 1:
	searchID();
	break;
	case 2:
	searchName();
	break;
	case 3:
	searchSalary();
	break;
	}
}

