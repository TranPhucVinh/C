#include <iostream>
#include <iomanip> // io manipulation

using namespace std;
class Student{
	public:
	string getName();
	void setName(string name);
	string getClassroom();
	void setClassroom(string classroom);
	int getID();
	void setID(int id);
	double getMark();
	void setMark(double mark);
	Student();
	Student (string name, string classroom, int id, double mark);
	void enterInformation();
	void displayInformation();

	private:
	string _name;
	string _classroom;
	int _id;
	double _mark;
};
Student::Student(){ // can put all these declaration in constructor Student(string name, string classroom, int id, double mark)
	_name = "";
	_id = 0;
	_classroom = "";
	_mark = 0;
}

Student::Student(string name, string classroom, int id, double mark){
	_name = name;
	_id = id;
	_classroom = classroom;
	_mark = mark;
}

string Student::getName(){
	return _name;
}
void Student::setName(string name){
	_name = name;
}

string Student::getClassroom(){
	return _classroom;	
}

void Student::setClassroom(string classroom){
	_classroom = classroom;
}

int Student::getID(){
	return _id;	
}

void Student::setID(int id){
	_id = id;
}

double Student::getMark(){
	return _mark;
}

void Student::setMark(double mark){
	_mark = mark;
}

void Student::displayInformation(){
	cout << setw(20) << _id << setw(30) << _name << setw(10) << _classroom << setw(10) << _mark << endl;

}

void Student::enterInformation(){

	cin.ignore();
	cout << "Enter student's name: ";
	getline(cin, _name); // getline() for string type
	cout << "Enter id: ";
	cin >> _id; // cin for number data type
	cout << "Enter classroom: ";
	cin.ignore(1);
	getline(cin, _classroom); // getline() for string type
	cout << "Enter student's mark: ";
	cin >> _mark; // cin for number data type
}	

main(){
	int num, n, i;
	int index = 0;
	Student arrStudent[100]; // array to store Student's information
	cout << "Enter corresponding number: \n";
	cout << "1. Add student's information \n";
	cout << "2. Delete student's information \n";
	cout << "3. Display student's information \n";
	cout << "4. Search \n";
	cout << "5. Exit \n";

	do 
	{
	cout << "Your choice ";
	cin >> num;
	if ( num >=1 && num <= 5){
		switch (num)
		{
		case 1:
			{
			cout << "Enter the number of student you wish to enter: ";
			cin >> n;
			for (i =0 ; i < n; i++){
				Student student;
				student.enterInformation();
				arrStudent[i] = student;
				index++;
			}
		break;
	}
		case 2:
		break;
		case 3:
		{
		cout << setw(20) << "ID" << setw(30) << "Name "<< setw(10) << "Class" << setw(10) << "Mark" << endl;
			for (i = 0; i < index; i++){
				arrStudent[i].displayInformation();
			}
		}
		break;
		case 4:{
			int studentID;
			cout << "Enter the ID of student: ";
			cin >> studentID;
			for (i = 0; i < n; i++){
				if (arrStudent[i].getID() == studentID)
				{
				cout << setw(20) << "ID" << setw(30) << "Name "<< setw(10) << "Class" << setw(10) << "Mark" << endl;
				arrStudent[i].displayInformation();
				}
			}
		}
		break;
		case 5:
		break;
	}
	}
	 else
	{
	 	cout << "You fool, entering the wrong number !!!!";
	}
}
	while (num>=1 && num < 5 );
	//
}

// ONLY SAVE student information in buffer, lost after ending program

// IN the program above, we haven;t used Student::set_() function as we haven't set any value, the value of name, id, class, mark are all enter from keyboard and are then processed