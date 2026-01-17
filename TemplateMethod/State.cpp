#include <iostream>
using namespace std;

// Forward declaration
class Document;

// === Abstract State ===
class DocumentState {
public:
    virtual void publish(Document* doc) = 0;
    virtual void reject(Document* doc) = 0;
    virtual string getName() = 0;
    virtual ~DocumentState() {}
};

// === Context ===
class Document {
private:
    DocumentState* _state;
    string _content;
public:
    Document(const string& content);
    ~Document();
    
    void setState(DocumentState* state) {
        delete _state;
        _state = state;
        cout << "Trang thai chuyen sang: " << _state->getName() << endl;
    }
    
    void publish() { _state->publish(this); }
    void reject() { _state->reject(this); }
    string getContent() { return _content; }
};

// === Concrete States ===
class DraftState : public DocumentState {
public:
    void publish(Document* doc) override;
    void reject(Document* doc) override {
        cout << "Khong the tu choi ban nhap." << endl;
    }
    string getName() override { return "Draft"; }
};

class ModerationState : public DocumentState {
public:
    void publish(Document* doc) override;
    void reject(Document* doc) override;
    string getName() override { return "Moderation"; }
};

class PublishedState : public DocumentState {
public:
    void publish(Document* doc) override {
        cout << "Da xuat ban roi, khong can lam gi." << endl;
    }
    void reject(Document* doc) override;
    string getName() override { return "Published"; }
};

class RejectedState : public DocumentState {
public:
    void publish(Document* doc) override;
    void reject(Document* doc) override {
        cout << "Da bi tu choi roi." << endl;
    }
    string getName() override { return "Rejected"; }
};

// === Implementation ===
Document::Document(const string& content) : _content(content) {
    _state = new DraftState();
    cout << "Tao document voi trang thai: " << _state->getName() << endl;
}

Document::~Document() { delete _state; }

void DraftState::publish(Document* doc) {
    cout << "Gui de kiem duyet..." << endl;
    doc->setState(new ModerationState());
}

void ModerationState::publish(Document* doc) {
    cout << "Duyet thanh cong! Xuat ban..." << endl;
    doc->setState(new PublishedState());
}

void ModerationState::reject(Document* doc) {
    cout << "Bi tu choi!" << endl;
    doc->setState(new RejectedState());
}

void PublishedState::reject(Document* doc) {
    cout << "Go bai viet xuong..." << endl;
    doc->setState(new DraftState());
}

void RejectedState::publish(Document* doc) {
    cout << "Gui lai de kiem duyet..." << endl;
    doc->setState(new ModerationState());
}

// === Client Code ===
//int main() {
//    Document* doc = new Document("Noi dung bai viet");
//
//    cout << "\n--- Quy trinh duyet bai ---" << endl;
//    doc->publish();  // Draft -> Moderation
//    doc->publish();  // Moderation -> Published
//    doc->publish();  // Da published roi
//
//    cout << "\n--- Thu reject ---" << endl;
//    doc->reject();   // Published -> Draft
//    doc->publish();  // Draft -> Moderation
//    doc->reject();   // Moderation -> Rejected
//    doc->publish();  // Rejected -> Moderation
//
//    delete doc;
//    return 0;
//}