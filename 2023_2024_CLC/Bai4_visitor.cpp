
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward declarations
class Mobile;

// ==================== Visitor Interface ====================
class IVisitor {
public:
	virtual void visit(Mobile* mobile) = 0;
	virtual ~IVisitor() {}
};

// ==================== Mobile ====================
class Mobile {
private:
	string Name;
	long long Price;
public:
	Mobile(string name, long long price) : Name(name), Price(price) {}
	
	string getName() const { return Name; }
	long long getPrice() const { return Price; }
	
	void accept(IVisitor* visitor) {
		visitor->visit(this);
	}
};

// ==================== Helper: Format Price ====================
string formatViVn(long long price) {
	string priceStr = to_string(price);
	string result = "";
	int count = 0;
	for (int i = priceStr.length() - 1; i >= 0; i--) {
		result = priceStr[i] + result;
		count++;
		if (count % 3 == 0 && i != 0) {
			result = "." + result;
		}
	}
	return result + " d";
}

string formatEnUS(long long price) {
	string priceStr = to_string(price);
	string result = "";
	int count = 0;
	for (int i = priceStr.length() - 1; i >= 0; i--) {
		result = priceStr[i] + result;
		count++;
		if (count % 3 == 0 && i != 0) {
			result = "," + result;
		}
	}
	return "VND " + result;
}

// ==================== Concrete Visitor: ViVnSimpleVisitor ====================
class ViVnSimpleVisitor : public IVisitor {
public:
	void visit(Mobile* mobile) override {
		cout << mobile->getName() << " - " << formatViVn(mobile->getPrice()) << endl;
	}
};

// ==================== Concrete Visitor: EnUSSimpleVisitor ====================
class EnUSSimpleVisitor : public IVisitor {
public:
	void visit(Mobile* mobile) override {
		cout << mobile->getName() << " - " << formatEnUS(mobile->getPrice()) << endl;
	}
};

// ==================== Concrete Visitor: ViVnTableVisitor ====================
class ViVnTableVisitor : public IVisitor {
public:
	void visit(Mobile* mobile) override {
		string nameCol = "|" + mobile->getName();
		while (nameCol.length() < 30) {
			nameCol += " ";
		}
		string priceCol = formatViVn(mobile->getPrice());
		while (priceCol.length() < 20) {
			priceCol = " " + priceCol;
		}
		cout << nameCol << "|" << priceCol << "|" << endl;
	}
};

// ==================== Concrete Visitor: EnUSTableVisitor ====================
class EnUSTableVisitor : public IVisitor {
public:
	void visit(Mobile* mobile) override {
		string nameCol = "|" + mobile->getName();
		while (nameCol.length() < 30) {
			nameCol += " ";
		}
		string priceCol = formatEnUS(mobile->getPrice());
		while (priceCol.length() < 20) {
			priceCol = " " + priceCol;
		}
		cout << nameCol << "|" << priceCol << "|" << endl;
	}
};

// ==================== Crawler ====================
class Crawler {
private:
	const char* URL;
public:
	Crawler(const char* url) : URL(url) {}
	
	vector<Mobile*> execute() {
		vector<Mobile*> tmp;
		tmp.push_back(new Mobile("iPhone 11 64GB", 8950000));
		tmp.push_back(new Mobile("iPhone 12 128GB", 12500000));
		tmp.push_back(new Mobile("iPhone 13 Pro Max 256 GB", 18990000));
		tmp.push_back(new Mobile("iPhone 14 Pro 512GB", 23790000));
		return tmp;
	}
};

// ==================== Main ====================
int main() {
	const char* url = "mobiles.com/iphone";
	Crawler* task = new Crawler(url);
	vector<Mobile*> items = task->execute();

	// ========== Test vi-VN format with Simple Layout ==========
	cout << "Sample output with vi-VN format" << endl;
	cout << "Crawled " << items.size() << " phones from " << url << endl;
	
	IVisitor* viSimpleVisitor = new ViVnSimpleVisitor();
	for (Mobile* mobile : items) {
		mobile->accept(viSimpleVisitor);
	}

	cout << endl;

	// ========== Test en-US format with Simple Layout ==========
	cout << "Sample output with en-US format" << endl;
	cout << "Crawled " << items.size() << " phones from " << url << endl;
	
	IVisitor* enSimpleVisitor = new EnUSSimpleVisitor();
	for (Mobile* mobile : items) {
		mobile->accept(enSimpleVisitor);
	}

	cout << endl;

	// ========== Test vi-VN format with Table Layout ==========
	cout << "Sample output with simple layout and vi-VN format" << endl;
	cout << "Crawled " << items.size() << " phones from " << url << endl;
	cout << "|Name        |Price               |" << endl;
	cout << "|-----------------------------|--------------------|" << endl;
	
	IVisitor* viTableVisitor = new ViVnTableVisitor();
	for (Mobile* mobile : items) {
		mobile->accept(viTableVisitor);
	}

	cout << endl;

	// ========== Test en-US format with Table Layout ==========
	cout << "Sample output with table layout and en-US format" << endl;
	cout << "Crawled " << items.size() << " phones from " << url << endl;
	cout << "|Name               |Price     |" << endl;
	cout << "|-----------------------------|--------------------|" << endl;
	
	IVisitor* enTableVisitor = new EnUSTableVisitor();
	for (Mobile* mobile : items) {
		mobile->accept(enTableVisitor);
	}

	// Cleanup
	for (Mobile* mobile : items) {
		delete mobile;
	}
	delete task;
	delete viSimpleVisitor;
	delete enSimpleVisitor;
	delete viTableVisitor;
	delete enTableVisitor;

	system("pause");
	return 0;
}
