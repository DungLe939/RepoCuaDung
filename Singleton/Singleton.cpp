#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

bool flag = true;

class PrintConsoleDivice {
private:
	// Bien thanh vien
	ostream* os;
	string text;
	// Nhot constructor lai 
	PrintConsoleDivice() {
		os = &cout;
	}
public:
	void Print(const string& s) {
		*os << s;
	}
	void printText() {
		cout << text << endl;
	}
	static PrintConsoleDivice GetInstace() {
		static PrintConsoleDivice instance;
		if (flag == true) {
			flag = false;
			instance.text = "Just a text";
		}
		return instance;
	}
};

int main() {
	PrintConsoleDivice print = PrintConsoleDivice::GetInstace();
	print.printText();

	PrintConsoleDivice print1 = PrintConsoleDivice::GetInstace();
	print1.printText();

	

	system("pause");
	return 0;
}