#include <iostream>
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

void Student::enterInformation(){

}

void Student::displayInformation(){

	cin.ignore();
	cout << "Enter student's name: ";
	getline(cin, _name); // getline() for striung type
	cout << "Enter id: ";
	cin >> _id; // cin for number data type,
	cout << "Enter classroom: ";
	getline(cin, _classroom); // getline() for striung type
	cout << "Enter student's mark: ";
	cin >> _classroom; // cin for number data type
}	

main(){

}