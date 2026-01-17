#include <iostream>
#include <string>
using namespace std;

// === Abstract Products (nhieu loai san pham) ===
class Report {
public:
    virtual void generate() = 0;
    virtual ~Report() {}
};

class Chart {
public:
    virtual void draw() = 0;
    virtual ~Chart() {}
};

class DataExporter {
public:
    virtual void exportData() = 0;
    virtual ~DataExporter() {}
};

// === Concrete Products - Ho PDF ===
class PDFReport : public Report {
public:
    void generate() override { cout << "[PDF] Tao bao cao PDF" << endl; }
};

class PDFChart : public Chart {
public:
    void draw() override { cout << "[PDF] Ve bieu do trong PDF" << endl; }
};

class PDFExporter : public DataExporter {
public:
    void exportData() override { cout << "[PDF] Xuat du lieu ra file PDF" << endl; }
};

// === Concrete Products - Ho HTML ===
class HTMLReport : public Report {
public:
    void generate() override { cout << "[HTML] Tao bao cao HTML" << endl; }
};

class HTMLChart : public Chart {
public:
    void draw() override { cout << "[HTML] Ve bieu do bang <canvas>" << endl; }
};

class HTMLExporter : public DataExporter {
public:
    void exportData() override { cout << "[HTML] Xuat du lieu ra trang web" << endl; }
};

// === Abstract Factory ===
class DocumentFactory {
public:
    virtual Report* createReport() = 0;
    virtual Chart* createChart() = 0;
    virtual DataExporter* createExporter() = 0;
    virtual ~DocumentFactory() {}
};

// === Concrete Factories ===
class PDFDocumentFactory : public DocumentFactory {
public:
    Report* createReport() override { return new PDFReport(); }
    Chart* createChart() override { return new PDFChart(); }
    DataExporter* createExporter() override { return new PDFExporter(); }
};

class HTMLDocumentFactory : public DocumentFactory {
public:
    Report* createReport() override { return new HTMLReport(); }
    Chart* createChart() override { return new HTMLChart(); }
    DataExporter* createExporter() override { return new HTMLExporter(); }
};

// === Client Code ===
void createDocuments(DocumentFactory* factory) {
    Report* report = factory->createReport();
    Chart* chart = factory->createChart();
    DataExporter* exporter = factory->createExporter();

    report->generate();
    chart->draw();
    exporter->exportData();

    delete report;
    delete chart;
    delete exporter;
}

int main() {
    cout << "=== Tao bo tai lieu PDF ===" << endl;
    DocumentFactory* pdfFactory = new PDFDocumentFactory();
    createDocuments(pdfFactory);
    delete pdfFactory;

    cout << "\n=== Tao bo tai lieu HTML ===" << endl;
    DocumentFactory* htmlFactory = new HTMLDocumentFactory();
    createDocuments(htmlFactory);
    delete htmlFactory;

    return 0;
}