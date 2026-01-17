#include <iostream>
#include <string>
using namespace std;

// Forward declaration
class Order;

// === Abstract State ===
class OrderState {
public:
    virtual void confirm(Order* order) = 0;
    virtual void ship(Order* order) = 0;
    virtual void deliver(Order* order) = 0;
    virtual void cancel(Order* order) = 0;
    virtual string getName() = 0;
    virtual ~OrderState() {}
};

// === Context ===
class Order {
private:
    OrderState* _state;
    string _orderId;
    double _totalAmount;

public:
    Order(const string& id, double amount);
    ~Order();

    void setState(OrderState* state) {
        delete _state;
        _state = state;
        cout << "[" << _orderId << "] Trang thai chuyen sang: " << _state->getName() << endl;
    }

    void confirm() { _state->confirm(this); }
    void ship() { _state->ship(this); }
    void deliver() { _state->deliver(this); }
    void cancel() { _state->cancel(this); }

    string getOrderId() { return _orderId; }
    double getTotalAmount() { return _totalAmount; }
    string getStateName() { return _state->getName(); }
};

// === Concrete States ===

// Trang thai: Cho xu ly
class PendingState : public OrderState {
public:
    void confirm(Order* order) override;
    void ship(Order* order) override {
        cout << "Khong the van chuyen! Don hang chua duoc xac nhan." << endl;
}
    void deliver(Order* order) override {
      cout << "Khong the giao hang! Don hang chua duoc xac nhan." << endl;
    }
    void cancel(Order* order) override;
    string getName() override { return "Pending"; }
};

// Trang thai: Da xac nhan
class ConfirmedState : public OrderState {
public:
    void confirm(Order* order) override {
      cout << "Don hang da duoc xac nhan roi!" << endl;
    }
 void ship(Order* order) override;
    void deliver(Order* order) override {
      cout << "Khong the giao hang! Don hang chua duoc van chuyen." << endl;
    }
    void cancel(Order* order) override;
    string getName() override { return "Confirmed"; }
};

// Trang thai: Dang van chuyen
class ShippingState : public OrderState {
public:
    void confirm(Order* order) override {
 cout << "Don hang da duoc xac nhan roi!" << endl;
    }
    void ship(Order* order) override {
        cout << "Don hang dang duoc van chuyen roi!" << endl;
    }
    void deliver(Order* order) override;
    void cancel(Order* order) override {
        cout << "Khong the huy! Don hang dang duoc van chuyen." << endl;
 }
    string getName() override { return "Shipping"; }
};

// Trang thai: Da giao hang
class DeliveredState : public OrderState {
public:
    void confirm(Order* order) override {
        cout << "Don hang da giao thanh cong!" << endl;
  }
    void ship(Order* order) override {
        cout << "Don hang da giao thanh cong!" << endl;
    }
    void deliver(Order* order) override {
        cout << "Don hang da giao thanh cong!" << endl;
    }
    void cancel(Order* order) override {
        cout << "Khong the huy! Don hang da giao thanh cong." << endl;
    }
    string getName() override { return "Delivered"; }
};

// Trang thai: Da huy
class CancelledState : public OrderState {
public:
    void confirm(Order* order) override {
cout << "Khong the xac nhan! Don hang da bi huy." << endl;
    }
    void ship(Order* order) override {
        cout << "Khong the van chuyen! Don hang da bi huy." << endl;
    }
    void deliver(Order* order) override {
        cout << "Khong the giao hang! Don hang da bi huy." << endl;
    }
  void cancel(Order* order) override {
        cout << "Don hang da bi huy roi!" << endl;
    }
    string getName() override { return "Cancelled"; }
};

// === Implementation ===
Order::Order(const string& id, double amount) : _orderId(id), _totalAmount(amount) {
    _state = new PendingState();
    cout << "Tao don hang " << _orderId << " voi so tien: " << _totalAmount << " VND" << endl;
    cout << "Trang thai ban dau: " << _state->getName() << endl;
}

Order::~Order() { 
    delete _state; 
}

// Pending -> Confirmed
void PendingState::confirm(Order* order) {
    cout << "Xac nhan don hang..." << endl;
    order->setState(new ConfirmedState());
}

// Pending -> Cancelled
void PendingState::cancel(Order* order) {
cout << "Huy don hang..." << endl;
    order->setState(new CancelledState());
}

// Confirmed -> Shipping
void ConfirmedState::ship(Order* order) {
 cout << "Bat dau van chuyen don hang..." << endl;
    order->setState(new ShippingState());
}

// Confirmed -> Cancelled
void ConfirmedState::cancel(Order* order) {
  cout << "Huy don hang..." << endl;
    order->setState(new CancelledState());
}

// Shipping -> Delivered
void ShippingState::deliver(Order* order) {
    cout << "Giao hang thanh cong!" << endl;
    order->setState(new DeliveredState());
}

 //=== Client Code ===
int main() {
    cout << "========== TEST CASE 1: Quy trinh binh thuong ==========" << endl;
   Order* order1 = new Order("ORD-001", 500000);
   cout << endl;

         // Confirmed -> Shipping
    order1->deliver();   // Shipping -> Delivered
    cout << "Trang thai cuoi: " << order1->getStateName() << endl;
    delete order1;

    cout << "\n========== TEST CASE 2: Huy don hang khi Pending ==========" << endl;
    Order* order2 = new Order("ORD-002", 300000);
    cout << endl;

  order2->cancel();    // Pending -> Cancelled
    order2->confirm();   // Khong the xac nhan
    cout << "Trang thai cuoi: " << order2->getStateName() << endl;
    delete order2;

    cout << "\n========== TEST CASE 3: Huy don hang khi Confirmed ==========" << endl;
    Order* order3 = new Order("ORD-003", 750000);
    cout << endl;

    order3->confirm();   // Pending -> Confirmed
    order3->cancel();    // Confirmed -> Cancelled
    cout << "Trang thai cuoi: " << order3->getStateName() << endl;
    delete order3;

    cout << "\n========== TEST CASE 4: Thu huy khi dang Shipping ==========" << endl;
    Order* order4 = new Order("ORD-004", 1000000);
    cout << endl;

    order4->confirm();   // Pending -> Confirmed
    order4->ship();      // Confirmed -> Shipping
    order4->cancel();    // Khong the huy khi dang Shipping
    order4->deliver();   // Shipping -> Delivered
    cout << "Trang thai cuoi: " << order4->getStateName() << endl;
    delete order4;

    cout << "\n========== TEST CASE 5: Thao tac khong hop le ==========" << endl;
    Order* order5 = new Order("ORD-005", 200000);
    cout << endl;

    order5->ship();      // Khong the ship khi chua confirm
    order5->deliver();   // Khong the deliver khi chua confirm
    order5->confirm();// Pending -> Confirmed
    order5->confirm();   // Da confirm roi
    cout << "Trang thai cuoi: " << order5->getStateName() << endl;
    delete order5;

    return 0;
}
