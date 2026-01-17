/*
Ho va ten : Le Tan Dung
MSSV: 24120290
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class MachDien {
protected:
	string _name;
	double _trigia;
	double _dientro;
public:
	virtual ~MachDien() {}
	virtual double getTriGia() = 0;
	virtual double getDienTro() = 0;
	virtual void Nhap(istream& is) = 0;
	virtual void Xuat(ostream& os, int n) = 0;
	virtual int countMachDon() = 0;
};

MachDien* TaoDoiTuong(string type, string name);

class MachDon : public MachDien {
public:
	MachDon(string name = "default", double trigia = 0, double dientro = 0) {
		if (trigia < 0 || dientro < 0) {
			throw exception("Value is invalid");
		}
		_name = name;
		_trigia = trigia;
		_dientro = dientro;
	}
	double getTriGia() {
		return _trigia;
	}
	double getDienTro() {
		return _dientro;
	}
	void Nhap(istream& is) {
		is >> _trigia >> _dientro;
		string closeTag;
		is >> closeTag;
	}
	void Xuat(ostream& os, int n) {
		for (int i = 0; i < n; i++) {
			os << '\t';
		}
		os << "MachDon - " << _name << " - " << _trigia << " - " << _dientro << endl;
	}
	int countMachDon() {
		return 1;
	}
};

class MachPhuc : public MachDien {
protected:
	vector<MachDien*> _child;
public:
	void add(MachDien* a) {
		if (a == nullptr) {
			throw exception("Argument can not be nullptr");
		}
		_child.push_back(a);
	}
	~MachPhuc() {
		for (MachDien* x : _child) {
			if (x)	delete x;
		}
		_child.clear();
	}
	void Nhap(istream& is) {
		string type;
		is >> _trigia >> _dientro;
		while (is >> type) {
			if (type == _name) {
				return;
			}
			string name;
			string tmp;
			is >> tmp >> name;
			MachDien* machdien = TaoDoiTuong(type, name);
			if (machdien) {
				machdien->Nhap(is);
				_child.push_back(machdien);
			}
		}
	}
};

class MachNoiTiep : public MachPhuc {
public:
	MachNoiTiep(string name = "default", double trigia = 0, double dientro = 0) {
		if (trigia < 0 || dientro < 0) {
			throw exception("Value is invalid");
		}
		_name = name;
		_trigia = trigia;
		_dientro = dientro;
	}
	double getTriGia() {
		double res = 0;
		for (MachDien* x : _child) {
			res += x->getTriGia();
		}
		return res;
	}
	double getDienTro() {
		double res = 0;
		for (MachDien* x : _child) {
			res += x->getDienTro();
		}
		return res;
	}
	void Xuat(ostream& os, int n) {
		for (int i = 0; i < n; i++) {
			cout << '\t';
		}
		os << "MachNoiTiep - " << _name << " - " << getTriGia() << " - " << getDienTro() << endl;
		for (MachDien* x : _child) {
			x->Xuat(os, n + 1);
		}
	}
	int countMachDon() {
		int res = 0;
		for (MachDien* x : _child) {
			res += x->countMachDon();
		}
		return res;
	}
};
int cnt = 0;
string name = "";

class MachSongSong : public MachPhuc {
public:
	MachSongSong(string name = "default", double trigia = 0, double dientro = 0) {
		if (trigia < 0 || dientro < 0) {
			throw exception("Value is invalid");
		}
		_name = name;
		_trigia = trigia;
		_dientro = dientro;
	}
	double getTriGia() {
		double res = 0;
		for (MachDien* x : _child) {
			res += x->getTriGia();
		}
		return res*1.1;
	}
	double getDienTro() {
		double res = 0;
		for (MachDien* x : _child) {
			double tmp = x->getDienTro();
			if (tmp == 0) {
				throw exception("Can not devide by zero");
			}
			res += 1/x->getDienTro();
		}
		if (res == 0) {
			throw exception("Dien tro is invalid");
		}
		return 1/res;
	}
	void Xuat(ostream& os, int n) {
		for (int i = 0; i < n; i++) {
			cout << '\t';
		}
		os << "MachSongSong - " << _name << " - " << getTriGia() << " - " << getDienTro() << endl;
		for (MachDien* x : _child) {
			x->Xuat(os, n + 1);
		}
	}
	int countMachDon() {
		int res = 0;
		for (MachDien* x : _child) {
			res += x->countMachDon();
		}
		if (res > cnt) {
			cnt = res;
			name = _name;
		}
		return res;
	}
};

class BoMach {
private:
	BoMach(){}
	vector<MachDien*> _list;
public:
	static BoMach getInstance() {
		static BoMach instance;
		return instance;
	}
	~BoMach() {
		for (MachDien* x : _list) {
			if (x)	delete x;
		}
		_list.clear();
	}
	void add(MachDien* a) {
		if (a == nullptr) {
			throw exception("Argument can not be nullptr");
		}
		_list.push_back(a);
	}
	void Nhap(istream& is) {
		string type;
		string name;
		string tmp;
		while (is >> type >> tmp >> name) {
			MachDien* a = TaoDoiTuong(type, name);
			if (a) {
				a->Nhap(is);
				_list.push_back(a);
			}
		}

	}
	void Xuat(ostream& os) const {
		for (MachDien* x : _list) {
			x->Xuat(os, 0);
		}
	}
	friend ostream& operator<<(ostream& os, const BoMach& a) {
		a.Xuat(os);
		return os;
	}
	friend istream& operator>>(istream& is, BoMach& a) {
		a.Nhap(is);
		return is;
	}
	int countMachDon() {
		int res = 0;
		for (MachDien* x : _list) {
			res += x->countMachDon();
		}
		return res;
	}
};

MachDien* TaoDoiTuong(string type, string name) {
	MachDien* tmp = nullptr;
	if (type == "MachDon") {
		tmp = new MachDon(name);
	}
	else if (type == "MachSongSong") {
		tmp = new MachSongSong(name);
	}
	else if (type == "MachNoiTiep") {
		tmp = new MachNoiTiep(name);
	}
	else {
		throw exception("Invalid type");
	}
	return tmp;
}

int main() {
	try {
		ifstream fi("data.txt");
		if (!fi) {
			throw exception("Can not open the file");
		}
		BoMach a = BoMach::getInstance();
		fi >> a;
		cout << a << endl;

		a.countMachDon();
		cout << "Mach song song: " << name << endl;
		cout << "So luong: " << cnt << endl;
	}
	catch (const exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}


	system("pause");
	return 0;
}

// Error o cho constuctor nhot lai bi thieu {}
// Bi sai loi chinh ta dan ra la abstract
// Co the bi double free