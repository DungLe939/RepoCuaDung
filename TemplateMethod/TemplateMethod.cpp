#include <iostream>
#include <vector>
using namespace std;

struct Record {
	int id;
	string name;
	double value;
};

// Abstract template method
class ReportGenerator {
protected:
	vector<Record> _data;
public:
	virtual ~ReportGenerator() {}
	void generateReport() {
		openConnection();
		fetchData();
		formatData();
		exportFile();
		closeConnection();
	}
	void openConnection() {
		cout << "Mo ket noi toi data base" << endl;
	}
	void fetchData() {
		cout << "Lay du lieu..." << endl;
		_data = { {1, "Product A", 100.5},
				  {2, "Product B", 200.0},
				  {3, "Product C", 150.75} };
	}
	void closeConnection() {
		cout << "Dong ket noi." << endl;
	}
	virtual void formatData() = 0;
	virtual void exportFile() = 0;
};

class PDFReport : public ReportGenerator {
public:
	void formatData() override {
		cout << "[PDF] Dinh dang du lieu: them font, can le..." << endl;
	}

	void exportFile() override {
		cout << "=== PDF Report ===" << endl;
		for (const auto& r : _data) {
			cout << "ID: " << r.id << " | Name: " << r.name
				<< " | Value: " << r.value << endl;
		}
		cout << "=== End Report ===" << endl;
	}
};

// --- Lop HTML Report ---
class HTMLReport : public ReportGenerator {
public:
	void formatData() override {
		cout << "[HTML] Dinh dang du lieu: wrap trong <table>..." << endl;
	}

	void exportFile() override {
		cout << "<html><body><table>" << endl;
		cout << "<tr><th>ID</th><th>Name</th><th>Value</th></tr>" << endl;
		for (const auto& r : _data) {
			cout << "<tr><td>" << r.id << "</td><td>" << r.name
				<< "</td><td>" << r.value << "</td></tr>" << endl;
		}
		cout << "</table></body></html>" << endl;
	}
};
// --- Lop CSV Report ---
class CSVReport : public ReportGenerator {
public:
	void formatData() override {
		cout << "[CSV] Dinh dang du lieu: phan cach bang dau phay..." << endl;
	}

	void exportFile() override {
		cout << "ID,Name,Value" << endl;
		for (const auto& r : _data) {
			cout << r.id << "," << r.name << "," << r.value << endl;
		}
	}
};

//int main() {
//	ReportGenerator* pdf = new PDFReport();
//	pdf->generateReport();
//	delete pdf;
//
//	return 0;
//}