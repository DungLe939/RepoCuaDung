#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// ==================== IFormatter Interface ====================
class IFormatter {
public:
	virtual string format(long long price) = 0;
	virtual ~IFormatter() {}
};

// ==================== Strategy: ViVnFormat ====================
class ViVnFormat : public IFormatter {
public:
	string format(long long price) override {
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
};

// ==================== Strategy: enUSFormat ====================
class enUSFormat : public IFormatter {
public:
	string format(long long price) override {
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
};

// ==================== Decorator: LayoutDecorator ====================
class LayoutDecorator : public IFormatter {
protected:
	IFormatter* formatter;
public:
	LayoutDecorator(IFormatter* f) : formatter(f) {}
	virtual string format(long long price) = 0;
	virtual ~LayoutDecorator() {}
};

// ==================== SimpleLayout ====================
class SimpleLayout : public LayoutDecorator {
public:
	SimpleLayout(IFormatter* f) : LayoutDecorator(f) {}
	string format(long long price) override {
		return formatter->format(price);
	}
};

// ==================== TableLayout ====================
class TableLayout : public LayoutDecorator {
public:
	TableLayout(IFormatter* f) : LayoutDecorator(f) {}
	string format(long long price) override {
		// Format with padding for table layout
		string priceStr = formatter->format(price);
		// Add padding to align in table
		while (priceStr.length() < 20) {
			priceStr = " " + priceStr;
		}
		return "|" + priceStr + "|";
	}
};

// ==================== Mobile ====================
class Mobile {
private:
	string Name;
	long long Price;
	IFormatter* formatter;
public:
	Mobile(string name, long long price) {
		Name = name;
		Price = price;
		formatter = nullptr;
	}
	void setFormatter(IFormatter* f) {
		formatter = f;
	}
	string getName() { return Name; }
	long long getPrice() { return Price; }
	
	void print() {
		if (formatter != nullptr) {
			cout << Name << " - " << formatter->format(Price);
		}
		else {
			cout << Name << " - " << Price;
		}
	}
	
	void printTable() {
		if (formatter != nullptr) {
			// Table format with columns
			string nameCol = "|" + Name;
			while (nameCol.length() < 30) {
				nameCol += " ";
			}
			cout << nameCol << formatter->format(Price);
		}
	}
};

// ==================== Crawler ====================
class Crawler {
private:
	const char* URL;
public:
	Crawler(const char* url) {
		if (url != nullptr) {
			URL = url;
		}
	}
	vector<Mobile*> execute() {
		vector<Mobile*> tmp;
		tmp.push_back(new Mobile("iPhone 11 64GB", 8950000));
		tmp.push_back(new Mobile("iPhone 12 128GB", 12500000));
		tmp.push_back(new Mobile("iPhone 13 Pro Max 256 GB", 18990000));
		tmp.push_back(new Mobile("iPhone 14 Pro 512GB", 23790000));
		return tmp;
	}
};

//// ==================== Main ====================
//int main() {
//	const char* url = "mobiles.com/iphone";
//	Crawler* task = new Crawler(url);
//	vector<Mobile*> items = task->execute();
//
//	// ========== Test vi-VN format with SimpleLayout ==========
//	cout << "Sample output with vi-VN format" << endl;
//	cout << "Crawled " << items.size() << " phones from " << url << endl;
//	
//	IFormatter* viFormatter = new SimpleLayout(new ViVnFormat());
//	for (Mobile* mobile : items) {
//		mobile->setFormatter(viFormatter);
//		mobile->print();
//		cout << endl;
//	}
//
//	cout << endl;
//
//	// ========== Test en-US format with SimpleLayout ==========
//	cout << "Sample output with en-US format" << endl;
//	cout << "Crawled " << items.size() << " phones from " << url << endl;
//	
//	IFormatter* enFormatter = new SimpleLayout(new enUSFormat());
//	for (Mobile* mobile : items) {
//		mobile->setFormatter(enFormatter);
//		mobile->print();
//		cout << endl;
//	}
//
//	cout << endl;
//
//	// ========== Test Table Layout with en-US format ==========
//	cout << "Sample output with table layout and en-US format" << endl;
//	cout << "Crawled " << items.size() << " phones from " << url << endl;
//	cout << "|Name          |Price |" << endl;
//	cout << "|------------------------------|---------------------|" << endl;
//	
//	IFormatter* tableFormatter = new TableLayout(new enUSFormat());
//	for (Mobile* mobile : items) {
//		mobile->setFormatter(tableFormatter);
//		mobile->printTable();
//		cout << endl;
//	}
//
//	// Cleanup
//	for (Mobile* mobile : items) {
//		delete mobile;
//	}
//	delete task;
//	delete viFormatter;
//	delete enFormatter;
//	delete tableFormatter;
//
//	system("pause");
//	return 0;
//}