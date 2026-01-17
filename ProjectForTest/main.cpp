#include <iostream>
#include <string>
#include <thread> // Dung de gia lap delay
#include <chrono>

using namespace std;

// 1. Interface chung
class IDatabase {
public:
    virtual string getData(string query) = 0;
    virtual ~IDatabase() = default;
};

// 2. Real Subject - Gia lap Database cham chap
class RealDatabase : public IDatabase {
public:
    string getData(string query) override {
        // comment: gia lap viec truy van rat lau, mat 2 giay
        cout << "[RealDatabase] Dang truy van du lieu tu server cho: " << query << "..." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return "Ket qua cua " + query;
    }
};

// 3. Caching Proxy - Co kha nang nho ket qua
class CachedDatabaseProxy : public IDatabase {
private:
    RealDatabase* realDb;
    string cachedResult; // Bien luu tru ket qua (Cache)
    string cachedQuery;  // Luu lai xem lan truoc hoi cai gi

public:
    CachedDatabaseProxy() {
        realDb = new RealDatabase();
        cachedResult = "";
        cachedQuery = "";
    }

    ~CachedDatabaseProxy() {
        delete realDb;
    }

    string getData(string query) override {
        // comment: kiem tra xem yeu cau nay co giong yeu cau truoc do khong va da co ket qua chua
        if (query == cachedQuery && !cachedResult.empty()) {
            cout << "[Proxy] Phat hien request giong nhau -> Tra ve cache (Khong goi Real DB)" << endl;
            return cachedResult;
        }

        // comment: neu la request moi, buoc phai goi Real DB
        cachedQuery = query;
        cachedResult = realDb->getData(query);
        return cachedResult;
    }
};

// 4. Client
int main() {
    CachedDatabaseProxy proxy;

    cout << "--- User A gui request ---" << endl;
    // comment: lan dau tien, proxy phai goi vao real db (mat 2s)
    cout << "User A nhan duoc: " << proxy.getData("SELECT * FROM users") << endl;

    cout << "\n--- User B gui request y het ---" << endl;
    // comment: lan nay proxy tu tra loi luon (tuc thi)
    cout << "User B nhan duoc: " << proxy.getData("SELECT * FROM users") << endl;

    cout << "\n--- User C gui request khac ---" << endl;
    // comment: request khac nen phai goi lai real db
    cout << "User C nhan duoc: " << proxy.getData("SELECT * FROM products") << endl;

    return 0;
}