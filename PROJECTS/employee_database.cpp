#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void createFile();
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
}
}
void searchID(){
	ifstream myFile("employee.txt");
	int id, salary, findID;
	string name;
	cout << "Enter employee's ID: ";
	cin >> findID;
	myFile >> id >> name >> salary;
	if (findID == id){
		cout << id << " " <<  name << " " << salary;
	}
}

void searchName(){
	cout << " ";
}

void searchSalary(){
	cout << " ";
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
	case 3:
	searchSalary();
	}
}

