#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Forward declarations
class Idea;
class Mvp;

// ==================== IFormatter Interface ====================
class IFormatter {
public:
	virtual string format(int money) = 0;
	virtual ~IFormatter() {}
};

// ==================== Concrete Formatters ====================
class DotFormat : public IFormatter {
public:
	string format(int money) override {
		string str = to_string(money);
		string result;
		int count = 0;
		for (int i = (int)str.length() - 1; i >= 0; i--) {
			if (count > 0 && count % 3 == 0) {
				result = "." + result;
			}
			result = str[i] + result;
			count++;
		}
		return result;
	}
};

class CommaFormat : public IFormatter {
public:
	string format(int money) override {
		string str = to_string(money);
		string result;
		int count = 0;
		for (int i = (int)str.length() - 1; i >= 0; i--) {
			if (count > 0 && count % 3 == 0) {
				result = "," + result;
			}
			result = str[i] + result;
			count++;
		}
		return result;
	}
};

// ==================== Currency Decorator ====================
class CurDecorator : public IFormatter {
protected:
	IFormatter* formatter;
public:
	CurDecorator(IFormatter* f) : formatter(f) {}
	virtual string format(int money) override = 0;
	virtual ~CurDecorator() { delete formatter; }
};

class VNDeco : public CurDecorator {
public:
	VNDeco(IFormatter* f) : CurDecorator(f) {}
	string format(int money) override {
		return formatter->format(money) + " d";
	}
};

class USDDeco : public CurDecorator {
public:
	USDDeco(IFormatter* f) : CurDecorator(f) {}
	string format(int money) override {
		return "$ " + formatter->format(money);
	}
};

// ==================== Visitor Interface ====================
class Visitor {
public:
	virtual void visit(Idea* idea) = 0;
	virtual void visit(Mvp* mvp) = 0;
	virtual ~Visitor() {}
};

// ==================== Project Abstract Class ====================
class Project {
protected:
	string name;
	IFormatter* formatter;
public:
	Project(string n, IFormatter* f = nullptr) : name(n), formatter(f) {}

	void setFormatter(IFormatter* f) { 
		delete formatter; 
		formatter = f; 
	}
	
	string getName() { return name; }
	IFormatter* getFormatter() { return formatter; }

	virtual void accept(Visitor* v) = 0;
	virtual int grandMoney() = 0;
	virtual void print() = 0;
	virtual ~Project() { delete formatter; }
};

// ==================== Idea Class ====================
class Idea : public Project {
private:
	static int taitro;
	int thang;
public:
	Idea(int t, string n, IFormatter* f = nullptr) : Project(n, f), thang(t) {}

	int getThang() { return thang; }

	int grandMoney() override {
		return thang * taitro;
	}

	void accept(Visitor* v) override {
		v->visit(this);
	}

	void print() override {
		// Default print without visitor
		cout << "Y tuong: " << name << ". Phat trien: " << thang << " thang. Kinh phi: ";
		if (formatter)
			cout << formatter->format(grandMoney());
		else
			cout << grandMoney();
		cout << endl;
	}

	static void setTaitro(int t) { taitro = t; }
	static int getTaitro() { return taitro; }
};
int Idea::taitro = 20000000;

// ==================== Mvp Class ====================
class Mvp : public Project {
private:
	static int taitroMar;
	int thangMar;
	static int taitroOpe;
	int thangOpe;
public:
	Mvp(int tOpe, int tMar, string n, IFormatter* f = nullptr) : Project(n, f), thangOpe(tOpe), thangMar(tMar) {}

	int getThangOpe() { return thangOpe; }
	int getThangMar() { return thangMar; }

	int grandMoney() override {
		return thangOpe * taitroOpe + thangMar * taitroMar;
	}

	void accept(Visitor* v) override {
		v->visit(this);
	}

	void print() override {
		// Default print without visitor
		cout << "San pham: " << name << ". Van hanh: " << thangOpe 
			 << " thang. Marketing: " << thangMar << " thang. Kinh phi: ";
		if (formatter)
			cout << formatter->format(grandMoney());
		else
			cout << grandMoney();
		cout << endl;
	}

	static void setTaitroMar(int t) { taitroMar = t; }
	static void setTaitroOpe(int t) { taitroOpe = t; }
};
int Mvp::taitroMar = 5000000;
int Mvp::taitroOpe = 20000000;

// ==================== Concrete Visitors ====================
class NormalPrint : public Visitor {
public:
	void visit(Idea* idea) override {
		cout << "Y tuong: " << idea->getName()
			<< ". Phat trien: " << idea->getThang() << " thang. Kinh phi: ";
		if (idea->getFormatter())
			cout << idea->getFormatter()->format(idea->grandMoney());
		else
			cout << idea->grandMoney();
		cout << endl;
	}

	void visit(Mvp* mvp) override {
		cout << "San pham: " << mvp->getName()
			<< ". Van hanh: " << mvp->getThangOpe() << " thang. Marketing: "
			<< mvp->getThangMar() << " thang. Kinh phi: ";
		if (mvp->getFormatter())
			cout << mvp->getFormatter()->format(mvp->grandMoney());
		else
			cout << mvp->grandMoney();
		cout << endl;
	}
};

class TablePrint : public Visitor {
public:
	void visit(Idea* idea) override {
		cout << left << setw(12) << "Y tuong"
			<< setw(15) << idea->getName()
			<< "Phat trien: " << idea->getThang() << " thang"
			<< setw(20) << " ";
		if (idea->getFormatter())
			cout << idea->getFormatter()->format(idea->grandMoney());
		else
			cout << idea->grandMoney();
		cout << endl;
	}

	void visit(Mvp* mvp) override {
		cout << left << setw(12) << "San pham"
			<< setw(15) << mvp->getName()
			<< "Van hanh: " << mvp->getThangOpe() << " thang. Marketing: "
			<< mvp->getThangMar() << " thang. ";
		if (mvp->getFormatter())
			cout << mvp->getFormatter()->format(mvp->grandMoney());
		else
			cout << mvp->grandMoney();
		cout << endl;
	}
};

// ==================== Main Function ====================
int main() {
	vector<Project*> projects;

	NormalPrint* normalPrinter = new NormalPrint();
	TablePrint* tablePrinter = new TablePrint();

	// ==================== Test 1: Basic with DotFormat ====================
	cout << "========== TEST 1: DotFormat (Basic) ==========" << endl;
	projects.push_back(new Idea(6, "SuperTech", new DotFormat()));
	projects.push_back(new Mvp(6, 3, "FutureCar", new DotFormat()));
	projects.push_back(new Idea(7, "VirtualHouse", new DotFormat()));
	projects.push_back(new Idea(4, "NightVision", new DotFormat()));
	projects.push_back(new Mvp(4, 5, "SmartKey", new DotFormat()));

	cout << "Chuong trinh ho tro Hackathon cua AlphaTech thang 6/2023" << endl;
	cout << "So du an: " << projects.size() << endl;

	int sum = 0;
	int i = 1;
	for (Project* p : projects) {
		cout << i++ << ". ";
		p->accept(normalPrinter);  // Using accept() instead of setPrinter + print
		sum += p->grandMoney();
	}
	cout << "Tong tien tai tro: " << sum << endl;

	// Cleanup test 1
	for (Project* p : projects) delete p;
	projects.clear();

	// ==================== Test 2: CommaFormat ====================
	cout << "\n========== TEST 2: CommaFormat ==========" << endl;
	projects.push_back(new Idea(6, "SuperTech", new CommaFormat()));
	projects.push_back(new Mvp(6, 3, "FutureCar", new CommaFormat()));

	for (Project* p : projects) {
		p->accept(normalPrinter);
	}

	for (Project* p : projects) delete p;
	projects.clear();

	// ==================== Test 3: VND Decorator with DotFormat ====================
	cout << "\n========== TEST 3: VND Currency (DotFormat + VNDeco) ==========" << endl;
	projects.push_back(new Idea(6, "SuperTech", new VNDeco(new DotFormat())));
	projects.push_back(new Mvp(6, 3, "FutureCar", new VNDeco(new DotFormat())));
	projects.push_back(new Idea(7, "VirtualHouse", new VNDeco(new DotFormat())));

	for (Project* p : projects) {
		p->accept(normalPrinter);
	}

	for (Project* p : projects) delete p;
	projects.clear();

	// ==================== Test 4: USD Decorator with CommaFormat ====================
	cout << "\n========== TEST 4: USD Currency (CommaFormat + USDDeco) ==========" << endl;
	projects.push_back(new Idea(6, "SuperTech", new USDDeco(new CommaFormat())));
	projects.push_back(new Mvp(6, 3, "FutureCar", new USDDeco(new CommaFormat())));
	projects.push_back(new Idea(4, "NightVision", new USDDeco(new CommaFormat())));

	for (Project* p : projects) {
		p->accept(normalPrinter);
	}

	for (Project* p : projects) delete p;
	projects.clear();

	// ==================== Test 5: TablePrint format ====================
	cout << "\n========== TEST 5: Table Format (VND) ==========" << endl;
	cout << left << setw(12) << "Loai du an" << setw(15) << "Ten du an"
		 << setw(40) << "Thong tin" << "Kinh phi" << endl;
	cout << string(80, '-') << endl;

	projects.push_back(new Idea(6, "SuperTech", new VNDeco(new DotFormat())));
	projects.push_back(new Mvp(6, 3, "FutureCar", new VNDeco(new DotFormat())));
	projects.push_back(new Idea(7, "VirtualHouse", new VNDeco(new DotFormat())));
	projects.push_back(new Idea(4, "NightVision", new VNDeco(new DotFormat())));
	projects.push_back(new Mvp(4, 5, "SmartKey", new VNDeco(new DotFormat())));

	for (Project* p : projects) {
		p->accept(tablePrinter);
	}

	for (Project* p : projects) delete p;
	projects.clear();

	// ==================== Test 6: No Formatter (raw numbers) ====================
	cout << "\n========== TEST 6: No Formatter (Raw Numbers) ==========" << endl;
	projects.push_back(new Idea(6, "SuperTech"));
	projects.push_back(new Mvp(6, 3, "FutureCar"));

	for (Project* p : projects) {
		p->accept(normalPrinter);
	}

	for (Project* p : projects) delete p;
	projects.clear();

	// ==================== Test 7: Using setFormatter() to change formatter ====================
	cout << "\n========== TEST 7: Using setFormatter() ==========" << endl;
	Idea* project1 = new Idea(6, "DynamicProject");
	
	cout << "Before setFormatter (raw): ";
	project1->print();
	
	project1->setFormatter(new VNDeco(new DotFormat()));
	cout << "After setFormatter (VND): ";
	project1->print();
	
	project1->setFormatter(new USDDeco(new CommaFormat()));
	cout << "After setFormatter (USD): ";
	project1->print();
	
	delete project1;

	// ==================== Test 8: Change static taitro values ====================
	cout << "\n========== TEST 8: Modified Grant Rates ==========" << endl;
	cout << "Setting Idea taitro = 25,000,000 and Mvp taitroOpe = 25,000,000" << endl;
	
	Idea::setTaitro(25000000);
	Mvp::setTaitroOpe(25000000);
	Mvp::setTaitroMar(7000000);

	projects.push_back(new Idea(6, "SuperTech", new VNDeco(new DotFormat())));
	projects.push_back(new Mvp(6, 3, "FutureCar", new VNDeco(new DotFormat())));

	for (Project* p : projects) {
		p->accept(normalPrinter);
	}

	// Final cleanup
	for (Project* p : projects) delete p;
	delete normalPrinter;
	delete tablePrinter;

	return 0;
}
