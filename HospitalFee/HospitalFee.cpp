#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

class BenhNhan {
protected:
	char MSBN[20];
	vector<string> BenhAn;
public:
	virtual int ThanhTien() = 0;
	void printLSB() {
		cout << "Lich su benh cua benh nhan " << MSBN << " la: " << endl;
		for (auto& x : BenhAn) {
			cout << x << endl;
		}
	}
	char* getMSBN() {
		return MSBN;
	}
	virtual ~BenhNhan() = default;
};
class NgoaiTru : public BenhNhan {
private:
	int TongPhiKham;
public:
	static int cnt;
	NgoaiTru() {
		TongPhiKham = 0;
	}
	NgoaiTru(int ngay, const char* msbn, int n) : NgoaiTru() {
		TongPhiKham = n;
		strcpy(MSBN, msbn);
		cnt++;
		BenhAn.push_back(to_string(ngay) + " " + msbn + " KB " + to_string(n));
	}
	void update(int ngay, int phikham) {
		BenhAn.push_back(to_string(ngay) + " " + MSBN + " KB " + to_string(phikham));
		TongPhiKham += phikham;
	}
	int ThanhTien() override {
		return TongPhiKham;
	}
	~NgoaiTru() {
		cnt--;
	}
};
class NoiTru : public BenhNhan {
private:
	int GiaPhong;
	int PhiKham;
	int NgayNhapVien;
	int NgayXuatVien;
	bool state;
public:
	static int cnt;
	bool getState() {
		return state;
	}
	void update(int ngay, int phikham, char* loaiphong) {
		NgayNhapVien = abs(ngay);
		PhiKham = phikham;
		state = true;
		if (strcmp(loaiphong, "A") == 0) {
			GiaPhong = 1400000;
		}
		else if (strcmp(loaiphong, "B") == 0) {
			GiaPhong = 900000;
		}
		else if (strcmp(loaiphong, "C") == 0) {
			GiaPhong = 600000;
		}
	}
	NoiTru() {
		GiaPhong = PhiKham = 0;
		NgayNhapVien = -1;
		NgayXuatVien = -1;
		state = true;
	}
	NoiTru(int ngay, const char* msbn, int phikham, char* loaiphong) : NoiTru() {
		NgayNhapVien = abs(ngay);
		strcpy(MSBN, msbn);
		PhiKham = phikham;
		if (strcmp(loaiphong, "A") == 0) {
			GiaPhong = 1400000;
		}
		else if (strcmp(loaiphong, "B") == 0) {
			GiaPhong = 900000;
		}
		else if (strcmp(loaiphong, "C") == 0) {
			GiaPhong = 600000;
		}
		//Update BenhAn
		BenhAn.push_back(to_string(ngay) + " " + msbn + " " + "NV" + " " + to_string(phikham) + " " + loaiphong);
		cnt++;
	}
	~NoiTru() {
		cnt--;
	}
	void updateNhapVien(int n) {
		if (state == true) {
			return;
		}
		NgayNhapVien = n;
	}
	void updateXuatVien(int n) {
		if (state == true) {
			NgayXuatVien = n;
			BenhAn.push_back(to_string(NgayXuatVien) + " " + MSBN + " " + "XV");
			state = false;
		}
	}
	int ThanhTien() override {
		int sum = (NgayXuatVien - NgayNhapVien) * (GiaPhong + PhiKham);
		return sum;
	}
};
class BenhVien {
private:
	vector<BenhNhan*> vec;
public:
	// De kiem tra xem co benh nhan co trong danh sach chua
	BenhNhan* isInit(const char* msbn) {
		for (BenhNhan* x : vec) {
			if (strcmp(msbn, x->getMSBN()) == 0) {
				return x;
			}
		}
		return nullptr;
	}
	// Them benh nhan vao danh sach
	void addBenhNhan(BenhNhan* a) {
		vec.push_back(a);
	}
	long long TKVP() {
		long long sum = 0;
		for (BenhNhan* x : vec) {
			x->printLSB();
			cout << "MSBN: " << x->getMSBN() << endl;
			cout << "Thanh tien: " << x->ThanhTien() << endl;
			cout << "----------------------------" << endl;
			sum += x->ThanhTien();
		}
		return sum;
	}
	void updateCuoiNgay(int n) {
		for (BenhNhan* a : vec) {
			NoiTru* tmp = dynamic_cast<NoiTru*>(a);
			if (tmp == nullptr) {
				continue;
			}
			else {
				tmp->updateXuatVien(n);
			}
		}
	}
	~BenhVien() {
		for (auto& x : vec) {
			delete x;
		}
		vec.clear();
	}
};

void NhapData(const char* fileName, BenhVien& a) {
	ifstream fi("data.txt");
	if (!fi) {
		cout << "Khong the truy cap file " << fileName << endl;
		return;
	}
	else {
		char buffer[100];
		while (fi.getline(buffer, 100)) {
			int ngay = atoi(strtok(buffer, " "));
			char* msbn = strtok(nullptr, " ");
			char* action = strtok(nullptr, " ");
			if (strcmp(action, "KB") == 0) {
				int phikham = atoi(strtok(nullptr, " "));
				NgoaiTru* isInit = dynamic_cast<NgoaiTru*>(a.isInit(msbn));
				if (isInit != nullptr) {
					isInit->update(ngay, phikham);
				}
				else {
					a.addBenhNhan(new NgoaiTru(ngay, msbn, phikham));
				}
			}
			else if (strcmp(action, "NV") == 0) {
				NoiTru* isInit = dynamic_cast<NoiTru*>(a.isInit(msbn));
				int phikham = atoi(strtok(nullptr, " "));
				char* loaiphong = strtok(nullptr, " ");
				if (isInit == nullptr) {
					a.addBenhNhan(new NoiTru(ngay, msbn, phikham, loaiphong));
				}
				else {
					//Doi tuong da duoc tao
					if (isInit->getState() == false) { // Da xuat vien moi cho NV
						isInit->update(ngay, phikham, loaiphong);
					}
				}
			}
			else if (strcmp(action, "XV") == 0) {
				NoiTru* isInit = dynamic_cast<NoiTru*>(a.isInit(msbn));
				if (isInit == nullptr) {
					cout << "Doi tuong chua duoc tao de xuat vien" << endl;
				}
				else {
					if (isInit->getState() == true) {
						isInit->updateXuatVien(ngay);
					}
				}
			}
			else if (strcmp(action, "TKVP") == 0) {
				a.updateCuoiNgay(ngay);
				cout << "Tong vien phi cua benh vien la: " << endl;
				cout << a.TKVP() << endl;
			}
		}
	}
	fi.close();
}
int NgoaiTru::cnt = 0;
int NoiTru::cnt = 0;

int main() {
	BenhVien a;
	const char* fileName = "data.txt";
	NhapData(fileName, a);
	cout << endl;
	cout << "So benh nhan ngoai tru la: " << NgoaiTru::cnt << endl;
	cout << "So benh nhan noi tru la: " << NoiTru::cnt << endl;

	system("pause");
	return 0;
}