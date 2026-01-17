#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Bat dau xu ly voi mau strategy
class IShapeFormatter {
protected:
	char c;
public:
	virtual string toStringFormatter(int width, int height) const = 0;
};

// Solid Formatter
class SolidFormatter : public IShapeFormatter {
public:
	SolidFormatter(char tmp = '*') {
		c = tmp;
	}
	string toStringFormatter(int width, int height) const {
		string tmp = "";
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				tmp += c;
			}
			tmp += '\n';
		}
		return tmp;
	}
};

// Hallow Formatter
class HallowFormatter : public IShapeFormatter {
public:
	HallowFormatter(char tmp = '*') {
		c = tmp;
	}
	string toStringFormatter(int width, int height) const {
		string tmp = "";
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if(j == 0 || j == width - 1)
					tmp += c;
				else if (i == 0 || i == height - 1) {
					tmp += c;
				}
				else {
					tmp += ' ';
				}
			}
			tmp += '\n';
		}
		return tmp;
	}
};

// Khai bao interface
class IShape {
public:
	virtual ~IShape(){}
	virtual string toString() const = 0;
};

// Lop Rectangle
class Rectangle : public IShape {
private:
	int chieudai, chieurong;
	static IShapeFormatter* formatter;
public:
	static void setFormatter(IShapeFormatter* a) {
		if (a == nullptr) {
			throw exception("Pointer IShapeFormatter can not be nullptr");
		}
		formatter = a;
	}
	Rectangle(int a = 0, int b = 0) {
		if (a < 0 || b < 0) {
			throw exception("Invalid Number");
		}
		chieudai = a;
		chieurong = b;
	}
	string toString() const {
		//return "Rectangle Width=" + to_string(chieudai) + ", Height=" + to_string(chieurong);
		return formatter->toStringFormatter(chieudai, chieurong);
	}
};

// Lop square
class Square : public IShape {
private:
	int canh;
	static IShapeFormatter* formatter;
public:
	static void setFormatter(IShapeFormatter* a) {
		if (a == nullptr) {
			throw exception("Pointer IShapeFormatter can not be nullptr");
		}
		formatter = a;
	}
	Square(int a = 0) {
		if (a < 0) {
			throw exception("Invalid value");
		}
		canh = a;
	}
	string toString() const {
		//return "Square Side=" + to_string(canh);
		return formatter->toStringFormatter(canh, canh);
	}
};

IShapeFormatter* Rectangle::formatter = nullptr;
IShapeFormatter* Square::formatter = nullptr;

int main() {
	// set Fomatter
	HallowFormatter a('*');
	SolidFormatter b('+');

	Rectangle::setFormatter(&a);
	Square::setFormatter(&b);

	vector<IShape*> shapes = {
		new Rectangle(10, 6),
		new Square(5),
		new Rectangle(8, 5),
		new Square(3)
	};


	for (const IShape* shape : shapes) {
		cout << shape->toString() << '\n';
	
	}
	system("pause");
	return 0;
}