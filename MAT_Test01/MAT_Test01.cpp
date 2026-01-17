/*
Ho va ten: Le Tan Dung
MSSV: 24120290
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
		int getPhut() const {
			return _phut;
		}
		DongHoTT() {
			_phut = _giay = _phanngan = _gio = 0;
		}
		void ChuanHoaGio() {
			ChuanHoa();
			int phutdu = _phut / 60;
			_gio += phutdu;
			_phut %= 60;
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
		DongHoTT(int phanngan) : DongHoTT() {
			_phanngan = phanngan;
			ChuanHoa();
		}
		DongHoTT(int giay, int phanngan) : DongHoTT() {
			_phanngan = phanngan;
			_giay = giay;
			ChuanHoa();
		}
		DongHoTT(int phut, int giay, int phanngan) : DongHoTT() {
			_phut = phut;
			_phanngan = phanngan;
			_giay = giay;
			ChuanHoa();
		}
		DongHoTT(const char* s) : DongHoTT() {
			if (s == nullptr)	return;
			char* tmp = new char[strlen(s) + 1];
			strcpy(tmp, s);

			_phut = atoi(strtok(tmp, ":"));
			_giay = atoi(strtok(nullptr, ":"));
			_phanngan = atoi(strtok(nullptr, ":"));

			ChuanHoa();
			delete[] tmp;
		}
		DongHoTT operator+(const DongHoTT& a) {
			DongHoTT res(*this);
			res._giay += a._giay;
			res._phut += a._phut;
			res._phanngan += a._phanngan;
			res.ChuanHoa();
			return res;
		}
		DongHoTT operator+(int a) {
			DongHoTT res(*this);
			res._giay += a;
			res.ChuanHoa();
			return res;
		}
		DongHoTT& operator++() {
			_giay++;
			ChuanHoa();
			return *this;
		}
		DongHoTT operator++(int) {
			DongHoTT res(*this);
			_giay++;
			ChuanHoa();
			return res;
		}
		bool operator>(const DongHoTT& a) {
			if (_phut > a._phut) {
				return true;
			}
			else if (_phut < a._phut) {
				return false;
			}

			if (_giay > a._giay) {
				return true;
			}
			else if (_giay < a._giay) {
				return false;
			}

			if (_phanngan > a._phanngan) {
				return true;
			}
			else if (_phanngan < a._phanngan) {
				return false;
			}
			return false;
		}
		void Xuat() {
			cout << setw(3) << setfill('0') << _gio << ":"
				<< setw(2) << setfill('0') << _phut << ":"
				<< setw(2) << setfill('0') << _giay << ":"
				<< setw(3) << setfill('0') << _phanngan;
		}
		friend DongHoTT operator+(int n, const DongHoTT& a) {
			DongHoTT res(a);
			res._giay += n;
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
	int _size;
public:
	//using DongHoTT = DongHoTT;
	ListDHTT() {
		_head = _tail = nullptr;
		_size = 0;
	}
	void Clear() {
		while (_head) {
			Node* node = _head;
			_head = _head->next;
			delete node;
		}
		_head = _tail = nullptr;
		_size = 0;
	}
	~ListDHTT() {
		Clear();
	}
	void AddTail(const DongHoTT& a) {
		Node* node = new Node{ a, nullptr };
		if (_head == nullptr) {
			_head = _tail = node;
		}
		else {
			_tail->next = node;
			_tail = node;
		}
		_size++;
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
		Node* currentNode;
		Iterator(Node* a) {
			currentNode = a;
		}
	public:
		Iterator() {
			currentNode = nullptr;
		}
		reference operator*() const {
			if (currentNode == nullptr) {
				throw out_of_range("Dereference null or end()");
			}
			return currentNode->data;
		}
		pointer operator->() const {
			if (currentNode == nullptr) {
				throw out_of_range("Accessing null or end()");
			}
			return &(currentNode->data);
		}
		Iterator& operator++() {
			if (currentNode == nullptr) {
				throw out_of_range("Accessing null or end()");
			}
			currentNode = currentNode->next;
			return *this;
		}
		Iterator operator++(int) {
			if (currentNode == nullptr) {
				throw out_of_range("Accessing null or end()");
			}
			Iterator res(*this);
			currentNode = currentNode->next;
			return res;
		}
		bool operator==(const Iterator& a) {
			return (currentNode == a.currentNode);
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
	void InChuanHoa2() {
		Node* node = _head;
		while (node) {
			node->data.ChuanHoaGio();
			node->data.Xuat();
			cout << endl;
			node = node->next;
		}
	}
};
bool funcCountIf(const ListDHTT::DongHoTT& a) {
	return a.getPhut() >= 60;
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
	cout << "So DHTT co so phut >= 60: " << nCI << endl;

	ListDHTT::DongHoTT dhttMax = *list.begin();
	std::for_each(list.begin(), list.end(),
		[&dhttMax](ListDHTT::DongHoTT dhtt) {
			if (dhtt > dhttMax) {
				dhttMax = dhtt;
			}
		});
	cout << "DHTT lon nhat: " << dhttMax << endl;

	list.InChuanHoa2();

	system("pause");
	return 0;
}