#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward declaration
class Order;

// === Observer Interface ===
class OrderObserver {
public:
 virtual void update(Order* order) = 0;
    virtual string getName() = 0;
    virtual ~OrderObserver() {}
};

// === Subject (Observable) ===
class Order {
private:
    vector<OrderObserver*> _observers;
    string _orderId;
    string _status;
    double _amount;

public:
    Order(const string& id, double amount) 
        : _orderId(id), _amount(amount), _status("Pending") {
  cout << "Tao don hang: " << _orderId << " - " << _amount << " VND" << endl;
    }

    // Dang ky observer
    void attach(OrderObserver* observer) {
     _observers.push_back(observer);
      cout << "Da dang ky: " << observer->getName() << endl;
    }

    // Huy dang ky observer
    void detach(OrderObserver* observer) {
        for (auto it = _observers.begin(); it != _observers.end(); ++it) {
            if (*it == observer) {
 _observers.erase(it);
cout << "Da huy dang ky: " << observer->getName() << endl;
                break;
  }
    }
    }

    // Thong bao den tat ca observers
    void notify() {
        cout << "--- Thong bao den " << _observers.size() << " observers ---" << endl;
        for (auto observer : _observers) {
            observer->update(this);
        }
    }

    // Thay doi trang thai -> tu dong thong bao
    void setStatus(const string& status) {
        _status = status;
        cout << "\n[" << _orderId << "] Trang thai doi sang: " << _status << endl;
    notify();
    }

    string getOrderId() { return _orderId; }
    string getStatus() { return _status; }
    double getAmount() { return _amount; }
};

// === Concrete Observers ===

// Observer 1: Gui Email cho khach hang
class EmailNotifier : public OrderObserver {
private:
    string _email;
public:
    EmailNotifier(const string& email) : _email(email) {}

    void update(Order* order) override {
     cout << "  [EMAIL -> " << _email << "] "
  << "Don hang " << order->getOrderId() 
      << " da chuyen sang: " << order->getStatus() << endl;
    }

    string getName() override { return "EmailNotifier (" + _email + ")"; }
};

// Observer 2: Gui SMS cho khach hang
class SMSNotifier : public OrderObserver {
private:
    string _phone;
public:
    SMSNotifier(const string& phone) : _phone(phone) {}

    void update(Order* order) override {
        cout << "  [SMS -> " << _phone << "] "
   << "Don hang " << order->getOrderId() 
      << ": " << order->getStatus() << endl;
    }

    string getName() override { return "SMSNotifier (" + _phone + ")"; }
};

// Observer 3: Ghi log vao he thong
class LogNotifier : public OrderObserver {
public:
    void update(Order* order) override {
        cout << "  [LOG] Order=" << order->getOrderId()
             << ", Status=" << order->getStatus()
  << ", Amount=" << order->getAmount() << " VND" << endl;
    }

    string getName() override { return "LogNotifier"; }
};

// Observer 4: Cap nhat kho hang
class InventoryNotifier : public OrderObserver {
public:
    void update(Order* order) override {
        if (order->getStatus() == "Confirmed") {
            cout << "  [INVENTORY] Tru hang trong kho cho don " 
        << order->getOrderId() << endl;
        } else if (order->getStatus() == "Cancelled") {
    cout << "  [INVENTORY] Hoan tra hang vao kho cho don " 
      << order->getOrderId() << endl;
 } else {
    cout << "  [INVENTORY] Khong can xu ly kho cho trang thai: " 
   << order->getStatus() << endl;
        }
    }

    string getName() override { return "InventoryNotifier"; }
};

// === Client Code ===
int main() {
    cout << "============ OBSERVER PATTERN DEMO ============\n" << endl;

    // Tao don hang (Subject)
    Order* order = new Order("ORD-001", 500000);
    cout << endl;

    // Tao cac observers
    EmailNotifier* email = new EmailNotifier("khachhang@gmail.com");
    SMSNotifier* sms = new SMSNotifier("0901234567");
    LogNotifier* log = new LogNotifier();
    InventoryNotifier* inventory = new InventoryNotifier();

 // Dang ky observers vao don hang
    cout << "=== DANG KY OBSERVERS ===" << endl;
    order->attach(email);
    order->attach(sms);
    order->attach(log);
    order->attach(inventory);

    // Thay doi trang thai -> tat ca observers se nhan thong bao
    cout << "\n=== THAY DOI TRANG THAI ===" << endl;
    order->setStatus("Confirmed");   // Tat ca 4 observers nhan thong bao
    order->setStatus("Shipping");  // Tat ca 4 observers nhan thong bao
    order->setStatus("Delivered");   // Tat ca 4 observers nhan thong bao

    // Huy dang ky SMS - khong muon nhan SMS nua
  cout << "\n=== HUY DANG KY SMS ===" << endl;
    order->detach(sms);

 // Thay doi trang thai -> chi 3 observers nhan thong bao (khong co SMS)
    cout << "\n=== TIEP TUC THAY DOI ===" << endl;
    order->setStatus("Completed");

    // Test case: Don hang bi huy
    cout << "\n=== TEST DON HANG MOI BI HUY ===" << endl;
    Order* order2 = new Order("ORD-002", 300000);
    order2->attach(email);
    order2->attach(inventory);
    order2->setStatus("Confirmed");
    order2->setStatus("Cancelled");  // Inventory se hoan tra hang

    // Giai phong bo nho
    delete order;
    delete order2;
    delete email;
    delete sms;
    delete log;
    delete inventory;

    return 0;
}
