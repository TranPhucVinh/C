#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void createFile();
void addInformation();
// void editInformation();
// void searchInformation();
// void deleteInformation();
	

main(){
	createFile();
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
				break;
				case 2:
				break;
				// editInformation();
				case 3:
				break;
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

void createFile() {
	ofstream openFile;
	openFile.open("employee.txt", ios::app); //app stands for append
	openFile << "ID " <<setw(20) << " Name " << setw(20) << "Salary " << endl;
}