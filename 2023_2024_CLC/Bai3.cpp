#include <iostream>
using namespace std;

class PrimeList {
private:
	int* arr;
	int size;

	bool checkPrime(int n) {
		if (n <= 1)	return false;
		for (int i = 2; i <= sqrt(n); i++) {
			if (n % i == 0)	return false;
		}
		return true;
	}
public:
	PrimeList() {
		arr = nullptr;
		size = 0;
	}
	~PrimeList() {
		if (arr != nullptr)
			delete[] arr;
		size = 0;
	}
	PrimeList(int n) : PrimeList() {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if(checkPrime(i))
				cnt++;
		}
		arr = new int[cnt];
		size = 0;
		for (int i = 0; i < n; i++) {
			if (checkPrime(i)) {
				arr[size++] = i;
			}
		}
	}
	int count() {
		return size;
	}
	void generate(int n) {
		if (arr) {
			delete[] arr;
			size = 0;
		}

		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (checkPrime(i))
				cnt++;
		}
		arr = new int[cnt];
		size = 0;
		for (int i = 0; i < n; i++) {
			if (checkPrime(i)) {
				arr[size++] = i;
			}
		}
	}
	friend ostream& operator<<(ostream& os, const PrimeList& a) {
		for (int i = 0; i < a.size; i++) {
			os << a.arr[i] << " ";
		}
		return os;
	}
	PrimeList& operator=(PrimeList& other) {
		if (this == &other) {
			return *this;
		}
		// Deep Copy
		if (arr != nullptr) {
			delete[] arr;
			size = 0;
		}
		size = other.size;
		arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
		return *this;
	}
	int operator[](int a) {
		if (size <= a) {
			throw exception("Bugs");
		}
		return arr[a];
	}
};


//int main() {
//	PrimeList list1(100);
//	cout << list1 << endl << endl;
//	list1.generate(500);
//	cout << list1;
//
//	PrimeList list2;
//	list2 = list1;
//	cout << list2[list2.count() - 1];
//	system("pause");
//	return 0;
//}