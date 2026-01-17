#include <iostream>
#include <string>

using namespace std;

// --- Class cha: Shape ---
class Shape {
protected:
    string _name;
public:
    // Constructor mac dinh
    Shape() : _name("") {
        cout << "Shape default constructor\n";
    }

    // Constructor co tham so
    Shape(string name) : _name(name) {
        cout << "Shape parameter constructor\n";
    }

    // Destructor ao (quan trong de xoa dung lop con)
    virtual ~Shape() {
        cout << "Shape destructor\n";
    }

    // Ham thuan ao
    virtual double area() = 0;

    // Ham ao hien thi
    virtual void display() {
        cout << _name << endl;
    }
};

// --- Class thanh phan: Point ---
class Point {
    int _x, _y;
public:
    // Constructor (mac dinh hoac co tham so)
    Point(int x = 0, int y = 0) : _x(x), _y(y) {
        cout << "Point constructor\n";
    }

    // Copy Constructor
    Point(const Point& p) {
        _x = p._x;
        _y = p._y;
        cout << "Point copy constructor\n";
    }

    ~Point() { cout << "Point destructor\n"; }
};

// --- Class con: Rectangle ---
class Rectangle : public Shape {
    Point _topLeft;
    int _width, _height;
public:
    // Constructor
    Rectangle(const Point& p, int w, int h)
        : Shape("Rectangle"), _topLeft(p), _width(w), _height(h) {
        // Luu y: _topLeft(p) se goi Copy Constructor cua Point
        cout << "Rectangle constructor\n";
    }

    // Copy Constructor (DAY LA CHO "GAY CAN" NHAT)
    Rectangle(const Rectangle& p) {
        // Vi khong co "Initializer List" goi Shape(p) hay _topLeft(p) o tren nay...
        // ...nen trinh bien dich se tu dong goi:
        // 1. Shape default constructor ("Shape default constructor")
        // 2. Point default constructor ("Point constructor")
        // Sau do moi chay vao than ham duoi day:

        cout << "Rectangle copy constructor\n";
        _name = p._name;
        _width = p._width;
        _height = p._height;
        _topLeft = p._topLeft; // Gan gia tri lai (operator=)
    }

    double area() override {
        return _width * _height;
    }

    void display() override {
        // Goi ham area() cua chinh no
        cout << _name << ": " << area() << endl;
    }

    ~Rectangle() {
        cout << "Rectangle destructor\n";
    }
};

// --- Ham Main ---
int main() {
    // 1. Tao rec1:
    // - Tao Point tam thoi (1, 2)
    // - Goi Rectangle Constructor
    // - Xoa Point tam thoi
    cout << "--- Tao rec1 ---\n";
    Rectangle rec1(Point(1, 2), 4, 5);

    // 2. Tao con tro s tu rec1 (Goi Copy Constructor):
    // - O day se goi Shape Default Ctor va Point Default Ctor (do code thieu init list)
    cout << "\n--- Tao s tu rec1 ---\n";
    Shape* s = new Rectangle(rec1);

    // 3. Goi ham display (da hinh):
    cout << "\n--- Goi display ---\n";
    s->display();

    // 4. Xoa con tro s:
    // - Goi Rectangle Destructor -> Point Destructor -> Shape Destructor
    cout << "\n--- Delete s ---\n";
    delete s;
}