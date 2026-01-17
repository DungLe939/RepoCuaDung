#include <iostream>
using namespace std;

struct Beverage {
	Beverage() {
		cout << "Beverage" << endl;
	}
	Beverage(const Beverage& a) {
		cout << "Copy beverage" << endl;
	}
};

struct Coffee : public Beverage {
	Coffee() {
		cout << "Coffee" << endl;
	}
	Coffee(const Coffee& a) {
		cout << "Copy Coffee" << endl;
	}
};

struct Cappuchino : public Coffee {
	Cappuchino() {
		cout << "Cappuchino" << endl;
	}
};

//int main() {
//	Cappuchino c1;
//	cout << endl;
//	Cappuchino c2(c1);
//
//
//	system("pause");
//	return 0;
//}