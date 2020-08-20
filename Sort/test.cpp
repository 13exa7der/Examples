
#include "sort.h"

int *createArray(const int n) {
	int *Arr = new int[n];

	for (int i = 0; i < n; i++) {
		Arr[i] = rand() % 1000;
	}

	return Arr;
}

void test(const int n) {
	([n]() {
		auto begin = chrono::steady_clock::now();
		int *Arr = createArray(n);
		patienceSort(Arr, n);
		auto end = chrono::steady_clock::now();
		auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
		cout << "Patience sort: " << elapsed_ms.count() << " ms" << endl;
		delete[] Arr;
	})();

	([n]() {
		auto begin = chrono::steady_clock::now();
		int *Arr = createArray(n);
		gnomeSort(Arr, n);
		auto end = chrono::steady_clock::now();
		auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
		cout << "Gnome sort: " << elapsed_ms.count() << " ms" << endl;
		delete[] Arr;
	})();

	([n]() {
		auto begin = chrono::steady_clock::now();
		int *Arr = createArray(n);
		qs(Arr, n);
		auto end = chrono::steady_clock::now();
		auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
		cout << "Qsort: " << elapsed_ms.count() << " ms" << endl;
		delete[] Arr;
	})();

	([n]() {
		auto begin = chrono::steady_clock::now();
		int *Arr = createArray(n);
		sortcomb(Arr, n);
		auto end = chrono::steady_clock::now();
		auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
		cout << "Comb sort: " << elapsed_ms.count() << " ms" << endl;
		delete[] Arr;
	})();

	
}

int main() {

	for (int i = 0; i < 10; i++) {
		cout << "Test " << i + 1 << ":" << endl;
		test(4000);
		cout << endl;
	}

	return 0;
}