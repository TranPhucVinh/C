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

}

Student::getID(){
	
}

main(){

}