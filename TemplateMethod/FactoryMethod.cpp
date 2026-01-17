#include <iostream>
#include <string>
using namespace std;

// === Abstract Product ===
class Report {
public:
    virtual void generate() = 0;
    virtual ~Report() {}
};

// === Concrete Products ===
class PDFReport : public Report {
public:
    void generate() override {
        cout << "=== PDF Report ===" << endl;
    }
};

class HTMLReport : public Report {
public:
    void generate() override {
        cout << "<html>HTML Report</html>" << endl;
    }
};

class CSVReport : public Report {
public:
    void generate() override {
        cout << "ID,Name,Value (CSV)" << endl;
    }
};

// === Simple Factory ===
class ReportFactory {
public:
    // Static method - khong can tao instance cua factory
    static Report* createReport(const string& type) {
        if (type == "pdf") {
            return new PDFReport();
        } else if (type == "html") {
            return new HTMLReport();
        } else if (type == "csv") {
            return new CSVReport();
        }
        return nullptr;
    }
};

//// === Client Code ===
//int main() {
//        // Su dung rat don gian - chi can goi static method
//        Report* pdf = ReportFactory::createReport("pdf");
//        if (pdf) {
//            pdf->generate();
//            delete pdf;
//        }
//
//        Report* html = ReportFactory::createReport("html");
//        if (html) {
//            html->generate();
//            delete html;
//        }
//
//        // Co the lay type tu input
//        string userChoice = "csv";
//        Report* report = ReportFactory::createReport(userChoice);
//        if (report) {
//            report->generate();
//            delete report;
//        }
//
//    return 0;
//}