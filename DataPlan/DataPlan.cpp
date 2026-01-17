#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

class HopDong {
protected:
	char* userName;
	char* cmnd;
	char* address;

	int ThoiGianGoi;
	int MB;
	static int DonGiaGoi;
	static int DonGiaTruyCap;
	static double VAT;
public:
	static void setValue(int a, int b, double c) {
		DonGiaGoi = a;
		DonGiaTruyCap = b;
		VAT = c / 100;
	}
	HopDong(const char* a = "Unknown", const char* b = "Unknown", const char* c = "Unknown", int time = 0, int mb = 0) {
		userName = new char[strlen(a) + 1];
		strcpy(userName, a);
		cmnd = new char[strlen(b) + 1];
		strcpy(cmnd, b);
		address = new char[strlen(c) + 1];
		strcpy(address, c);
		ThoiGianGoi = time;
		MB = mb;
	}
	virtual long long ThanhTien() = 0;
	virtual void Xuat() {
		cout << "User Name: " << userName << endl;
		cout << "CMND: " << cmnd << endl;
		cout << "Address: " << address << endl;
	}
	virtual ~HopDong() {
		delete[] userName;
		delete[] cmnd;
		delete[] address;
		MB = ThoiGianGoi = 0;
	}
};
class Basic : public HopDong {
public:
	Basic(const char* a = "Unknown", const char* b = "Unknown", const char* c = "Unknown", int time = 0, int mb = 0) : HopDong(a, b, c, time, mb) {
	}
	long long ThanhTien() override {
		int CuocDienThoai = ThoiGianGoi * DonGiaGoi;
		int CuocInternet = MB * DonGiaTruyCap;
		long long All = CuocDienThoai + CuocInternet + ((CuocDienThoai + CuocInternet) * VAT);
		return All;
	}
	void Xuat() override {
		HopDong::Xuat();
		cout << "Ban dang su dung goi: Basic" << endl;
		cout << "Tong tien: " << ThanhTien() << endl << endl;
	}
};
class DataFree : public HopDong {
protected:
	int NguongFreeData;
public:
	DataFree(const char* a = "Unknown", const char* b = "Unknown", const char* c = "Unknown", int time = 0, int mb = 0, int freeData = 0) : HopDong(a, b, c, time, mb) {
		NguongFreeData = freeData;
	}
	long long ThanhTien() override {
		int CuocDienThoai = ThoiGianGoi * DonGiaGoi;
		int CuocInternet;
		if (MB <= NguongFreeData) {
			CuocInternet = 0;
		}
		else {
			CuocInternet = (MB - NguongFreeData) * DonGiaTruyCap;
		}
		long long All = CuocDienThoai + CuocInternet + ((CuocDienThoai + CuocInternet) * VAT);
		return All;
	}
	void Xuat() override {
		HopDong::Xuat();
		cout << "Ban dang su dung goi: Data Free" << endl;
		cout << "Tong tien: " << ThanhTien() << endl << endl;
	}
};
class DataFix : public HopDong {
public:
	DataFix(const char* a = "Unknown", const char* b = "Unknown", const char* c = "Unknown", int time = 0, int mb = 0) : HopDong(a, b, c, time, mb) {
	}
	long long ThanhTien() override {
		int CuocDienThoai = (ThoiGianGoi * DonGiaGoi) * 90 / 100;
		int CuocInternet = 1000000;
		long long All = CuocDienThoai + CuocInternet + ((CuocDienThoai + CuocInternet) * VAT);
		return All;
	}
	void Xuat() override {
		HopDong::Xuat();
		cout << "Ban dang su dung goi: Data Fix" << endl;
		cout << "Tong tien: " << ThanhTien() << endl << endl;
	}
};

class CongTy {
private:
	vector<HopDong*> arr;
public:
	void addHopDong(HopDong* a) {
		arr.push_back(a);
	}
	void ThongBao() {
		cout << "=====BANG IN THONG BAO TIEN CUA TAT CA USER=====" << endl;
		for (int i = 0; i < arr.size(); i++) {
			arr[i]->Xuat();
			cout << "================================================" << endl;
		}
	}
	~CongTy() {
		for (auto x : arr) {
			delete x;
		}
		arr.clear();
	}
};

int HopDong::DonGiaGoi = 0; // khoi tao mac dinh
int HopDong::DonGiaTruyCap = 0; // khoi tao mac dinh
double HopDong::VAT = 0.0; // khoi tao mac dinh

void loadFile(ifstream& fi) {
	char tmp[101];
	int a = 0, b = 0, c = 0;
	while (fi.getline(tmp, 101)) {
		char* key = strtok(tmp, "=");
		char* val = strtok(NULL, "=");
		if (strcmp(key, "DonGiaGoi") == 0) {
			a = atoi(val);
		}
		else if (strcmp(key, "DonGiaTruyCap") == 0) {
			b = atoi(val);
		}
		else if (strcmp(key, "VAT") == 0) {
			c = atof(val);
		}
	}
	HopDong::setValue(a, b, c);
}
void menu() {
	cout << "\n===== MENU QUAN LY HOP DONG =====\n" << endl;
	cout << "1. Them hop dong Basic" << endl;
	cout << "2. Them hop dong Data Free" << endl;
	cout << "3. Them hop dong Data Fix" << endl;
	cout << "4. In thong bao tat ca hop dong" << endl;
	cout << "0. Thoat chuong trinh" << endl;
	cout << "Chon: ";
}
int main() {
	ifstream fi("data.txt");
	loadFile(fi);
	fi.close();

	CongTy congty;
	int choice;

	do {
		menu();
		cin >> choice;
		cin.ignore();

		char name[101], cmnd[101], addr[101];
		int time, mb;
		int freeData = 0;

		if (choice == 1) {
			// them hop dong Basic
			cout << "Nhap ten nguoi dung: "; cin.getline(name, 101);
			cout << "Nhap CMND: "; cin.getline(cmnd, 101);
			cout << "Nhap dia chi: "; cin.getline(addr, 101);
			cout << "Nhap thoi gian goi (phut): "; cin >> time;
			cout << "Nhap dung luong su dung (MB): "; cin >> mb;
			congty.addHopDong(new Basic(name, cmnd, addr, time, mb));
			cout << "==> Da them hop dong Basic thanh cong!" << endl;
			cin.ignore();
		}
		else if (choice == 2) {
			// them hop dong Data Free
			cout << "Nhap ten nguoi dung: "; cin.getline(name, 101);
			cout << "Nhap CMND: "; cin.getline(cmnd, 101);
			cout << "Nhap dia chi: "; cin.getline(addr, 101);
			cout << "Nhap thoi gian goi (phut): "; cin >> time;
			cout << "Nhap dung luong su dung (MB): "; cin >> mb;
			cout << "Nhap luong luong data mien phi (freeData): ";
			cin >> freeData;
			congty.addHopDong(new DataFree(name, cmnd, addr, time, mb, freeData));
			cout << "==> Da them hop dong Data Free thanh cong!" << endl;
			cin.ignore();
		}
		else if (choice == 3) {
			cout << "Nhap ten nguoi dung: "; cin.getline(name, 101);
			cout << "Nhap CMND: "; cin.getline(cmnd, 101);
			cout << "Nhap dia chi: "; cin.getline(addr, 101);
			cout << "Nhap thoi gian goi (phut): "; cin >> time;
			cout << "Nhap dung luong su dung (MB): "; cin >> mb;
			congty.addHopDong(new DataFix(name, cmnd, addr, time, mb));
			cout << "==> Da them hop dong Data Fix thanh cong!" << endl;
			cin.ignore();
		}
		else if (choice == 4) {
			congty.ThongBao();
		}
		else if (choice == 0) {
			cout << "Thoat chuong trinh..." << endl;
			return 0;
		}
		else {
			cout << "Lua chon khong hop le!" << endl;
		}
		system("pause");
		system("cls");
	} while (choice != 0);

	return 0;
}