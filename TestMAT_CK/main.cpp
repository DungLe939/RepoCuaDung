#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class MachDien {
protected:
	string _MaSo;
	double _DienTro;
	double _TriGia;
public:
	virtual ~MachDien() {};
	virtual void Nhap(istream& is) = 0;
	virtual void Xuat(ostream& os, int n) = 0;
	virtual double TinhDienTro() = 0;
	virtual double TinhTriGia() = 0;
};

MachDien* TaoDoiTuong(string type, string maso);

class MachDon : public MachDien {
public:
	MachDon(string maso = "Default", double trigia = 0, double dientro = 0) {
		_MaSo = maso;
		_TriGia = trigia;
		_DienTro = dientro;
	}
	double TinhDienTro() {
		return _DienTro;
	}
	double TinhTriGia() {
		return _TriGia;
	}
	void Nhap(istream& is) {
		string tmp;
		is >> _TriGia >> _DienTro;
		is >> tmp;
	}
	void Xuat(ostream& os, int n) {
		for (int i = 0; i < n; i++) {
			cout << '\t';
		}
		os << "MachDon - " << _MaSo << " - " << _TriGia << " - " << _DienTro << endl;
	}
};

class MachPhuc : public MachDien {
protected:
	vector<MachDien*> _child;
public:
	void add(MachDien* a) {
		if (a == nullptr) {
			throw exception("Pointer is null");
		}
		_child.push_back(a);
	}
	~MachPhuc() {
		for (MachDien* x : _child) {
			delete x;
		}
		_child.clear();
	}
	void Nhap(istream& is) {
		string type;
		is >> _TriGia >> _DienTro;
		while (is >> type) {
			if (type == _MaSo) {
				break;
			}
			string maso, tmp;
			is >> tmp >> maso;
			MachDien* m = TaoDoiTuong(type, maso);
			if (m) {
				m->Nhap(is);
				_child.push_back(m);
			}
		}
	}
};

class MachNoiTiep : public MachPhuc {
public:
	MachNoiTiep(string maso = "Default", double trigia = 0, double dientro = 0) {
		_MaSo = maso;
		_TriGia = trigia;
		_DienTro = dientro;
	}
	double TinhTriGia() {
		double res = 0;
		for (MachDien* x : _child) {
			res += x->TinhTriGia();
		}
		return res;
	}
	double TinhDienTro() {
		double res = 0;
		for (MachDien* x : _child) {
			res += x->TinhDienTro();
		}
		return res;
	}
	void Xuat(ostream& os, int n) {
		for (int i = 0; i < n; i++) {
			os << '\t';
		}
		os << fixed << setprecision(2);
		os << "MachNoiTiep - " << _MaSo << " - " << TinhTriGia() << " - " << TinhDienTro() << endl;
		for (MachDien* m : _child) {
			m->Xuat(os, n + 1);
		}
	}
};

class MachSongSong : public MachPhuc {
public:
	MachSongSong(string maso = "Default", double trigia = 0, double dientro = 0) {
		_MaSo = maso;
		_TriGia = trigia;
		_DienTro = dientro;
	}
	double TinhTriGia() {
		double res = 0;
		for (MachDien* x : _child) {
			res += x->TinhTriGia();
		}
		return res*1.1;
	}
	double TinhDienTro() {
		double res = 0;
		for (MachDien* x : _child) {
			double R = x->TinhDienTro();
			if (R == 0) {
				throw exception("Devide by zero");
			}
			res += 1/x->TinhDienTro();
		}
		if (res == 0) {
			throw exception("Devide by zero in res");
		}
		return 1/res;
	}
	void Xuat(ostream& os, int n) {
		for (int i = 0; i < n; i++) {
			os << '\t';
		}
		os << fixed << setprecision(2);
		os << "MachSongSong - " << _MaSo << " - " << TinhTriGia() << " - " << TinhDienTro() << endl;
		for (MachDien* m : _child) {
			m->Xuat(os, n + 1);
		}
	}
};

class BoMach {
private:
	vector<MachDien*> _list;

	// Nhốt
	BoMach(){}

public:
	static BoMach getInstance() {
		static BoMach a;
		return a;
	}
	~BoMach() {
		for (MachDien* a : _list) {
			delete a;
		}
		_list.clear();
	}
	void add(MachDien* a) {
		if (a == nullptr) {
			throw exception("Pointer is nullptr");
		}
		_list.push_back(a);
	}
	void Nhap(istream& is) {
		string type, tmp, maso;
		while (is >> type >> tmp >> maso) {
			MachDien* m = TaoDoiTuong(type, maso);
			if (m) {
				m->Nhap(is);
				_list.push_back(m);
			}
		}
	}
	void Xuat(ostream& os) const {
		for (MachDien* m : _list) {
			m->Xuat(os, 0);
			os << endl;
		}
	}
	friend istream& operator>>(istream& is, BoMach& a) {
		a.Nhap(is);
		return is;
	}
	friend ostream& operator<<(ostream& os, const BoMach& a) {
		a.Xuat(os);
		return os;
	}
};

MachDien* TaoDoiTuong(string type, string maso) {
	MachDien* a = nullptr;
	if (type == "MachDon") {
		a = new MachDon(maso);
	}
	else if (type == "MachNoiTiep") {
		a = new MachNoiTiep(maso);
	}
	else if (type == "MachSongSong") {
		a = new MachSongSong(maso);
	}
	else {
		throw exception("Loai mach khong hop le");
	}
	return a;
}

int main() {
	try {
		ifstream fi("data.txt");
		if (!fi) {
			throw exception("File khong mo duoc");
		}
		BoMach bomach = BoMach::getInstance();
		fi >> bomach;
		cout << bomach;
	}
	catch(const exception& ex){
		cout << ex.what() << endl;
	}

	system("pause");
	return 0;
}