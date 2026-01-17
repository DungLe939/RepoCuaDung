#include <iostream>
using namespace std;
class SortAlgorithm {
private:
	static SortAlgorithm* _algorithm; // Luu doi tuong duy nhat cua lop
	void (*currentAlgorithm)(float[], int);
	SortAlgorithm() {
		currentAlgorithm = InsertionSort;
	}
public:
	
	static SortAlgorithm* getObject(void(*pAlg)(float[], int));
	static void SelectionSort(float[], int);
	static void InsertionSort(float[], int);
	static void InterchangeSort(float[], int);
	void sort(float a[], int n) {
		if (currentAlgorithm != nullptr) {
			currentAlgorithm(a, n);
		}
	}
};

SortAlgorithm* SortAlgorithm::_algorithm = nullptr;
SortAlgorithm* SortAlgorithm::getObject(void(*pAlg)(float[], int) = NULL) {
	if (_algorithm == nullptr) {
		return new SortAlgorithm();
	}
	if (pAlg != nullptr) {
		_algorithm->currentAlgorithm = pAlg;
	}
	return _algorithm;
}
void SortAlgorithm::SelectionSort(float a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swap(a[i], a[minIndex]);
		}
	}
}
void SortAlgorithm::InsertionSort(float a[], int n) {
	for (int i = 1; i < n; i++) {
		float key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
void SortAlgorithm::InterchangeSort(float a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
			}
		}
	}
}
int main() {
	float arr[] = { 64, 34, 25, 12, 22, 11, 90 };
	int n = sizeof(arr) / sizeof(arr[0]);
	SortAlgorithm* sorter = SortAlgorithm::getObject(SortAlgorithm::InterchangeSort);
	sorter->sort(arr, n);
	cout << "Sorted array: \n";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}
{
	char* className() {
		return (char*)"ELIPSE;
	}
	// So sanh xem Figure* co phai la doi tuong cua lop Ellipse hay khong
	bool isInstanceOf(Figure* a, char* className) {
		if(strcmp(a->className(), className) == 0) {
			return true;
		})
	}
	Figure* clone() {
		return new Ellipse(*this);
	}
}