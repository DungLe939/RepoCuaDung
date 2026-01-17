#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// ============= STRATEGY PATTERN: Number Formatting =============

// Interface cho MoneyFormatter (Strategy)
class MoneyFormatter {
public:
    virtual ~MoneyFormatter() {}
    virtual string format(int amount) = 0;
};

// Formatter với dấu chấm phân cách
class DotSeparatorFormatter : public MoneyFormatter {
public:
    string format(int amount) override {
        string result = to_string(amount);
        int insertPosition = result.length() - 3;
        
        while (insertPosition > 0) {
            result.insert(insertPosition, ".");
            insertPosition -= 3;
        }
        
        return result;
    }
};

// Formatter với dấu phẩy phân cách
class CommaSeparatorFormatter : public MoneyFormatter {
public:
    string format(int amount) override {
        string result = to_string(amount);
        int insertPosition = result.length() - 3;
        
        while (insertPosition > 0) {
            result.insert(insertPosition, ","); 
            insertPosition -= 3;
        }
        
        return result;
    }
};

// Formatter không có phân cách (mặc định)
class NoSeparatorFormatter : public MoneyFormatter {
public:
    string format(int amount) override {
        return to_string(amount);
    }
};

// ============= DECORATOR PATTERN: Currency Symbol =============

// Abstract Decorator - cũng implement MoneyFormatter để có thể wrap
class CurrencyDecorator : public MoneyFormatter {
protected:
    MoneyFormatter* wrappedFormatter;  // Component được wrap
    
public:
    CurrencyDecorator(MoneyFormatter* formatter) 
        : wrappedFormatter(formatter) {}
    
    virtual ~CurrencyDecorator() {
        // Không delete wrappedFormatter vì có thể được quản lý ở nơi khác
    }
    
    // Pure virtual - concrete decorator phải implement
    virtual string format(int amount) = 0;
};

// Concrete Decorator cho VND
class VNDDecorator : public CurrencyDecorator {
public:
    VNDDecorator(MoneyFormatter* formatter) 
        : CurrencyDecorator(formatter) {}
    
    string format(int amount) override {
        // Delegate việc format số cho wrapped formatter
        string numberPart = wrappedFormatter->format(amount);
        
        // Decorate: Thêm ký hiệu VND vào cuối
        return numberPart + " vnd";
    }
};

// Concrete Decorator cho USD
class USDDecorator : public CurrencyDecorator {
public:
    USDDecorator(MoneyFormatter* formatter) 
        : CurrencyDecorator(formatter) {}
    
    string format(int amount) override {
        // Delegate việc format số cho wrapped formatter
        string numberPart = wrappedFormatter->format(amount);
        
        // Decorate: Thêm ký hiệu USD vào đầu
        return "$ " + numberPart;
    }
};

// Concrete Decorator cho EUR (bonus - mở rộng)
class EURDecorator : public CurrencyDecorator {
public:
    EURDecorator(MoneyFormatter* formatter) 
        : CurrencyDecorator(formatter) {}
    
    string format(int amount) override {
        string numberPart = wrappedFormatter->format(amount);
        return numberPart + " €";
    }
};

// ============= PROJECT HIERARCHY =============

// Struct moi de chua goi tai tro phuc hop
class FundingPackage {
    long long vndAmount;    // Tien phap dinh
    double cryptoAmount;    // Tien ma hoa
    string officeAddress;   // Dia chi van phong
    string roomName;        // Ten phong

    // Constructor tien loi
    FundingPackage(long long vnd, double crypto, string address, string room)
        : vndAmount(vnd), cryptoAmount(crypto), officeAddress(address), roomName(room) {
    }
};

// Lớp cơ sở Project
class Project {
protected:
    string name;
public:
    static MoneyFormatter* formatter;  // <-- Change 'protected' to 'public'
    
public:
    Project(string projectName) : name(projectName) {}
    virtual ~Project() {}
    
    virtual int grantMoney() = 0;
    virtual void print() = 0;
    
    // Thiết lập formatter chung (có thể là base strategy hoặc decorator)
    static void setFormatter(MoneyFormatter* fmt) {
        formatter = fmt;
    }
    
    // Format số tiền
    string formatMoney(int amount) {
        if (formatter == nullptr) {
            return to_string(amount);
        }
        return formatter->format(amount);
    }
};

// Lớp Idea
class Idea : public Project {
private:
    int developMonths;
    static const int MONEY_PER_MONTH = 20000000;
    
public:
    Idea(string projectName, int months) 
        : Project(projectName), developMonths(months) {}
    
    int grantMoney() override {
        return developMonths * MONEY_PER_MONTH;
    }
    
    void print() override {
        cout << "Y tuong: " << name 
             << ". Phat trien: " << developMonths << " thang"
             << ". Kinh phi: " << formatMoney(grantMoney());
    }
};

// Lớp Mvp
class Mvp : public Project {
private:
    int operationMonths;
    int marketingMonths;
    static const int MONEY_PER_MONTH = 15000000;
    
public:
    Mvp(string projectName, int opMonths, int mktMonths)
        : Project(projectName), 
          operationMonths(opMonths), 
          marketingMonths(mktMonths) {}
    
    int grantMoney() override {
        return (operationMonths + marketingMonths) * MONEY_PER_MONTH;
    }
    
    void print() override {
        cout << "San pham: " << name
             << ". Van hanh: " << operationMonths << " thang"
             << ". Marketing: " << marketingMonths << " thang"
             << ". Kinh phi: " << formatMoney(grantMoney());
    }
};

// Khởi tạo static member - mặc định VND với dấu chấm
MoneyFormatter* Project::formatter = new VNDDecorator(new DotSeparatorFormatter());

// ============= MAIN PROGRAM =============

int main()
{
    cout << "Chuong trinh ho tro Hackathon cua AlphaTech thang 6/2023" << endl;
    cout << "========================================================\n" << endl;

    vector<Project*> projects = {
        new Idea("SuperTech", 6),
        new Mvp("FutureCar", 6, 3),
        new Idea("VirtualHouse", 7),
        new Idea("NightVision", 4),
        new Mvp("SmartKey", 4, 5)
    };

    cout << "So du an: " << projects.size() << endl;
    cout << "\n--- Hien thi theo VND (dau cham) ---" << endl;

    int sum = 0;
    for (int i = 0; i < projects.size(); i++) {
        sum += projects[i]->grantMoney();
        cout << i + 1 << ".";
        projects[i]->print();
        cout << endl;
    }

    cout << "Tong tien tai tro: " << Project::formatter->format(sum) << endl;

    // ===== Demo: Chuyển sang USD =====
    cout << "\n--- Chuyen sang USD (dau phay) ---" << endl;
    Project::setFormatter(new USDDecorator(new CommaSeparatorFormatter()));

    for (int i = 0; i < projects.size(); i++) {
        cout << i + 1 << ".";
        projects[i]->print();
        cout << endl;
    }
    cout << "Tong tien tai tro: " << Project::formatter->format(sum) << endl;

    // ===== Demo: VND không có dấu phân cách =====
    cout << "\n--- VND khong phan cach (test) ---" << endl;
    Project::setFormatter(new VNDDecorator(new NoSeparatorFormatter()));

    for (int i = 0; i < projects.size(); i++) {
        cout << i + 1 << ".";
        projects[i]->print();
        cout << endl;
    }
    cout << "Tong tien tai tro: " << Project::formatter->format(sum) << endl;

    // ===== Demo: EUR với dấu chấm =====
    cout << "\n--- EUR (dau cham) ---" << endl;
    Project::setFormatter(new EURDecorator(new DotSeparatorFormatter()));

    for (int i = 0; i < projects.size(); i++) {
        cout << i + 1 << ".";
        projects[i]->print();
        cout << endl;
    }
    cout << "Tong tien tai tro: " << Project::formatter->format(sum) << endl;

    // Cleanup (bỏ qua tiềm ẩn rò rỉ vùng nhớ như yêu cầu đề bài)
    for (auto project : projects) {
        delete project;
    }

    return 0;
}

//Chương trình hỗ trợ Hackathon của AlphaTech tháng 6 / 2023
//Số dự án : 5
//1. Ý tưởng : SuperTech.Phát triển : 6 tháng.Kinh phí : 120.000.000 đ
//2. Sản phẩm : FutureCar.Vận hành : 6 tháng.Marketing : 3 tháng.Kinh phí : 135.000.000 đ
//3. Ý tưởng : VirtualHouse.Phát triển : 7 tháng.Kinh phí : 140.000.000 đ
//4. Ý tưởng : NightVision.Phát triển : 4 tháng.Kinh phí : 80.000.000 đ
//5. Sản phẩm : SmartKey.Vận hành : 4 tháng.Marketing : 5 tháng.Kinh phí : 135.000.000 đ
//Tổng tiền tài trợ : 610.000.000 đ
