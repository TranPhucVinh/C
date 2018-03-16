#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void addInformation();
void editInformation();
void search();
// void deleteInformation();
void loop();

main(){
	int choice;
	cout << "Employee management program \n";
START:	cout << "Enter the corresponding number  \n";
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
				loop();
				case 2:
				editInformation();
				loop();
				break;
				case 3:
				search();
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
	loop();
           }

void searchName(){
	ifstream employee("employee.txt");
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
	loop();
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
	loop();
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

void editInformation(){
	fstream employee("employee.txt");
	int id, enterID, count = 0;
	string name, enterName;
	double salary, enterSalary;
	int findID;
	employee.seekg(44); // set cursor based on set(w) in file.txt
	cout << "Enter the ID of employee you wish to edit: ";
	cin >> findID;
	while(employee >> id >> name >> salary)
	{
	if (findID == id){
	cin.ignore();
	cout << "Edit ID: ";
	cin >> enterID;
	cout << "Edit Name: ";
	cin.ignore(1);
	getline(cin, enterName);
	cout << "Edit Salary: ";
	cin >> enterSalary;
	cout << "Name" << setw(20) << "Age" << setw(20) << "Salary" << endl;
	cout << enterID << setw(20) <<  enterName << setw(20) << enterSalary << endl;
	count = 1;
	}
	}
	if (count == 0) {cout << " Fuck that shit \n";}
	employee.close();
}

void loop() {
	string resp;
	cout << "WANT SOME MORE BLOODY ? (TYPE IN Y OR N) \n";
	cin >> resp;
goAgain:	if (resp == "Y") {
		main();
	}
	else if (resp == "N"){
		cout << "Thanks for your experience";
	}
	else 
	{
	cout << "You fool, entering wrong words even with only 2 choices !!! \n";
	cout << "Enter the again, you fool! :"	;
	cin >> resp;
	goto goAgain;
	}
}