

#include "sort.h"

using namespace std;

int *createArray(const int n) {
	int *Arr = new int[n];

	for (int i = 0; i < n; i++) {
		Arr[i] = rand() % 1000;
	}

	return Arr;
}

void showArray(const int * const Arr, const int n) {
	cout << "[";
	for (int i = 0; i < n; i++) {
		cout << (i == 0 ? "" : ",") << Arr[i];
	}
	cout << "]" << endl;
}

void test() {
	cout << "Default:";
	int *Arr = createArray(10);
	showArray(Arr, 10);

	cout << "Sorted (by patience sort):";
	int *ordArr = patienceSort(Arr, 10);
	showArray(ordArr, 10);
	delete[] ordArr;

	cout << "Sorted (by gnome sort):";
	ordArr = gnomeSort(Arr, 10);
	showArray(ordArr, 10);
	delete[] ordArr;

	cout << "Sorted (by qsort):";
	ordArr = qs(Arr, 10);
	showArray(ordArr, 10);
	delete[] ordArr;

	cout << "Sorted (by sortcomb):";
	ordArr = sortcomb(Arr, 10);
	showArray(ordArr, 10);
	delete[] ordArr;

	delete [] Arr;
}

int main() {
	for (int i = 0; i < 10; i++) {
		cout << "Test " << i + 1 << ":" << endl;
		test();
		cout << endl;
	}

	return 0;
}
