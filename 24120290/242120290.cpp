#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class NhanVien {
protected:
	string _name;
	string _address;
public:
	virtual ~NhanVien() {}
	virtual void Xuat(ostream& os) const = 0;
	virtual void Nhap(istream& is) = 0;
	friend ostream& operator<<(ostream& os, const NhanVien& a) {
		a.Xuat(os);
		return os;
	}
	friend istream& operator>>(istream& is, NhanVien& a) {
		a.Nhap(is);
		return is;
	}
};

class NhanVienThuKy : public NhanVien {
private:
	string _ccnn;
	int _slbc;
public:
	NhanVienThuKy(string name, string diachi, string ccna, int slbc) {
		_name = name;
		_address = diachi;
		_ccnn = ccna;
		_slbc = slbc;
	}
	void Xuat(ostream& os) {
		os << "nvtk: " << _name << " - " << _address << " - " << _ccnn << " - " << _slbc;
	}
	void Nhap()
};

class CongTy {
private:
	CongTy() {}
	vector<NhanVien*> _list;
public:
	static CongTy getInstance() {
		static CongTy a;
		return a;
	}
	~CongTy() {
		for (NhanVien* a : _list) {
			if (a != nullptr) {
				delete a;
			}
		}
		_list.clear();
	}
	void add(NhanVien* a) {
		if (a == nullptr) {
			throw exception("Nhan vien is nullptr");
		}
	}
	void Xuat(ostream& os) {
		for (NhanVien* a : _list) {
			cout << a << endl;
		}
	}
	void Nhap(istream& is) {
		string line;
		while (getline(is, line)) {

			//Get type
			size_t pos1 = line.find(':');
			string type = line.substr(0, pos1);

			//Get Name
			size_t pos2 = line.find('(');
			string name = line.substr(pos1 + 2, pos2 - pos1 - 3);

			//Get Address
			size_t pos3 = line.find(')');
			string address = line.substr(pos2 + 1, pos3 - pos2 - 1);

			// TIm chuyen nganh
			size_t pos4 = line.find('[');
			size_t pos5 = line.find(']');
			string chuyengang = line.substr(pos4 + 1, pos5 - pos4 - 1);

			// 5. Tìm kinh nghi?m (trong ngo?c nh?n)
			size_t pos6 = line.find("<");
			size_t pos7 = line.find(">");
			string kn = line.substr(pos6 + 1, pos7 - pos6 - 1);
		}
	}
};
int main() {
	try {
		ifstream fi("data.txt");
		if (!fi) {
			throw exception("Khong mo duoc file");
		}

	}
	catch (const exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}

	return 0;
}