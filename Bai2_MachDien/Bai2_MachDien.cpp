#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
	string name;
public:
	virtual void introduce() {
		cout << "I'm " << name << endl;
	}
	virtual void work() = 0;
	void doDailyTask() {
		introduce();
		work();
	}
};

class Student : public Person {
private:
	Person* pAdvisor;
public:
	Student(string name,
		Person* pAdvisor) {
		this->name = name;
		this->pAdvisor = pAdvisor;
	}
	void introduce() {
		Person::introduce();
		cout << "My advisor " << endl;
		pAdvisor->introduce();
	}
	void work() {
		cout << "study" << endl;
	}
};

class Professor : public Person {
public:
	Professor(string name) {
		this->name = name;
	}
	void work() {
		cout << "teach" << endl;
	}
};

int main() {
	Professor p1("Hinton");
	Student p2("Bengio", &p1);
	Person* p3 = new Student("LeCun",
		&p2);

	p1.introduce();
	p1.work();

	p2.introduce();
	p3->introduce();

	//Person* p4 = new Person();

	delete p3;
	//delete p4;

	return 0;
}

//a) Are there any lines in the main() function that cannot be compiled ?
//If yes, why can’t they be compiled ?

// Trả lời: main bị lỗi ở Person* p4 = new Person(); do person là abstract 

//b) Assume that all invalid lines of code are removed, can we change the
//key word protected in Line #2 to private ? Explain.

// Trả lời: Không thể tại vì kế thừa cần protected khi chỉnh qua private lớp con không thể kế thừa

//c) What is the output of this code if the invalid lines of code are
//removed ?

// I'm Hinton
// teach
// I'm Bengio
// My advisor 
// I'm Hinton
// I'm Lecun
// My advisor 
// I'm Bengio
// My advisor 
// I'm Hinton