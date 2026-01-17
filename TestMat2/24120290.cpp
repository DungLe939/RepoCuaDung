/*
* Ho va ten: Le Tan Dung
* MSSV: 24120290
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
class ListDHTT {
public:
	class DongHoTT {
	private:
		int _phut, _giay, _phanngan;
		int _gio;
	public:
		int GetPhut() const {
			return _phut;
		}
		void ChuanHoa() {
			_phut = abs(_phut);
			_giay = abs(_giay);
			_phanngan = abs(_phanngan);

			int giaydu = _phanngan / 1000;
			_phanngan %= 1000;
			_giay += giaydu;

			int phutdu = _giay / 60;
			_giay %= 60;
			_phut += phutdu;
		}
		void ChuanHoav2() {
			_phut = abs(_phut);
			_giay = abs(_giay);
			_phanngan = abs(_phanngan);
			_gio = abs(_gio);

			int giaydu = _phanngan / 1000;
			_phanngan %= 1000;
			_giay += giaydu;

			int phutdu = _giay / 60;
			_giay %= 60;
			_phut += phutdu;

			int giodu = _phut / 60;
			_phut %= 60;
			_gio += giodu;
		}
		void Xuat() {
			cout << setw(3) << setfill('0') << _gio << ":"
				<< setw(2) << setfill('0') << _phut << ":"
				<< setw(2) << setfill('0') << _giay << ":"
				<< setw(3) << setfill('0') << _phanngan;
		}
		DongHoTT() {
			_phut = _giay = _phanngan = 0;
			_gio = 0;
		}
		DongHoTT(int phanngan) : DongHoTT() {
			_phanngan = phanngan;
			ChuanHoa();
		}
		DongHoTT(int giay, int phanngan) : DongHoTT() {
			_giay = giay;
			_phanngan = phanngan;
			ChuanHoa();
		}
		DongHoTT(int phut, int giay, int phanngan) : DongHoTT() {
			_phut = phut;
			_giay = giay;
			_phanngan = phanngan;
			ChuanHoa();
		}
		DongHoTT(const char* a) : DongHoTT() {
			int tmp = sscanf(a, "%d:%d:%d", &_phut, &_giay, &_phanngan);
			ChuanHoa();
		}
		DongHoTT(const DongHoTT& a) : DongHoTT() {
			if (this != &a) {
				_giay = a._giay;
				_phut = a._phut;
				_phanngan = a._phanngan;
			}
		}
		DongHoTT operator+(const DongHoTT& a) {
			DongHoTT res(*this);
			res._phut += a._phut;
			res._giay += a._giay;
			res._phanngan += a._phanngan;
			res.ChuanHoa();
			return res;
		}
		DongHoTT operator+(int giay) {
			DongHoTT res(*this);
			res._giay += giay;
			res.ChuanHoa();
			return res;
		}
		DongHoTT& operator++() {
			_giay += 1;
			ChuanHoa();
			return *this;
		}
		DongHoTT operator++(int) {
			DongHoTT res(*this);
			_giay += 1;
			return res;
		}
		DongHoTT& operator=(const DongHoTT& a) {
			if (this == &a)	return *this;
			else {
				_giay = a._giay;
				_phut = a._phut;
				_phanngan = a._phanngan;
			}
			return *this;
		}
		bool operator>(const DongHoTT& a) {
			if (_phut > a._phut) {
				return true;
			}
			if (_phut < a._phut) {
				return false;
			}
			if (_giay > a._giay) {
				return true;
			}
			if (_giay < a._giay) {
				return false;
			}
			if (_phanngan > a._phanngan) {
				return true;
			}
			if (_phanngan < a._phanngan) {
				return false;
			}
			return false;
		}
		friend DongHoTT operator+(const int& a, const DongHoTT& b) {
			DongHoTT res(b);
			res._giay += a;
			res.ChuanHoa();
			return res;
		}
		friend ostream& operator<<(ostream& os, const DongHoTT& a) {
			os << setw(3) << setfill('0') << a._phut << ":"
				<< setw(2) << setfill('0') << a._giay << ":"
				<< setw(3) << setfill('0') << a._phanngan;
			return os;
		}
	};
private:
	struct Node {
		DongHoTT data;
		Node* next;
	};
	Node* _head;
	Node* _tail;
	int size;
public:
	ListDHTT() {
		_head = _tail = 0;
		size = 0;
	}
	void AddTail(const DongHoTT& a) {
		Node* node = new Node{ a, nullptr };
		if (!node)	return;
		if (_head == nullptr) {
			_head = _tail = node;
		}
		else {
			_tail->next = node;
			_tail = node;
		}
		size++;
	}
	void AddTail(const char* a) {
		AddTail(DongHoTT(a));
	}
	void Clear() {
		while (_head) {
			Node* node = _head;
			_head = _head->next;
			delete node;
		}
		size = 0;
		_head = _tail = nullptr;
	}
	~ListDHTT() {
		Clear();
	}
	friend ostream& operator<<(ostream& os, const ListDHTT& a) {
		Node* node = a._head;
		while (node) {
			os << node->data << endl;
			node = node->next;
		}
		return os;
	}
	class Iterator {
	public:
		using iterator_category = forward_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = DongHoTT;
		using pointer = DongHoTT*;
		using reference = DongHoTT&;
	private:
		friend class ListDHTT;
		Node* current_Node;
		Iterator(Node* node) {
			current_Node = node;
		}
	public:
		Iterator() {
			current_Node = nullptr;
		}
		reference operator*() const {
			if (!current_Node) {
				throw out_of_range("Dereference end() or null node");
			}
			return current_Node->data;
		}
		pointer operator->() const {
			if (!current_Node) {
				throw out_of_range("Dereference end() or null node");
			}
			return &(current_Node->data);
		}
		Iterator& operator++() {
			if (current_Node == nullptr) {
				throw out_of_range("Error");
			}
			current_Node = current_Node->next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator res(*this);
			if (current_Node) {
				current_Node = current_Node->next;
			}
			return res;
		}
		bool operator==(const Iterator& a) {
			return current_Node == a.current_Node;
		}
		bool operator!=(const Iterator& a) {
			return !(*this == a);
		}
	};
	Iterator begin() {
		return Iterator(_head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}
};
bool funcCountIf(const ListDHTT::DongHoTT& a) {
	return a.GetPhut() >= 60;
}
int main() {
	ListDHTT list;
	ListDHTT::DongHoTT dhtt1(20, 70, -2076), dhtt2("13:31:94"), dhtt3(200, 8060), dhtt4(40001);

	cout << "dhtt1: " << dhtt1 << endl;
	cout << "dhtt2: " << dhtt2 << endl;
	cout << "dhtt3: " << dhtt3 << endl;
	cout << "dhtt4: " << dhtt4 << endl;

	list.AddTail("1:2:3");
	list.AddTail(dhtt1);
	list.AddTail(dhtt2);
	list.AddTail(dhtt3);
	list.AddTail(dhtt4);
	cout << "List:\n" << list << endl;

	list.AddTail(dhtt1 + dhtt2);
	list.AddTail(dhtt3 + 12345);
	list.AddTail(10000 + dhtt4);
	cout << "List:\n" << list << endl;

	list.AddTail(10000 + ++dhtt1 + dhtt2++);
	list.AddTail(10000 + dhtt1++ + dhtt2++);
	cout << "dhtt1: " << dhtt1 << endl;
	cout << "dhtt2: " << dhtt2 << endl;
	cout << "List:\n" << list << endl;

	int nCI = std::count_if(list.begin(), list.end(), funcCountIf);
	cout << "So DHTT co phut >= 60: " << nCI << endl;

	ListDHTT::DongHoTT dhttMax = *list.begin();
	std::for_each(list.begin(), list.end(),
		[&dhttMax](ListDHTT::DongHoTT dhtt) {
			if (dhtt > dhttMax) {
				dhttMax = dhtt;
			}
		}
	);
	cout << "DHTT lon nhat: " << dhttMax << endl;

	for (ListDHTT::Iterator it = list.begin(); it != list.end(); ++it) {
		ListDHTT::DongHoTT& res = *it;
		res.ChuanHoav2();
		res.Xuat();
		cout << endl;
	}
	system("pause");
	return 0;
}